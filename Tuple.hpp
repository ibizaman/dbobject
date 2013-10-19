#include "polymorph/ResultSetHelper.hxx"
#include "polymorph/MySQLTypeConverter.h"
#include <stdexcept>

namespace dbobject {

/********************/
/* getOne functions */
/********************/

// Real logic of getOne()
template<int I>
std::tuple<> Tuple::getOne(std::shared_ptr<sql::ResultSet>)
{
    return std::tuple<>();
}

// For one row, get all results
template<int I, typename T, typename... Rest>
std::tuple<T, Rest...> Tuple::getOne(std::shared_ptr<sql::ResultSet> result)
{
    std::tuple<T> value(ResultSetHelper::get<T>(result, I));
    return std::tuple_cat(value, getOne<I+1, Rest...>(result));
}

/*
 * The purpose of the indirection is to allow decomposition of T into
 * std::tuple<Ts...>; since function templates can't be partially specialiased,
 * this must be done with overloading and template parameter inference from
 * argument types. The tuple isn't being passed to the private functions, only
 * a type_tag instance, which has zero overhead since it is an empty struct but
 * still allows template parameter inference to occur. – ecatmur
 */
template<typename... Ts>
std::tuple<Ts...> Tuple::getOne(std::shared_ptr<sql::ResultSet> result, type_tag<std::tuple<Ts...>>)
{
    if (!result->next()) {
        throw std::runtime_error("No result to fetch");
    }
    return getOne<1, Ts...>(result);
}

// Uses type_tag structure to call helper function.
template<typename T>
T Tuple::getOne(const SQL::Select& query)
{
    return getOne(_backend->query(query), type_tag<T>{});
}

template<typename T>
T Tuple::getOne(const SQL::TableName& table, const SQL::Expression& where)
{
    return getOne<T>(SQL::Query::select()
            .from(table)
            .where(where)
        );
}

template<typename T>
T Tuple::getOne(const SQL::TableName& table, const SQL::List<SQL::ColumnName>& columns, const SQL::Expression& where)
{
    return getOne<T>(SQL::Query::select(columns)
            .from(table)
            .where(where)
        );
}

/*************************/
/* getAsTuples functions */
/*************************/

// For each row, call getOne()
template<typename T>
typename VectorOfTuples<T>::type Tuple::getAsTuples(std::shared_ptr<sql::ResultSet> result)
{
    typename VectorOfTuples<T>::type vec;
    size_t count = result->rowsCount();
    vec.reserve(count);
    for (size_t i = 0; i < count; ++i) {
        vec.push_back(getOne(result, type_tag<T>{}));
    }
    return (vec);
}

// Execute query and gives result to next function.
template<typename T>
typename VectorOfTuples<T>::type Tuple::getAsTuples(const SQL::Select& query)
{
    return getAsTuples<T>(_backend->query(query));
}

template<typename T>
typename VectorOfTuples<T>::type Tuple::getAsTuples(const SQL::TableName& table)
{
    return getAsTuples<T>(SQL::Query::select()
            .from(table)
        );
}

template<typename T>
typename VectorOfTuples<T>::type Tuple::getAsTuples(const SQL::TableName& table, const SQL::Expression& where)
{
    return getAsTuples<T>(SQL::Query::select()
            .from(table)
            .where(where)
        );
}

template<typename T>
typename VectorOfTuples<T>::type Tuple::getAsTuples(const SQL::TableName& table, const SQL::List<SQL::ColumnName>& columns)
{
    return getAsTuples<T>(SQL::Query::select(columns)
            .from(table)
        );
}

template<typename T>
typename VectorOfTuples<T>::type Tuple::getAsTuples(const SQL::TableName& table, const SQL::List<SQL::ColumnName>& columns, const SQL::Expression& where)
{
    return getAsTuples<T>(SQL::Query::select(columns)
            .from(table)
            .where(where)
        );
}


/**************************/
/* getAsVectors functions */
/**************************/

template<int I> std::tuple<> Tuple::getAsVectors(std::shared_ptr<sql::ResultSet>)
{
    return std::tuple<>();
}

template<int I, typename T, typename... Rest>
typename TupleOfVectors<std::tuple<T, Rest...>>::type
    Tuple::getAsVectors(std::shared_ptr<sql::ResultSet> result)
{
    result->beforeFirst();

    std::vector<T> vec;
    vec.reserve(result->rowsCount());
    while (result->next()) {
        vec.push_back(ResultSetHelper::get<T>(result, I));
    }

    std::tuple<std::vector<T>> values(vec);
    return std::tuple_cat(values, getAsVectors<I+1, Rest...>(result));
}

template<typename... Ts>
typename TupleOfVectors<std::tuple<Ts...>>::type
    Tuple::getAsVectors(std::shared_ptr<sql::ResultSet> result, type_tag<std::tuple<Ts...>>)
{
    return getAsVectors<1, Ts...>(result);
}

/*
 * Uses type_tag structure to call helper function.
 */
template<typename T>
typename TupleOfVectors<T>::type
    Tuple::getAsVectors(const SQL::Select& query)
{
    return getAsVectors(_backend->query(query), type_tag<T>{});
}

template<typename T>
typename TupleOfVectors<T>::type
    Tuple::getAsVectors(const SQL::TableName& table)
{
    return getAsVectors<T>(SQL::Query::select()
            .from(table)
        );
}

template<typename T>
typename TupleOfVectors<T>::type
    Tuple::getAsVectors(const SQL::TableName& table, const SQL::Expression& where)
{
    return getAsVectors<T>(SQL::Query::select()
            .from(table)
            .where(where)
        );
}

template<typename T>
typename TupleOfVectors<T>::type
    Tuple::getAsVectors(const SQL::TableName& table, const SQL::List<SQL::ColumnName>& columns)
{
    return getAsVectors<T>(SQL::Query::select(columns)
            .from(table)
        );
}

template<typename T>
typename TupleOfVectors<T>::type
    Tuple::getAsVectors(const SQL::TableName& table, const SQL::List<SQL::ColumnName>& columns, const SQL::Expression& where)
{
    return getAsVectors<T>(SQL::Query::select(columns)
            .from(table)
            .where(where)
        );
}


/**************************/
/* store & update helpers */
/**************************/

template<typename Tup, int I>
auto Tuple::tupleToLiterals(const Tup&) const
    -> typename std::enable_if<I == std::tuple_size<Tup>::value, SQL::List<SQL::Literal>>::type
{
    return SQL::List<SQL::Literal>();
}

template<typename Tup, int I>
auto Tuple::tupleToLiterals(const Tup& typedValues) const
    -> typename std::enable_if<I != std::tuple_size<Tup>::value, SQL::List<SQL::Literal>>::type
{
    SQL::Literal stringValue = MySQLTypeConverter::toString(std::get<I>(typedValues));

    auto stringValues = tupleToLiterals<Tup, I+1>(typedValues);
    stringValues.insert(stringValues.begin(), stringValue);

    return stringValues;
}

template<typename TupleOfVectors, int I>
    auto Tuple::tupleOfVectorsRowToLiterals(const TupleOfVectors&, int) const
    -> typename std::enable_if<I == std::tuple_size<TupleOfVectors>::value, SQL::List<SQL::Literal>>::type
{
    return SQL::List<SQL::Literal>();
}

template<typename TupleOfVectors, int I>
    auto Tuple::tupleOfVectorsRowToLiterals(const TupleOfVectors& vectors, int row) const
    -> typename std::enable_if<I != std::tuple_size<TupleOfVectors>::value, SQL::List<SQL::Literal>>::type
{
    SQL::Literal stringValue = MySQLTypeConverter::toString(std::get<I>(vectors).at(row));

    auto stringValues = tupleOfVectorsRowToLiterals<TupleOfVectors, I+1>(vectors, row);
    stringValues.insert(stringValues.begin(), stringValue);

    return stringValues;
}

template<typename... Ts>
SQL::Insert Tuple::storeQuery(const PolymorphicType<SQL::TableName>& table, const std::tuple<Ts...>& tuple)
{
    return SQL::Query::insert()
            .addValues(tupleToLiterals(tuple))
            .into(*table);
}

template<typename... Ts>
SQL::Insert Tuple::storeQuery(const PolymorphicType<SQL::TableName>& table, const std::tuple<std::vector<Ts>...>& vectors)
{
    auto query = SQL::Query::insert().into(*table);
    for (int i = 0; i < std::get<0>(vectors).size(); ++i) {
        query.addValues(tupleOfVectorsRowToLiterals(vectors, i));
    }
    return query;
}

template<typename... Ts>
SQL::Insert Tuple::storeQuery(const PolymorphicType<SQL::TableName>& table, const std::vector<std::tuple<Ts...>>& tuples)
{
    auto query = SQL::Query::insert().into(*table);
    for (auto tuple : tuples) {
        query.addValues(tupleToLiterals(tuple));
    }
    return query;
}


/*******************/
/* store functions */
/*******************/

template<typename... Ts>
void Tuple::store(const PolymorphicType<SQL::TableName>& table, const std::tuple<Ts...>& tuple)
{
    _backend->query(storeQuery<Ts...>(table, tuple));
}

template<typename... Ts>
Tuple::count Tuple::store(const PolymorphicType<SQL::TableName>& table, const std::tuple<std::vector<Ts>...>& vectors)
{
    return _backend->query(storeQuery<Ts...>(table, vectors));
}

template<typename... Ts>
Tuple::count Tuple::store(const PolymorphicType<SQL::TableName>& table, const std::vector<std::tuple<Ts...>>& tuples)
{
    return _backend->query(storeQuery<Ts...>(table, tuples));
}


/*****************************/
/* store or update functions */
/*****************************/

template<typename... Ts>
void Tuple::store(const PolymorphicType<SQL::TableName>& table, const SQL::List<SQL::ColumnName> columns, const std::tuple<Ts...>& tuple)
{
    _backend->query(storeQuery(table, tuple)
            .columnNames(columns)
            .orUpdate()
        );
}

template<typename... Ts>
Tuple::count Tuple::store(const PolymorphicType<SQL::TableName>& table, const SQL::List<SQL::ColumnName> columns, const std::tuple<std::vector<Ts>...>& vectors)
{
    return _backend->query(storeQuery(table, vectors)
            .columnNames(columns)
            .orUpdate()
        );
}

template<typename... Ts>
Tuple::count Tuple::store(const PolymorphicType<SQL::TableName>& table, const SQL::List<SQL::ColumnName> columns, const std::vector<std::tuple<Ts...>>& tuples)
{
    return _backend->query(storeQuery(table, tuples)
            .columnNames(columns)
            .orUpdate()
        );
}

}
