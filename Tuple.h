#ifndef DBOBJECT_TUPLE_H
#define DBOBJECT_TUPLE_H

#include <memory>
#include <tuple>
#include <vector>
#include "backends/Backend.h"
#include "query/Select.h"
#include "query/Insert.h"
#include "query/Update.h"

namespace dbobject {

/*
 * Stores a tuple of vectors, each vector is a column.
 */
template<typename T> struct TupleOfVectors;

template<typename... Ts> struct TupleOfVectors<std::tuple<Ts...>>
{
    typedef std::tuple<std::vector<Ts>...> type;
};

/*
 * Stores a vector of tuples, each tuple is an object.
 */
template<typename T> struct VectorOfTuples;

template<typename... Ts> struct VectorOfTuples<std::tuple<Ts...>>
{
    typedef std::vector<std::tuple<Ts...>> type;
};

class Tuple
{
public:
    typedef Backend::count count;

    Tuple(std::shared_ptr<Backend>);
    void setBackend(std::shared_ptr<Backend>);

    /*
     * Provide passthrough to backend functions
     */
    std::shared_ptr<sql::ResultSet> query(const SQL::Select&);
    count query(const SQL::Insert&);
    count query(const SQL::Update&);

    /*
     * Retrieval of one tuple
     */
    template<typename T> T getOne(const SQL::Select&);
    template<typename T> T getOne(const SQL::TableName&, const SQL::Expression&);
    template<typename T> T getOne(const SQL::TableName&, const SQL::List<SQL::SimpleExpr>&, const SQL::Expression&);

    /*
     * Retrieval of multiple tuples, each corresponding to one query row
     */
    template<typename T> typename VectorOfTuples<T>::type getAsTuples(const SQL::Select&);
    template<typename T> typename VectorOfTuples<T>::type getAsTuples(const SQL::TableName&);
    template<typename T> typename VectorOfTuples<T>::type getAsTuples(const SQL::TableName&, const SQL::Expression&);
    template<typename T> typename VectorOfTuples<T>::type getAsTuples(const SQL::TableName&, const SQL::List<SQL::SimpleExpr>&);
    template<typename T> typename VectorOfTuples<T>::type getAsTuples(const SQL::TableName&, const SQL::List<SQL::SimpleExpr>&, const SQL::Expression&);

    /*
     * Retreival of multiple vectors, each corresponding to one query column
     */
    template<typename T> typename TupleOfVectors<T>::type getAsVectors(const SQL::Select&);
    template<typename T> typename TupleOfVectors<T>::type getAsVectors(const SQL::TableName&);
    template<typename T> typename TupleOfVectors<T>::type getAsVectors(const SQL::TableName&, const SQL::Expression&);
    template<typename T> typename TupleOfVectors<T>::type getAsVectors(const SQL::TableName&, const SQL::List<SQL::SimpleExpr>&);
    template<typename T> typename TupleOfVectors<T>::type getAsVectors(const SQL::TableName&, const SQL::List<SQL::SimpleExpr>&, const SQL::Expression&);

    /*
     * Store new tuples
     */
    template<typename... Ts> void store(const PolymorphicType<SQL::TableName>&, const std::tuple<Ts...>&);
    // cannot user TupleOfVectors<std::tuple<Ts...>>::type for 2nd argument
    // since it would result in a non deduced context
    // i.e. type deduction works only forward
    template<typename... Ts> count store(const PolymorphicType<SQL::TableName>&, const std::tuple<std::vector<Ts>...>&);
    template<typename... Ts> count store(const PolymorphicType<SQL::TableName>&, const std::vector<std::tuple<Ts...>>&);

    /*
     * Indifferently store new tuples or update existing tuples
     */
    template<typename... Ts> void store(const PolymorphicType<SQL::TableName>&, const SQL::List<SQL::SimpleExpr>, const std::tuple<Ts...>&);
    template<typename... Ts> count store(const PolymorphicType<SQL::TableName>&, const SQL::List<SQL::SimpleExpr>, const std::tuple<std::vector<Ts>...>&);
    template<typename... Ts> count store(const PolymorphicType<SQL::TableName>&, const SQL::List<SQL::SimpleExpr>, const std::vector<std::tuple<Ts...>>&);

private:
    std::shared_ptr<Backend> _backend;

    /*
     * Empty structure needed to expand tuple Args...
     */
    template<typename T> struct type_tag {};

    /*
     * Helper functions for getOne().
     * Transform a ResultSet into a Tuple
     */
    template<int I>
        std::tuple<> getOne(std::shared_ptr<sql::ResultSet>);
    template<int I, typename T, typename... Rest>
        std::tuple<T, Rest...> getOne(std::shared_ptr<sql::ResultSet>);
    template<typename... Ts>
        std::tuple<Ts...> getOne(std::shared_ptr<sql::ResultSet>,type_tag<std::tuple<Ts...>>);

    /*
     * Helper functions for getAsTuples().
     * Transform a ResultSet into a VectorOfTuples
     */
    template<typename T>
    typename VectorOfTuples<T>::type getAsTuples(std::shared_ptr<sql::ResultSet>);

    /*
     * Helper functions for getAsVectors().
     * Transform a ResultSet into a TupleOfVectors
     */
    template<int I>
        std::tuple<>
        getAsVectors(std::shared_ptr<sql::ResultSet>);
    template<int I, typename T, typename... Rest>
        typename TupleOfVectors<std::tuple<T, Rest...>>::type
        getAsVectors(std::shared_ptr<sql::ResultSet>);
    template<typename... Ts>
        typename TupleOfVectors<std::tuple<Ts...>>::type
        getAsVectors(std::shared_ptr<sql::ResultSet>, type_tag<std::tuple<Ts...>>);

    /*
     * Helper functions for store().
     */
    // Transform a tuple into a list of literals
    template<typename Tup, int I>
        auto tupleToLiterals(const Tup&) const
        -> typename std::enable_if<I == std::tuple_size<Tup>::value, SQL::List<SQL::Literal>>::type;
    template<typename Tup, int I = 0>
        auto tupleToLiterals(const Tup&) const
        -> typename std::enable_if<I != std::tuple_size<Tup>::value, SQL::List<SQL::Literal>>::type;

    // Transform a tuple of vectors' row into a list of literals
    template<typename TupleOfVectors, int I>
        auto tupleOfVectorsRowToLiterals(const TupleOfVectors&, size_t) const
        -> typename std::enable_if<I == std::tuple_size<TupleOfVectors>::value, SQL::List<SQL::Literal>>::type;
    template<typename TupleOfVectors, int I = 0>
        auto tupleOfVectorsRowToLiterals(const TupleOfVectors&, size_t) const
        -> typename std::enable_if<I != std::tuple_size<TupleOfVectors>::value, SQL::List<SQL::Literal>>::type;

    // Queries to insert
    template<typename... Ts> SQL::Insert storeQuery(const PolymorphicType<SQL::TableName>&, const std::tuple<Ts...>&);
    template<typename... Ts> SQL::Insert storeQuery(const PolymorphicType<SQL::TableName>&, const std::tuple<std::vector<Ts>...>&);
    template<typename... Ts> SQL::Insert storeQuery(const PolymorphicType<SQL::TableName>&, const std::vector<std::tuple<Ts...>>&);
};

}

#include "Tuple.hpp"

#endif
