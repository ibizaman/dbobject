#include "Literal.h"
#include "polymorph/TypeConverter.h"

namespace dbobject {
namespace SQL {

template<>
Literal::Literal(std::string value)
    : SimpleExpr('\''+value+'\'')
{
}

template<>
Literal::Literal(const char* value)
    : SimpleExpr('\''+std::string(value)+'\'')
{
}

template<>
Literal::Literal(SimpleExpr value)
    : SimpleExpr(TypeConverter::toString(value))
{
}

template<>
Literal::Literal(int value)
    : SimpleExpr(TypeConverter::toString(value))
{
}

template<>
Literal::Literal(double value)
    : SimpleExpr(TypeConverter::toString(value))
{
}

template<>
Literal::Literal(bool value)
    : SimpleExpr(TypeConverter::toString(value))
{
}

template<>
Literal::Literal(IntLiteral value)
    : SimpleExpr(TypeConverter::toString(value._value))
{
}

IntLiteral::IntLiteral(int value)
    : Literal(value),
      _int(value)
{
}

void IntLiteral::setValue(int value)
{
    _int = value;
    _value = TypeConverter::toString(value);
}

int IntLiteral::value() const
{
    return _int;
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

IntLiteral operator"" _l(unsigned long long value)
{
    return IntLiteral(static_cast<int>(value));
}

Literal operator"" _l(long double value)
{
    return Literal(static_cast<double>(value));
}

}

}
}
