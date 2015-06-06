#ifndef DOBJECT_SQL_JOIN_H
#define DOBJECT_SQL_JOIN_H

#include "Assignement.h"
#include "Clause.h"
#include "ColumnName.h"
#include "JoinedTable.h"
#include "polymorph/PolymorphicType.hxx"

namespace dbobject {
namespace SQL {

class Join : public Clause
{
public:
    typedef Assignement<ColumnName,ColumnName> On;

    Join(const PolymorphicType<JoinedTable>&, const On&);
    std::string operator()() const override;

private:
    PolymorphicType<JoinedTable> _table;
    On _on;
};

}
}

#endif
