#include "Select.h"

namespace dbobject {
namespace SQL {

std::string Select::getSQL() const
{
    std::string sql;

    try {

        sql += "SELECT ";
        if (_distinct.initialized()) {
            sql += "DISTINCT ";
        }
        if (!_columns.initialized()) {
            sql += "*";
        } else {
            sql += _columns.get()();
        }

        sql += " FROM " + (*_from.get())();

        if (!_joins.empty()) {
            sql += " JOIN " + _joins();
        }

        if (_where.initialized() && !(*_where.get()).empty()) {
            sql += " WHERE " + (*_where.get())();
        }

        if (!_groupBy.empty()) {
            sql += " GROUP BY " + _groupBy();
        }

        if (_having.initialized()) {
            sql += " HAVING " + (*_having.get())();
        }

        if (!_orderBy.empty()) {
            sql += " ORDER BY " + _orderBy();
        }

        if (_limit_row_count.initialized()) {
            sql += " LIMIT ";
            if (_limit_offset.initialized()) {
                sql += (_limit_offset.get())() + ", ";
            }
            sql += (_limit_row_count.get())();
        }

    } catch(non_initialized_optional&) {
        throw malformed_sql("Select query malformed : " + sql);
    }

    return sql;
}

Select& Select::select()
{
    _columns = List<ColumnName>();
    return *this;
}

Select& Select::select(const List<ColumnName>& columns)
{
    _columns = columns;
    return *this;
}

Select& Select::from(const PolymorphicType<TableName>& from)
{
    _from = from;
    return *this;
}

Select& Select::join(const List<Join>& joins)
{
    _joins = joins;
    return *this;
}

Select& Select::distinct(bool distinct)
{
    _distinct = distinct;
    return *this;
}

Select& Select::where(const PolymorphicType<Expression>& where)
{
    _where = where;
    return *this;
}

Select& Select::groupBy(const List<GroupBy>& groupBy)
{
    _groupBy = groupBy;
    return *this;
}

Select& Select::having(const PolymorphicType<Expression>& having)
{
    _having = having;
    return *this;
}

Select& Select::orderBy(const List<OrderBy>& orderBy)
{
    _orderBy = orderBy;
    return *this;
}

Select& Select::limit(unsigned int limit_row_count)
{
    _limit_row_count = limit_row_count;
    return *this;
}

Select& Select::limit(unsigned int limit_offset, unsigned int limit_row_count)
{
    _limit_offset = limit_offset;
    _limit_row_count = limit_row_count;
    return *this;
}

}
}
