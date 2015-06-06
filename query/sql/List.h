#ifndef DBOBJECT_SQL_LIST_H
#define DBOBJECT_SQL_LIST_H

#include <vector>
#include <initializer_list>
#include "Clause.h"
#include "polymorph/PolymorphicType.hxx"

namespace dbobject {
namespace SQL {

template<typename T>
class List : public Clause
{
public:
    typedef typename std::vector<PolymorphicType<T>>::iterator iterator;
    typedef typename std::vector<PolymorphicType<T>>::const_iterator const_iterator;

    List();
    List(std::initializer_list<PolymorphicType<T>>);
    template<typename U> List(const std::vector<U>&);
    template<typename U> List(const List<U>&);

    std::string operator()() const override;

    void insert(const_iterator, const T&);
    template<typename U> void push_back(const U&);
    void clear();
    bool empty() const;
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

private:
    std::vector<PolymorphicType<T>> _list;
};

}
}

#include "List.hpp"

#endif
