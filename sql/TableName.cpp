#include "TableName.h"

namespace dbobject {
namespace SQL {

TableName::TableName(const PolymorphicType<SimpleExpr>& table)
    : _table((*table)())
{
}

TableName::TableName(const PolymorphicType<SchemaName>& schema, const PolymorphicType<SimpleExpr>& table)
    : _schema(schema),
      _table((*table)())
{
}

void TableName::setSchema(const PolymorphicType<SchemaName>& schema)
{
    _schema.set(schema);
}

std::string TableName::schema() const
{
    return (*_schema.get())();
}

bool TableName::hasSchema() const
{
    return _schema.initialized();
}

std::string TableName::name() const
{
    return '`' + _table + '`';
}

std::string TableName::operator()() const
{
    if (!hasSchema()) {
        return name();
    } else {
        return (*_schema.get())() + "." + name();
    }
}

namespace Operators {

TableName operator"" _t(char const* str, std::size_t)
{
    return TableName(str);
}

TableName operator/(const SchemaName& schema, TableName table)
{
    table.setSchema(schema);
    return table;
}

}

}
}
