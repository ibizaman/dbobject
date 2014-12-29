#ifndef DBOBJECT_SQL_LITERAL_H
#define DBOBJECT_SQL_LITERAL_H

#include <string>
#include "SimpleExpr.h"
#include "polymorph/PolymorphicType.hxx"
#include "lib/typeconverter/TypeConverter.h"
#include "lib/Datetime.h"

namespace dbobject {
namespace SQL {

class Literal : public SimpleExpr
{
public:
    template<typename T>
    Literal(T);
    Literal(const std::string&);
    Literal(const char*);
    Literal(const datetime::Date&);
    Literal(const datetime::Datetime&);
};

template<typename T>
class ValueLiteral : public Literal
{
public:
    ValueLiteral(const T&);
    void setValue(const T&);
    T value() const;

private:
    T _typedValue;
};

typedef ValueLiteral<int> IntLiteral;

namespace Operators {
IntLiteral& operator-(IntLiteral&);
Literal operator"" _l(char const*, std::size_t);
ValueLiteral<unsigned long long> operator"" _l(unsigned long long);
ValueLiteral<long double> operator"" _l(long double);
}

}
}

#include "Literal.hpp"

#endif
