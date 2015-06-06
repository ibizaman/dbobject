#include <gmock/gmock.h>
#include "Tuple.h"

#include <memory>
#include <stdexcept>
#include <string>
#include "mock/BackendMock.h"
#include "mock/ResultSetMock.h"

using testing::Return;
using testing::ReturnPointee;
using testing::An;
using namespace dbobject;

typedef std::tuple<bool, int, std::string> test_tuple;

class TupleTest : public testing::Test
{
public:
    TupleTest()
        : backend(new BackendMock),
          result(new ResultSetMock),
          db(backend)
    {
    }

    std::shared_ptr<BackendMock> backend;
    std::shared_ptr<ResultSetMock> result;
    Tuple db;
};

TEST_F( TupleTest, getOneButNoResult )
{
    EXPECT_CALL( *backend, query(An<const SQL::Select&>()) ).WillOnce(Return(result));
    EXPECT_CALL( *result, next() ).WillOnce(Return(false));

    SQL::Select sql;
    ASSERT_THROW( db.getOne<test_tuple>(sql), std::runtime_error );
}

TEST_F( TupleTest, getOne )
{
    EXPECT_CALL( *backend, query(An<const SQL::Select&>()) ).WillOnce(Return(result));
    {
        testing::InSequence s;
        EXPECT_CALL(*result, next()).WillOnce(Return(true));
        EXPECT_CALL(*result, getBoolean(1)).WillOnce(Return(true));
        EXPECT_CALL(*result, getInt(2)).WillOnce(Return(365));
        EXPECT_CALL(*result, getString(3)).WillOnce(Return(std::string("hello")));
    }

    test_tuple expect{true, 365, "hello"};

    SQL::Select sql;
    ASSERT_EQ( expect, (db.getOne<test_tuple>(sql)) );
}

TEST_F( TupleTest, getAsVectors )
{
    EXPECT_CALL( *backend, query(An<const SQL::Select&>()) ).WillOnce(Return(result));
    {
        ::testing::InSequence s;

        EXPECT_CALL(*result, beforeFirst()).RetiresOnSaturation();
        EXPECT_CALL(*result, rowsCount()).WillOnce(Return(3)).RetiresOnSaturation();
        EXPECT_CALL(*result, next()).WillOnce(Return(true)).RetiresOnSaturation();
        EXPECT_CALL(*result, getBoolean(1)).WillOnce(Return(true)).RetiresOnSaturation();
        EXPECT_CALL(*result, next()).WillOnce(Return(true)).RetiresOnSaturation();
        EXPECT_CALL(*result, getBoolean(1)).WillOnce(Return(false)).RetiresOnSaturation();
        EXPECT_CALL(*result, next()).WillOnce(Return(true)).RetiresOnSaturation();
        EXPECT_CALL(*result, getBoolean(1)).WillOnce(Return(false)).RetiresOnSaturation();
        EXPECT_CALL(*result, next()).WillOnce(Return(false)).RetiresOnSaturation();

        EXPECT_CALL(*result, beforeFirst()).RetiresOnSaturation();
        EXPECT_CALL(*result, rowsCount()).WillOnce(Return(3)).RetiresOnSaturation();
        EXPECT_CALL(*result, next()).WillOnce(Return(true)).RetiresOnSaturation();
        EXPECT_CALL(*result, getInt(2)).WillOnce(Return(365)).RetiresOnSaturation();
        EXPECT_CALL(*result, next()).WillOnce(Return(true)).RetiresOnSaturation();
        EXPECT_CALL(*result, getInt(2)).WillOnce(Return(320)).RetiresOnSaturation();
        EXPECT_CALL(*result, next()).WillOnce(Return(true)).RetiresOnSaturation();
        EXPECT_CALL(*result, getInt(2)).WillOnce(Return(250)).RetiresOnSaturation();
        EXPECT_CALL(*result, next()).WillOnce(Return(false)).RetiresOnSaturation();

        EXPECT_CALL(*result, beforeFirst()).RetiresOnSaturation();
        EXPECT_CALL(*result, rowsCount()).WillOnce(Return(3)).RetiresOnSaturation();
        EXPECT_CALL(*result, next()).WillOnce(Return(true)).RetiresOnSaturation();
        EXPECT_CALL(*result, getString(3)).WillOnce(Return(std::string("hello"))).RetiresOnSaturation();
        EXPECT_CALL(*result, next()).WillOnce(Return(true)).RetiresOnSaturation();
        EXPECT_CALL(*result, getString(3)).WillOnce(Return(std::string("hi"))).RetiresOnSaturation();
        EXPECT_CALL(*result, next()).WillOnce(Return(true)).RetiresOnSaturation();
        EXPECT_CALL(*result, getString(3)).WillOnce(Return(std::string("howdy"))).RetiresOnSaturation();
        EXPECT_CALL(*result, next()).WillOnce(Return(false)).RetiresOnSaturation();
    }

    std::tuple<std::vector<bool>, std::vector<int>, std::vector<std::string>> expect{
        {true, false, false},
        {365, 320, 250},
        {"hello", "hi", "howdy"}
    };

    SQL::Select sql;
    auto r = db.getAsVectors<test_tuple>(sql);
    EXPECT_EQ( std::get<0>(expect), std::get<0>(r) );
    EXPECT_EQ( std::get<1>(expect), std::get<1>(r) );
    EXPECT_EQ( std::get<2>(expect), std::get<2>(r) );
}

