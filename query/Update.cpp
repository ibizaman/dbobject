#include "Update.h"

namespace dbobject {
namespace SQL {

std::string Update::getSQL() const
{
    std::string sql;

    try {

        sql += "UPDATE " + (*_update.get())() + " SET " + _set.get()();

        if (_where.initialized()) {
            sql += " WHERE " + (*_where.get())();
        }

        if (!_orderBy.empty()) {
            sql += " ORDER BY " + _orderBy();
        }

        if (_limit.initialized()) {
            sql += " LIMIT " + (_limit.get())();
        }

    } catch(non_initialized_optional&) {
        throw malformed_sql("Update query malformed");
    }

    return sql;
}

Update& Update::update(const PolymorphicType<TableName>& update)
{
    _update = update;
    return *this;
}

Update& Update::set(const List<ColumnAssignement>& set)
{
    _set = set;
    return *this;
}

Update& Update::where(const PolymorphicType<Expression>& where)
{
    _where = where;
    return *this;
}

Update& Update::orderBy(const List<OrderBy>& orderBy)
{
    _orderBy = orderBy;
    return *this;
}

Update& Update::limit(int limit)
{
    _limit = limit;
    return *this;
}

}
}

