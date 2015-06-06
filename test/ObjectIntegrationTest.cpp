#include "ObjectIntegrationTest.h"
#include "dummy/DummyObject.h"

using namespace dbobject::SQL::Operators;

std::shared_ptr<Object> ObjectIntegrationTest::dbobject;

ObjectIntegrationTest::ObjectIntegrationTest(const SQL::TableName& name)
    : TupleIntegrationTest(name)
{
}

void ObjectIntegrationTest::SetUpTestCase()
{
    TupleIntegrationTest::SetUpTestCase();
    dbobject = std::shared_ptr<Object>(new Object(TupleIntegrationTest::dbtuple));
}

TEST_F( ObjectIntegrationTest, getObjectFail )
{
    ASSERT_THROW( dbobject->getOne<DummyObject>("string"_c == "hello"_l), std::runtime_error );
}

TEST_F( ObjectIntegrationTest, insertAndGetObject )
{
    Ptr<DummyObject>::type obj(new DummyObject);
    obj->setBool(false);
    obj->setInt(3);
    obj->setString("hello");

    dbobject->storeOne<DummyObject>(obj);
    auto received = dbobject->getOne<DummyObject>("string"_c == "hello"_l);

    EXPECT_EQ( obj->getInt(), received->getInt() );
    EXPECT_EQ( obj->getString(), received->getString() );
}

TEST_F( ObjectIntegrationTest, insertAndGetList )
{
    Ptr<DummyObject>::type o1(new DummyObject);
    o1->setBool(false);
    o1->setInt(3);
    o1->setString("hello");
    Ptr<DummyObject>::type o2(new DummyObject);
    o1->setBool(true);
    o2->setInt(4);
    o2->setString("hi");
    List<DummyObject>::type list;
    list.push_back(o1);
    list.push_back(o2);

    List<DummyObject>::type received;
    try {
        dbobject->storeList<DummyObject>(list);
        received = dbobject->getList<DummyObject>();
    } catch (sql::SQLException& e) {
        FAIL() << printSQLError(e);
    }

    ASSERT_EQ( 2, received.size() );

    EXPECT_TRUE( std::find_if(received.begin(), received.end(), [o1](std::shared_ptr<DummyObject> d){
            return o1->getInt() == d->getInt()
               and o1->getString() == d->getString();
       }) != std::end(received) );
    EXPECT_TRUE( std::find_if(received.begin(), received.end(), [o2](std::shared_ptr<DummyObject> d){
            return o2->getInt() == d->getInt()
               and o2->getString() == d->getString();
       }) != std::end(received) );
}

TEST_F( ObjectIntegrationTest, insertAndCount )
{
    unsigned int count;

    try {
        count = dbobject->count<DummyObject>();
    } catch (sql::SQLException& e) {
        FAIL() << printSQLError(e);
    }

    EXPECT_EQ( 0, count );

    {
        Ptr<DummyObject>::type obj(new DummyObject);
        obj->setBool(false);
        obj->setInt(3);
        obj->setString("hello");

        try {
            dbobject->storeOne<DummyObject>(obj);
        } catch (sql::SQLException& e) {
            FAIL() << printSQLError(e);
        }
    }

    {
        Ptr<DummyObject>::type obj(new DummyObject);
        obj->setBool(false);
        obj->setInt(4);
        obj->setString("hi");

        try {
            dbobject->storeOne<DummyObject>(obj);
        } catch (sql::SQLException& e) {
            FAIL() << printSQLError(e);
        }
    }

    try {
        count = dbobject->count<DummyObject>();
    } catch (sql::SQLException& e) {
        FAIL() << printSQLError(e);
    }

    EXPECT_EQ( 2, count );
}

TEST_F( ObjectIntegrationTest, insertAndCountWhere )
{
    unsigned int count;

    try {
        count = dbobject->count<DummyObject>();
    } catch (sql::SQLException& e) {
        FAIL() << printSQLError(e);
    }

    EXPECT_EQ( 0, count );

    {
        Ptr<DummyObject>::type obj(new DummyObject);
        obj->setBool(false);
        obj->setInt(3);
        obj->setString("hello");

        try {
            dbobject->storeOne<DummyObject>(obj);
        } catch (sql::SQLException& e) {
            FAIL() << printSQLError(e);
        }
    }

    {
        Ptr<DummyObject>::type obj(new DummyObject);
        obj->setBool(false);
        obj->setInt(4);
        obj->setString("hi");

        try {
            dbobject->storeOne<DummyObject>(obj);
        } catch (sql::SQLException& e) {
            FAIL() << printSQLError(e);
        }
    }

    try {
        count = dbobject->count<DummyObject>("string"_c == "hi"_l);
    } catch (sql::SQLException& e) {
        FAIL() << printSQLError(e);
    }

    EXPECT_EQ( 1, count );
}

