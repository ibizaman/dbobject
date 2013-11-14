#include "Insert.h"
#include "functional/MapHelper.hxx"
#include "functional/VectorHelper.hxx"

namespace dbobject {
namespace SQL {

std::string Insert::zipColumnNameLiteral(const List<ColumnName>& columns, const List<Literal>& values) const
{
    auto columnStrings = VectorHelper::map(columns, std::mem_fn(&ColumnName::operator()));
    auto valueStrings = VectorHelper::map(values, std::mem_fn(&Literal::operator()));
    return MapHelper::concat(MapHelper::zip(columnStrings.begin(), columnStrings.end(), valueStrings.begin(), valueStrings.end()), " = ", ", ");
}

std::string Insert::getSQL() const
{
    std::string sql;

    if (!_into.initialized()) {
        throw malformed_sql("Insert query malformed, no table defined : " + sql);
    }
    sql += "INSERT INTO " + (*_into.get())();

    if (_values.size() < 1) {
        throw malformed_sql("Insert query malformed, no values to insert : " + sql);
    }

    if (_columns.initialized() && _values.size() == 1) {
        sql += " SET " + zipColumnNameLiteral(_columns.get(), _values.at(0));
    } else {
        if (_columns.initialized()) {
            sql += "(" + _columns.get()() + ")";
        }
        sql += " VALUES ";
        for (auto value : _values) {
            sql += "(" + value() + "), ";
        }
        sql.erase(sql.end()-2, sql.end());
    }
    
    if (_onDuplicate.initialized()) {
        sql += " ON DUPLICATE KEY UPDATE ";
        if (!_onDuplicate.get().empty()) {
            sql += _onDuplicate.get()(); 
        } else if (_columns.initialized()) {
            for (auto column : _columns.get()) {
                sql += (*column)() + " = VALUES(" + (*column)() + "), ";
            }
            sql.erase(sql.end()-2, sql.end());
        } else {
            throw malformed_sql("Insert query malformed, cannot use 'orUpdate' if no columns are defined : " + sql);
        }
    }

    return sql;
}

Insert& Insert::insert(const List<ColumnAssignement>& insert)
{
    _columns.get().clear();
    _values.clear();

    List<Literal> valueList;
    for (auto columnAssignement : insert) {
        _columns.get().push_back(columnAssignement->left());
        valueList.push_back(columnAssignement->right());
    }

    _values.push_back(valueList);
    return *this;
}

Insert& Insert::columnNames(const List<ColumnName>& columns)
{
    _columns = columns;
    return *this;
}

Insert& Insert::addValues(const List<Literal>& values)
{
    _values.push_back(values);
    return *this;
}

Insert& Insert::into(const PolymorphicType<TableName>& into)
{
    _into = into;
    return *this;
}

Insert& Insert::orUpdate()
{
    return orUpdate(List<ColumnAssignement>());
}

Insert& Insert::orUpdate(const List<ColumnAssignement>& onDuplicate)
{
    _onDuplicate = onDuplicate;
    return *this;
}

}
}
