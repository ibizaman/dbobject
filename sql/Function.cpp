#include "Function.h"

dbobject::SQL::Count::Count()
    : SimpleExpr("COUNT(*)")
{
}

dbobject::SQL::Count::Count(const dbobject::PolymorphicType<dbobject::SQL::SimpleExpr>& expr)
    : SimpleExpr(std::string("COUNT(") + (*expr)() + ")")
{
}

