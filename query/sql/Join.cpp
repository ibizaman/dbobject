#include "Join.h"

namespace dbobject {
namespace SQL {

Join::Join(const PolymorphicType<JoinedTable>& table, const On& on)
    : _table(table),
      _on(on)
{
}

std::string Join::operator()() const
{
    return (*_table)() + " ON " + _on();
}

}
}
