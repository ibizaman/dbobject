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
    void setString(std::string s) {_s = s;}
    std::string getString() const {return _s;}

private:
    bool _b;
    int _i;
    std::string _s;
};

template<> struct Object::Properties<DummyObject>
{
    typedef std::tuple<bool, int, std::string> tuple;
    static const SQL::List<SQL::ColumnName> fields;
    static const SQL::TableName table;

    static Ptr<DummyObject>::type fromTuple(const tuple& t)
    {
        Ptr<DummyObject>::type o(new DummyObject);
        o->setBool(std::get<0>(t));
        o->setInt(std::get<1>(t));
        o->setString(std::get<2>(t));
        return o;
    }

    static tuple toTuple(const Ptr<DummyObject>::type& o)
    {
        tuple t;
        std::get<0>(t) = o->getBool();
        std::get<1>(t) = o->getInt();
        std::get<2>(t) = o->getString();
        return t;
    }
};

}

#endif
