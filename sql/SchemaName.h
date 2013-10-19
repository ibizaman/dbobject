#ifndef DBOBJECT_SQL_SCHEMANAME_H
#define DBOBJECT_SQL_SCHEMANAME_H

#include "Clause.h"
#include "SimpleExpr.h"
#include "polymorph/PolymorphicType.hxx"

namespace dbobject {
namespace SQL {

class SchemaName : public Clause
{
public:
    SchemaName(const PolymorphicType<SimpleExpr>&);
    std::string operator()() const override;
private:
    std::string _schema;
};

namespace Operators {
SchemaName operator"" _s(char const*, std::size_t);
}

}
}

#endif
