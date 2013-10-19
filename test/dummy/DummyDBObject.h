#ifndef DUMMYDBOBJECT_H
#define DUMMYDBOBJECT_H

#include "Object.h"
#include "test/dummy/DummyObject.h"

namespace dbobject {

class DummyDBObject : public Object
{
public:
    using Object::Object;

    Ptr<DummyObject>::type getDummyObject(const std::string& s)
    {
        return getOne<DummyObject>(SQL::Assignement<SQL::ColumnName, SQL::Literal>(SQL::ColumnName("string"), SQL::Literal(s)));
    }

    List<DummyObject>::type getDummyObjects()
    {
        return getList<DummyObject>();
    }

    List<DummyObject>::type getDummyObjects(const std::string& s)
    {
        return getList<DummyObject>(SQL::Assignement<SQL::ColumnName, SQL::Literal>(SQL::ColumnName("string"), SQL::Literal(s)));
    }

    void store(const Ptr<DummyObject>::type& o)
    {
        storeOne<DummyObject>(o);
    }

    void store(const List<DummyObject>::type& o)
    {
        storeList<DummyObject>(o);
    }
};

}

#endif
