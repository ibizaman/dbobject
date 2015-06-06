#ifndef DBOBJECT_SQL_SIMPLEEXPR_H
#define DBOBJECT_SQL_SIMPLEEXPR_H

#include "Clause.h"

namespace dbobject {
namespace SQL {

class SimpleExpr : public Clause
{
public:
    SimpleExpr();
    SimpleExpr(const std::string&);
    virtual std::string operator()() const override;

protected:
    std::string _value;
};

}
}

#endif
