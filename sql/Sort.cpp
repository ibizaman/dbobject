#include "Sort.h"

namespace dbobject {
namespace SQL {

Sort<ColumnName>::Sort(const ColumnName& name, const Direction& direction)
    : ColumnName(name),
      _direction(direction)
{
}

std::string Sort<ColumnName>::operator()() const
{
    return ColumnName::operator()() + (_direction == DESC ? " DESC" : "");
}

}
}
