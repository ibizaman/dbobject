#ifndef DBOBJECT_SQL_LITERAL_H
#define DBOBJECT_SQL_LITERAL_H

#include <string>
#include "SimpleExpr.h"
#include "polymorph/PolymorphicType.hxx"

namespace dbobject {
namespace SQL {

class Literal : public SimpleExpr
{
public:
    template<typename T>
    Literal(T);
};

class IntLiteral : public Literal
{
public:
    IntLiteral(int);
    void setValue(int);
    int value() const;
private:
    int _int;
};

namespace Operators {
IntLiteral& operator-(IntLiteral&);
Literal operator"" _l(char const*, std::size_t);
IntLiteral operator"" _l(unsigned long long);
Literal operator"" _l(long double);
}

}
}

#include "Literal.hpp"

#endif
