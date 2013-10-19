#include "Assignement.h"

namespace dbobject {
namespace SQL {
namespace Operators {
    
Assignement<SimpleExpr, SimpleExpr> operator==(const PolymorphicType<SimpleExpr>& left, const PolymorphicType<SimpleExpr>& right)
{
    return Assignement<SimpleExpr, SimpleExpr>(left, right);
}

}
}
}
