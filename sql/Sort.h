#ifndef DBOBJECT_SQL_SORT_H
#define DBOBJECT_SQL_SORT_H

#include "ColumnName.h"

namespace dbobject {
namespace SQL {

enum Direction {ASC, DESC};

template<typename T> class Sort;

template<>
class Sort<ColumnName> : public ColumnName
{
public:
    Sort(const ColumnName&, const Direction& = ASC);
    virtual std::string operator()() const override;
private:
    Direction _direction;
};

namespace Operators {
template<typename T>
Sort<T> operator|(const T&, const Direction&);
}

}
}

#include "Sort.hpp"

#endif
