#ifndef DBOBJECT_SQL_COLUMNNAME_H
#define DBOBJECT_SQL_COLUMNNAME_H

#include "SimpleExpr.h"
#include "TableName.h"
#include "polymorph/Delayed.hxx"
#include "polymorph/PolymorphicType.hxx"

namespace dbobject {
namespace SQL {

class ColumnName : public SimpleExpr
{
public:
    ColumnName(const PolymorphicType<SimpleExpr>&);
    ColumnName(const PolymorphicType<TableName>&, const PolymorphicType<SimpleExpr>&);
    ColumnName(const PolymorphicType<SchemaName>&, const PolymorphicType<SimpleExpr>&, const PolymorphicType<SimpleExpr>&);
    void setSchema(const PolymorphicType<SchemaName>&);
    void setTable(const PolymorphicType<TableName>&);
    void setTable(const std::string&);
    virtual std::string schema() const;
    virtual std::string table() const;
    virtual bool hasSchema() const;
    virtual bool hasTable() const;
    std::string name() const;
    std::string operator()() const override;
private:
    Delayed<PolymorphicType<TableName>> _table;
};

namespace Operators {
ColumnName operator"" _c(char const*, std::size_t);
ColumnName operator/(const TableName&, ColumnName);
}

}
}

#endif
