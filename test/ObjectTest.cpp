#include <gtest/gtest.h>

#include <memory>
#include "Tuple.h"
#include "Object.h"
#include "test/dummy/DummyObject.h"
#include "test/mock/BackendMock.h"
#include "test/mock/ResultSetMock.h"

#include <string>

using testing::Return;
using namespace dbobject;
using namespace dbobject::SQL::Operators;

class ObjectTest : public testing::Test
{
public:
    ObjectTest()
        : backend(new BackendMock),
          result(new ResultSetMock),
          dbtuple(new Tuple(backend)),
          db(new Object(dbtuple))
    {
    }

    std::shared_ptr<BackendMock> backend;
    std::shared_ptr<ResultSetMock> result;
    std::shared_ptr<Tuple> dbtuple;
    std::shared_ptr<Object> db;
};

TEST_F( ObjectTest, getOne )
{
    DummyObject expect;
    expect.setBool(false);
    expect.setInt(3);
    expect.setString("hello");

    auto query = SQL::Query::select({"bool", "int", "string"})
        .from("DummyObject")
        .where( SQL::Assignement<SQL::ColumnName, SQL::Literal>("string", "hello") );

    EXPECT_CALL( *backend, query(query) ).WillOnce(Return(result));
    EXPECT_CALL( *result, next() ).WillOnce(Return(true));
    EXPECT_CALL( *result, getBoolean(1) ).WillOnce(Return(false));
    EXPECT_CALL( *result, getInt(2) ).WillOnce(Return(3));
    EXPECT_CALL( *result, getString(3) ).WillOnce(Return(std::string("hello")));

    //auto o = db->getDummyObject("hello");
    auto o = db->getOne<DummyObject>("string"_c == "hello"_l);

    EXPECT_EQ( expect.getBool(), o->getBool() );
    EXPECT_EQ( expect.getInt(), o->getInt() );
    EXPECT_EQ( expect.getString(), o->getString() );
}

TEST_F( ObjectTest, getList )
{
    DummyObject expect1;
    expect1.setBool(true);
    expect1.setInt(3);
    expect1.setString("hello");

    DummyObject expect2;
    expect2.setBool(false);
    expect2.setInt(4);
    expect2.setString("hello");

    auto query = SQL::Query::select({"bool", "int", "string"})
        .from("DummyObject")
        .where( SQL::Assignement<SQL::ColumnName, SQL::Literal>("string", "hello") );

    EXPECT_CALL( *backend, query(query) ).WillOnce(Return(result));

    {
        ::testing::InSequence s;

        EXPECT_CALL(*result, rowsCount()).WillOnce(Return(2)).RetiresOnSaturation();

        EXPECT_CALL(*result, next()).WillOnce(Return(true)).RetiresOnSaturation();
        EXPECT_CALL( *result, getBoolean(1) ).WillOnce(Return(true));
        EXPECT_CALL(*result, getInt(2)).WillOnce(Return(3)).RetiresOnSaturation();
        EXPECT_CALL(*result, getString(3)).WillOnce(Return("hello")).RetiresOnSaturation();

        EXPECT_CALL(*result, next()).WillOnce(Return(true)).RetiresOnSaturation();
        EXPECT_CALL( *result, getBoolean(1) ).WillOnce(Return(false));
        EXPECT_CALL(*result, getInt(2)).WillOnce(Return(4)).RetiresOnSaturation();
        EXPECT_CALL(*result, getString(3)).WillOnce(Return("hello")).RetiresOnSaturation();
    }

    auto o = db->getList<DummyObject>("string"_c == "hello"_l);

    EXPECT_EQ( expect1.getBool(), o[0]->getBool() );
    EXPECT_EQ( expect1.getInt(), o[0]->getInt() );
    EXPECT_EQ( expect1.getString(), o[0]->getString() );

    EXPECT_EQ( expect2.getBool(), o[1]->getBool() );
    EXPECT_EQ( expect2.getInt(), o[1]->getInt() );
    EXPECT_EQ( expect2.getString(), o[1]->getString() );
}

TEST_F( ObjectTest, storeOne )
{
    Ptr<DummyObject>::type o(new DummyObject);
    o->setBool(false);
    o->setInt(3);
    o->setString("hello");

    auto query = SQL::Query::insert()
        .into("DummyObject")
        .columnNames({"bool", "int", "string"})
        .addValues({false, 3, "hello"})
        .orUpdate();

    EXPECT_CALL( *backend, query(query) );

    db->storeOne<DummyObject>(o);
}

TEST_F( ObjectTest, storeList )
{
    Ptr<DummyObject>::type o1(new DummyObject);
    o1->setBool(true);
    o1->setInt(3);
    o1->setString("hello");
    Ptr<DummyObject>::type o2(new DummyObject);
    o2->setBool(false);
    o2->setInt(4);
    o2->setString("hi");
    List<DummyObject>::type list;
    list.push_back(o1);
    list.push_back(o2);

    auto query = SQL::Query::insert()
        .into("DummyObject")
        .columnNames({"bool", "int", "string"})
        .addValues({true, 3, "hello"})
        .addValues({false, 4, "hi"})
        .orUpdate();

    EXPECT_CALL( *backend, query(query) );

    db->storeList<DummyObject>(list);
}
