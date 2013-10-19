#ifndef DBOBJECT_SQL_JOINEDTABLE_H
#define DBOBJECT_SQL_JOINEDTABLE_H

#include "Clause.h"
#include "TableName.h"
#include "polymorph/PolymorphicType.hxx"

namespace dbobject {
namespace SQL {

class JoinedTable : public Clause
{
public:
    enum JoinType {INNER, LEFT, RIGHT};
    JoinedTable(const PolymorphicType<TableName>&, const JoinType& = LEFT);
    std::string table() const;
    JoinType joinType() const;
    std::string operator()() const override;
private:
    PolymorphicType<TableName> _table;
    JoinType _joinType;
};

namespace Operators {
JoinedTable operator|(const PolymorphicType<TableName>& table, const JoinedTable::JoinType& joinType);
}

}
}

#endif