TEST_F( TupleTest, getAsTuples )
{
    EXPECT_CALL( *backend, query(An<const SQL::Select&>()) ).WillOnce(Return(result));
    {
        ::testing::InSequence s;

        EXPECT_CALL(*result, rowsCount()).WillOnce(Return(3)).RetiresOnSaturation();

        EXPECT_CALL(*result, next()).WillOnce(Return(true)).RetiresOnSaturation();
        EXPECT_CALL(*result, getBoolean(1)).WillOnce(Return(true)).RetiresOnSaturation();
        EXPECT_CALL(*result, getInt(2)).WillOnce(Return(365)).RetiresOnSaturation();
        EXPECT_CALL(*result, getString(3)).WillOnce(Return(std::string("hello"))).RetiresOnSaturation();

        EXPECT_CALL(*result, next()).WillOnce(Return(true)).RetiresOnSaturation();
        EXPECT_CALL(*result, getBoolean(1)).WillOnce(Return(false)).RetiresOnSaturation();
        EXPECT_CALL(*result, getInt(2)).WillOnce(Return(320)).RetiresOnSaturation();
        EXPECT_CALL(*result, getString(3)).WillOnce(Return(std::string("hi"))).RetiresOnSaturation();

        EXPECT_CALL(*result, next()).WillOnce(Return(true)).RetiresOnSaturation();
        EXPECT_CALL(*result, getBoolean(1)).WillOnce(Return(false)).RetiresOnSaturation();
        EXPECT_CALL(*result, getInt(2)).WillOnce(Return(250)).RetiresOnSaturation();
        EXPECT_CALL(*result, getString(3)).WillOnce(Return(std::string("howdy"))).RetiresOnSaturation();
    }

    std::vector<test_tuple> expect{
        std::make_tuple(true, 365, "hello"),
        std::make_tuple(false, 320, "hi"),
        std::make_tuple(false, 250, "howdy")
    };

    SQL::Select sql;
    auto r = db.getAsTuples<test_tuple>(sql);
    ASSERT_EQ( expect, r );
}

TEST_F( TupleTest, storeOne )
{
    test_tuple to_store{true, 365, "hello"};
    SQL::Insert query = SQL::Query::insert().into("table").addValues({true, 365, "hello"});

    EXPECT_CALL( *backend, query(query) );

    db.store("table", to_store);
}

TEST_F( TupleTest, storeTupleOfVectors )
{
    std::vector<test_tuple> to_store{
        std::make_tuple(true, 365, "hello"),
        std::make_tuple(false, 320, "hi"),
        std::make_tuple(false, 250, "howdy")
    };
    SQL::Insert query = SQL::Query::insert().into("table")
        .addValues({true, 365, "hello"})
        .addValues({false, 320, "hi"})
        .addValues({false, 250, "howdy"});

    EXPECT_CALL( *backend, query(query) );

    db.store("table", to_store);
}

TEST_F( TupleTest, storeVectorOfTuples )
{
    std::tuple<std::vector<bool>, std::vector<int>, std::vector<std::string>> to_store{
        {true, false, false},
        {365, 320, 250},
        {"hello", "hi", "howdy"}
    };
    SQL::Insert query = SQL::Query::insert().into("table")
        .addValues({true, 365, "hello"})
        .addValues({false, 320, "hi"})
        .addValues({false, 250, "howdy"});

    EXPECT_CALL( *backend, query(query) );

    db.store("table", to_store);
}

TEST_F( TupleTest, storeOrUpdateOne )
{
    test_tuple to_store{true, 365, "hello"};
    SQL::Insert query = SQL::Query::insert()
        .into("table")
        .addValues({true, 365, "hello"})
        .columnNames({"a", "b", "c"})
        .orUpdate();

    EXPECT_CALL( *backend, query(query) );

    db.store("table", {"a", "b", "c"}, to_store);
}

TEST_F( TupleTest, storeOrUpdateTupleOfVectors )
{
    std::vector<test_tuple> to_store{
        std::make_tuple(true, 365, "hello"),
        std::make_tuple(false, 320, "hi"),
        std::make_tuple(false, 250, "howdy")
    };
    SQL::Insert query = SQL::Query::insert().into("table")
        .addValues({true, 365, "hello"})
        .addValues({false, 320, "hi"})
        .addValues({false, 250, "howdy"})
        .columnNames({"a", "b", "c"})
        .orUpdate();

    EXPECT_CALL( *backend, query(query) );

    db.store("table", {"a", "b", "c"}, to_store);
}

TEST_F( TupleTest, storeOrUpdateVectorOfTuples )
{
    std::tuple<std::vector<bool>, std::vector<int>, std::vector<std::string>> to_store{
        {true, false, false},
        {365, 320, 250},
        {"hello", "hi", "howdy"}
    };
    SQL::Insert query = SQL::Query::insert().into("table")
        .addValues({true, 365, "hello"})
        .addValues({false, 320, "hi"})
        .addValues({false, 250, "howdy"})
        .columnNames({"a", "b", "c"})
        .orUpdate();

    EXPECT_CALL( *backend, query(query) );

    db.store("table", {"a", "b", "c"}, to_store);
}
