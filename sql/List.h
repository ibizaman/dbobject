#ifndef DBOBJECT_SQL_LIST_H
#define DBOBJECT_SQL_LIST_H

#include <vector>
#include "Clause.h"
#include "polymorph/PolymorphicType.hxx"

namespace dbobject {
namespace SQL {

template<typename T>
class List : public Clause, public std::vector<PolymorphicType<T>>
{
public:
    using std::vector<PolymorphicType<T>>::vector;
    std::string operator()() const override;

private:
    typedef std::vector<PolymorphicType<T>> V;
};

}
}

#include "List.hpp"

#endif
