#include "JoinedTable.h"

namespace dbobject {
namespace SQL {

JoinedTable::JoinedTable(const PolymorphicType<TableName>& table, const JoinType& joinType)
    : _table(table),
      _joinType(joinType)
{
}

std::string JoinedTable::table() const
{
    return _table->name();
}

JoinedTable::JoinType JoinedTable::joinType() const
{
    return _joinType;
}

std::string JoinedTable::operator()() const
{
    std::string sql;
    switch(_joinType) {
        case INNER:
            sql += "JOIN ";
            break;
        case LEFT:
            sql += "LEFT JOIN ";
            break;
        case RIGHT:
            sql += "RIGHT JOIN ";
            break;
    }
    sql += (*_table)();
    return sql;
}

namespace Operators {

JoinedTable operator|(const PolymorphicType<TableName>& table, const JoinedTable::JoinType& joinType)
{
    return JoinedTable(table, joinType);
}

}

}
}
