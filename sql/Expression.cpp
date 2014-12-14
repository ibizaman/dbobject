#include "Expression.h"

namespace dbobject {
namespace SQL {

Expression::Expression()
{
}

Expression::Expression(const std::string& expression)
    : _expression(expression)
{
}

std::string Expression::operator()() const
{
    return _expression;
}

bool Expression::empty() const
{
    return _expression.empty();
}

namespace Operators {

Expression between(const SimpleExpr& v, const SimpleExpr& left, const SimpleExpr& right)
{
    return Expression(v() + " BETWEEN " + left() + " AND " + right());
}

Expression coalesce(const List<SimpleExpr>& list)
{
    return Expression("COALESCE("+list()+")");
}

Expression nullSafeEqual(const SimpleExpr& left, const SimpleExpr& right)
{
    return Expression(left() + "<=>" + right());
}

Expression operator>=(const SimpleExpr& left, const SimpleExpr& right)
{
    return Expression(left() + ">=" + right());
}

Expression operator>(const SimpleExpr& left, const SimpleExpr& right)
{
    return Expression(left() + ">" + right());
}

Expression greatest(const List<SimpleExpr>& list)
{
    return Expression("GREATEST("+list()+")");
}

Expression in(const List<SimpleExpr>& list)
{
    return Expression("IN("+list()+")");
}

Expression interval(const List<SimpleExpr>& list)
{
    return Expression("INTERVAL("+list()+")");
}

Expression isNull(const SimpleExpr& value)
{
    return Expression(value() + " IS NULL");
}

Expression operator==(const bool& boolean, const SimpleExpr& value)
{
    return Expression(value() + " IS " + (boolean ? "TRUE" : "FALSE"));
}

Expression operator==(const SimpleExpr& value, const bool& boolean)
{
    return Expression(value() + " IS " + (boolean ? "TRUE" : "FALSE"));
}

Expression least(const List<SimpleExpr>& list)
{
    return Expression("LEAST("+list()+")");
}

Expression operator<=(const SimpleExpr& left, const SimpleExpr& right)
{
    return Expression(left() + "<=" + right());
}

Expression operator<(const SimpleExpr& left, const SimpleExpr& right)
{
    return Expression(left() + "<" + right());
}

Expression like(const SimpleExpr& value, const std::string& like)
{
    return Expression(value() + " LIKE " + like);
}

Expression operator!=(const SimpleExpr& left, const SimpleExpr& right)
{
    return Expression(left() + "<>" + right());
}

/*
 * Expression mixers
 */
Expression operator||(const Expression& left, const Expression& right)
{
    auto l = left();
    auto r = right();
    if (l.empty()) {
        return right;
    } else if (r.empty()) {
        return left;
    } else {
        return Expression(left() + " OR " + right());
    }
}

Expression operator^(const Expression& left, const Expression& right)
{
    auto l = left();
    auto r = right();
    if (l.empty()) {
        return right;
    } else if (r.empty()) {
        return left;
    } else {
        return Expression(left() + " XOR " + right());
    }
}

Expression operator&&(const Expression& left, const Expression& right)
{
    auto l = left();
    auto r = right();
    if (l.empty()) {
        return right;
    } else if (r.empty()) {
        return left;
    } else {
        return Expression(left() + " AND " + right());
    }
}

Expression operator!(const Expression& expr)
{
    return Expression("NOT " + expr());
}

}

}
}
