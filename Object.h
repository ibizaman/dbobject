#ifndef DBOBJECT_OBJECT_H
#define DBOBJECT_OBJECT_H

#include "Types.h"
#include "query/Select.h"
#include "query/sql/Expression.h"

namespace dbobject {

class Tuple;

class Object
{
public:
    Object(std::shared_ptr<Tuple> = nullptr);
    void setBackend(std::shared_ptr<Tuple>);

    template<typename T>
        struct Properties;

    template<typename T>
        typename Ptr<T>::type getOne(const SQL::Expression&);
    template<typename T>
        typename List<T>::type getList(const SQL::Expression& = SQL::Expression());
    template<typename T>
        typename List<T>::type getList(SQL::Select);

    template<typename T>
        void storeOne(const typename Ptr<T>::type&);
    template<typename T>
        void storeList(const typename List<T>::type&);

    template<typename T>
        unsigned int count();
    template<typename T>
        unsigned int count(const SQL::Expression&);
    template<typename T>
        unsigned int count(SQL::Select);

    template<typename Tuple, typename T, typename... Getters>
        static Tuple mapOnGetters(T, Getters...);

    template<typename T, typename Tuple, typename... Setters>
        static typename Ptr<T>::type mapOnSetters(Tuple, Setters...);

private:
    template<int I, typename Tuple, typename T>
        static void mapOnGetters(Tuple*, T);

    template<int I, typename Tuple, typename T, typename Getter, typename... Rest>
        static typename std::enable_if<std::is_member_function_pointer<Getter>::value, void>::type
        mapOnGetters(Tuple*, T, Getter, Rest...);

    template<int I, typename Tuple, typename T, typename Getter, typename... Rest>
        static typename std::enable_if<!std::is_member_function_pointer<Getter>::value, void>::type
        mapOnGetters(Tuple*, T, Getter, Rest...);

    template<int I, typename T, typename Tuple>
        static void mapOnSetters(T*, Tuple);

    template<int I, typename T, typename Tuple, typename Setter, typename... Rest>
        static typename std::enable_if<std::is_member_function_pointer<Setter>::value, void>::type
        mapOnSetters(T*, Tuple, Setter, Rest...);

    template<int I, typename T, typename Tuple, typename Setter, typename... Rest>
        static typename std::enable_if<!std::is_member_function_pointer<Setter>::value, void>::type
        mapOnSetters(T*, Tuple, Setter, Rest...);

    std::shared_ptr<Tuple> _db;
};

}

#include "Object.hpp"

#endif
