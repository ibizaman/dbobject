#include "Tuple.h"
#include "sql/All.h"

namespace dbobject {

template<typename T>
typename Ptr<T>::type Object::getOne(const SQL::Expression& where)
{
    auto tuple = _db->getOne<typename Properties<T>::tuple>(Properties<T>::table, Properties<T>::fields, where);
    return Properties<T>::fromTuple(tuple);
}

template<typename T>
typename List<T>::type Object::getList(const SQL::Expression& where)
{
    auto list = _db->getAsTuples<typename Properties<T>::tuple>(Properties<T>::table, Properties<T>::fields, where);

    typename List<T>::type objects;
    objects.reserve(objects.size());

    for (auto& tuple: list) {
        objects.push_back(Properties<T>::fromTuple(tuple));
    }

    return objects;
}

template<typename T>
void Object::storeOne(const typename Ptr<T>::type& object)
{
    _db->store(Properties<T>::table, Properties<T>::fields, Properties<T>::toTuple(object));
}

template<typename T>
void Object::storeList(const typename List<T>::type& objects)
{
    typename VectorOfTuples<typename Properties<T>::tuple>::type tuples;

    for (auto object : objects) {
        tuples.push_back(Properties<T>::toTuple(object));
    }

    if (objects.size() > 0) {
        _db->store(Properties<T>::table, Properties<T>::fields, tuples);
    }
}

}
