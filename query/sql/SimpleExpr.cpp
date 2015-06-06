#include "SimpleExpr.h"

namespace dbobject {
namespace SQL {

SimpleExpr::SimpleExpr()
{
}

SimpleExpr::SimpleExpr(const std::string& value)
    : _value(value)
{
}

std::string SimpleExpr::operator()() const
{
    return _value;
}

}
}
