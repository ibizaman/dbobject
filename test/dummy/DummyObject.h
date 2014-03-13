#ifndef DUMMYOBJECT_H
#define DUMMYOBJECT_H

#include "Object.h"

namespace dbobject {

class DummyObject
{
public:
    void setBool(bool b) {_b = b;}
    int getBool() const {return _b;}
    void setInt(int i) {_i = i;}
    int getInt() const {return _i;}
    void setString(std::string s_) {s = s_;}
    std::string getString() const {return s;}

    std::string s;

private:
    bool _b;
    int _i;
};

template<> struct Object::Properties<DummyObject>
{
    typedef std::tuple<bool, int, std::string> tuple;
    static const SQL::List<SQL::ColumnName> fields;
    static const SQL::TableName table;

    static Ptr<DummyObject>::type fromTuple(const tuple& t)
    {
        return mapOnSetters<DummyObject>(
                t,
                &DummyObject::setBool,
                &DummyObject::setInt,
                &DummyObject::s
            );
    }

    static tuple toTuple(const Ptr<DummyObject>::type& o)
    {
        return mapOnGetters<tuple>(
                o,
                &DummyObject::getBool,
                &DummyObject::getInt,
                &DummyObject::s
            );
    }
};

}

#endif
