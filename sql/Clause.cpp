#include "Clause.h"

namespace dbobject {
namespace SQL {

std::ostream& operator<<(std::ostream& out, const Clause& clause)
{
    out << clause();
    return out;
}

}
}
