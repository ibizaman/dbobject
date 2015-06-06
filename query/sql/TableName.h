#ifndef DBOBJECT_SQL_TABLENAME_H
#define DBOBJECT_SQL_TABLENAME_H

#include "SchemaName.h"
#include "SimpleExpr.h"
#include "polymorph/Delayed.hxx"
#include "polymorph/PolymorphicType.hxx"

namespace dbobject {
namespace SQL {

class TableName : public Clause
{
public:
    TableName(const PolymorphicType<SimpleExpr>&);
    TableName(const PolymorphicType<SchemaName>&, const PolymorphicType<SimpleExpr>&);
    void setSchema(const PolymorphicType<SchemaName>&);
    virtual std::string schema() const;
    virtual bool hasSchema() const;
    std::string name() const;
    std::string operator()() const override;
private:
    Delayed<PolymorphicType<SchemaName>> _schema;
    std::string _table;
};

namespace Operators {
TableName operator"" _t(char const*, std::size_t);
TableName operator/(const SchemaName&, TableName);
}

}
}

#endif
