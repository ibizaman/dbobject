#include "Literal.h"

namespace dbobject {
namespace SQL {

Literal::Literal(const std::string& value)
    : SimpleExpr('\''+value+'\'')
{
}

Literal::Literal(const char* value)
    : SimpleExpr('\''+std::string(value)+'\'')
{
}

Literal::Literal(const datetime::Date& value)
    : SimpleExpr('\''+TypeConverter::toString(value)+'\'')
{
}

Literal::Literal(const datetime::Datetime& value)
    : SimpleExpr('\''+TypeConverter::toString(value)+'\'')
{
}

namespace Operators {

IntLiteral& operator-(IntLiteral& literal)
{
    literal.setValue(-literal.value());
    return literal;
}

Literal operator"" _l(char const* str, std::size_t)
{
    return Literal(str);
}

ValueLiteral<unsigned long long> operator"" _l(unsigned long long value)
{
    return ValueLiteral<unsigned long long>(value);
}

ValueLiteral<long double> operator"" _l(long double value)
{
    return ValueLiteral<long double>(value);
}

}

}
}
