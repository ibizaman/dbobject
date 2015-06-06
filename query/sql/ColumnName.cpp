#include "ColumnName.h"

namespace dbobject {
namespace SQL {

ColumnName::ColumnName(const PolymorphicType<SimpleExpr>& column)
    : SimpleExpr(*column)
{
}

ColumnName::ColumnName(const PolymorphicType<TableName>& table, const PolymorphicType<SimpleExpr>& column)
    : SimpleExpr(*column),
      _table(table)
{
}

ColumnName::ColumnName(const PolymorphicType<SchemaName>& schema, const PolymorphicType<SimpleExpr>& table, const PolymorphicType<SimpleExpr>& column)
    : SimpleExpr(*column),
      _table(TableName(schema, table))
{
}

void ColumnName::setSchema(const PolymorphicType<SchemaName>& schema)
{
    (*_table.get()).setSchema(schema);
}

void ColumnName::setTable(const PolymorphicType<TableName>& table)
{
    _table.set(table);
}

std::string ColumnName::schema() const
{
    return (*_table.get()).schema();
}

bool ColumnName::hasSchema() const
{
    if (!hasTable()) {
        return false;
    } else {
        return (*_table.get()).hasSchema();
    }
}

std::string ColumnName::table() const
{
    return (*_table.get()).name();
}

bool ColumnName::hasTable() const
{
    return _table.initialized();
}

std::string ColumnName::name() const
{
    return '`' + _value + '`';
}

std::string ColumnName::operator()() const
{
    if (!hasTable()) {
        return name();
    } else {
        return (*_table.get())() + "." + name();
    }
}

namespace Operators {

ColumnName operator"" _c(char const* str, std::size_t)
{
    return ColumnName(str);
}

ColumnName operator/(const TableName& table, ColumnName column)
{
    column.setTable(table);
    return column;
}

}

}
}
