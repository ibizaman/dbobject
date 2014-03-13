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

// mapOnGetters

template<typename Tuple, typename T, typename... Getters>
Tuple Object::mapOnGetters(T object, Getters... getters)
{
    Tuple tuple;
    mapOnGetters<0>(&tuple, object.get(), getters...);
    return tuple;
}

template<int I, typename Tuple, typename T>
void Object::mapOnGetters(Tuple*, T)
{
}

template<int I, typename Tuple, typename T, typename Getter, typename... Rest>
typename std::enable_if<std::is_member_function_pointer<Getter>::value, void>::type
    Object::mapOnGetters(Tuple* tuple, T object, Getter getter, Rest... getters)
{
    std::get<I>(*tuple) = (object->*getter)();
    mapOnGetters<I+1>(tuple, object, getters...);
}

template<int I, typename Tuple, typename T, typename Getter, typename... Rest>
typename std::enable_if<!std::is_member_function_pointer<Getter>::value, void>::type
    Object::mapOnGetters(Tuple* tuple, T object, Getter getter, Rest... getters)
{
    std::get<I>(*tuple) = object->*getter;
    mapOnGetters<I+1>(tuple, object, getters...);
}

// mapOnSetters

template<typename T, typename Tuple, typename... Setters>
typename Ptr<T>::type Object::mapOnSetters(Tuple tuple, Setters... setters)
{
    typename Ptr<T>::type object(new T);
    mapOnSetters<0>(object.get(), tuple, setters...);
    return object;
}

template<int I, typename T, typename Tuple>
void Object::mapOnSetters(T*, Tuple)
{
}

template<int I, typename T, typename Tuple, typename Setter, typename... Rest>
typename std::enable_if<std::is_member_function_pointer<Setter>::value, void>::type
    Object::mapOnSetters(T* object, Tuple tuple, Setter setter, Rest... setters)
{
    (object->*setter)(std::get<I>(tuple));
    mapOnSetters<I+1>(object, tuple, setters...);
}

template<int I, typename T, typename Tuple, typename Setter, typename... Rest>
typename std::enable_if<!std::is_member_function_pointer<Setter>::value, void>::type
    Object::mapOnSetters(T* object, Tuple tuple, Setter setter, Rest... setters)
{
    object->*setter = std::get<I>(tuple);
    mapOnSetters<I+1>(object, tuple, setters...);
}

}
