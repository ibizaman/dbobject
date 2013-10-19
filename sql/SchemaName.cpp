#include "SchemaName.h"

namespace dbobject {
namespace SQL {

SchemaName::SchemaName(const PolymorphicType<SimpleExpr>& schema)
    : _schema((*schema)())
{
}

std::string SchemaName::operator()() const
{
    return '`'+_schema+'`';
}

namespace Operators {

SchemaName operator"" _s(char const* str, std::size_t)
{
    return SchemaName(str);
}

}

}
}
