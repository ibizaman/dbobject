#pragma once

#include "ColumnName.h"
#include "polymorph/PolymorphicType.hxx"

namespace dbobject {
namespace SQL {

class Count : public SimpleExpr
{
public:
    Count();
    Count(const PolymorphicType<SimpleExpr>&);
};

}
}

