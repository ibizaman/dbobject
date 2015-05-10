#ifndef DBOBJECT_SQL_EXPRESSION_H
#define DBOBJECT_SQL_EXPRESSION_H

#include "Clause.h"
#include "ColumnName.h"
#include "List.h"
#include "SimpleExpr.h"

namespace dbobject {
namespace SQL {

class Expression : public Clause
{
public:
    Expression();
    Expression(const std::string&);
    std::string operator()() const;
    bool empty() const;

private:
    std::string _expression;
};

namespace Operators {

/*
 * Operators
 * See : http://dev.mysql.com/doc/refman/5.0/en/comparison-operators.html
 */
Expression between(const SimpleExpr&, const SimpleExpr&, const SimpleExpr&);
Expression coalesce(const List<SimpleExpr>&);
Expression nullSafeEqual(const SimpleExpr&, const SimpleExpr&);
Expression operator>=(const SimpleExpr&, const SimpleExpr&);
Expression operator>(const SimpleExpr&, const SimpleExpr&);
Expression greatest(const List<SimpleExpr>&);
Expression in(const ColumnName&, const List<SimpleExpr>&);
Expression interval(const List<SimpleExpr>&);
Expression isNull(const SimpleExpr&);
Expression operator==(bool, const SimpleExpr&); // IS operator
Expression operator==(const SimpleExpr&, bool);
Expression least(const List<SimpleExpr>&);
Expression operator<=(const SimpleExpr&, const SimpleExpr&);
Expression operator<(const SimpleExpr&, const SimpleExpr&);
//Expression like(const SimpleExpr&, const LikeLiteral&);
Expression operator!=(const SimpleExpr&, const SimpleExpr&);

/*
 * Expression mixers
 * See : http://dev.mysql.com/doc/refman/5.0/en/expressions.html
 */
Expression operator||(const Expression&, const Expression&);
Expression operator^(const Expression&, const Expression&);
Expression operator&&(const Expression&, const Expression&);
Expression operator!(const Expression&);

}

}
}

#endif
