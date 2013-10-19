#ifndef DBOBJECT_OBJECT_H
#define DBOBJECT_OBJECT_H

#include "Types.h"
#include "sql/Expression.h"

namespace dbobject {

class Tuple;

class Object
{
public:
    Object(std::shared_ptr<Tuple> = nullptr);
    void setBackend(std::shared_ptr<Tuple>);

    template<typename T> struct Properties;

    template<typename T> typename Ptr<T>::type getOne(const SQL::Expression&);
    template<typename T> typename List<T>::type getList(const SQL::Expression& = SQL::Expression());

    template<typename T> void storeOne(const typename Ptr<T>::type&);
    template<typename T> void storeList(const typename List<T>::type&);

    std::shared_ptr<Tuple> _db;
};

}

#include "Object.hpp"

#endif
