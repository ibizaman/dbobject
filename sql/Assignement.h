#ifndef DBOBJECT_SQL_ASSIGNEMENT_H
#define DBOBJECT_SQL_ASSIGNEMENT_H

#include "Expression.h"
#include "SimpleExpr.h"
#include "polymorph/PolymorphicType.hxx"

namespace dbobject {
namespace SQL {

template<typename Left, typename Right, typename Enable = void>
class Assignement;

namespace AssignementImpl {

/*
 * If pod, simply return the variable, if class, returns operator()()
 */

template<typename Base, typename Type>
auto print(const Type&) -> typename std::enable_if<std::is_base_of<PolymorphicType<Base>, Type>::value, std::string>::type;

template<typename Base, typename Type>
auto print(const Type&) -> typename std::enable_if<std::is_base_of<Base, Type>::value, Type>::std::string;

template<typename Base, typename Type>
auto print(const Type&) -> typename std::enable_if<!std::is_base_of<PolymorphicType<Base>, Type>::value && !std::is_base_of<Base, Type>::value, std::string>::type;

}

/*
 * Class enabled only if Left and Right can be "both_convertible_to"
 * a SimpleExpr
 */
template<typename Left, typename Right>
class Assignement<Left, Right>
    : public Expression
{
public:
    template<typename L, typename R>
    Assignement(const L&, const R&);
    template<typename L, typename R>
    Assignement(const Assignement<L, R>&);
    PolymorphicType<Left> left() const;
    PolymorphicType<Right> right() const;
private:
    PolymorphicType<Left> _left;
    PolymorphicType<Right> _right;
};

namespace Operators {
Assignement<SimpleExpr, SimpleExpr> operator==(const PolymorphicType<SimpleExpr>&, const PolymorphicType<SimpleExpr>&);
}

}
}

#include "Assignement.hpp"

#endif
