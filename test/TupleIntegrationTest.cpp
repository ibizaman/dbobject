#include "TupleIntegrationTest.h"

TupleIntegrationTest::TupleIntegrationTest(const SQL::TableName& name)
    : MySQLBackendIntegrationTest(name)
{
}

void TupleIntegrationTest::SetUpTestCase()
{
    MySQLBackendIntegrationTest::SetUpTestCase();
    dbtuple = std::shared_ptr<Tuple>(new Tuple(MySQLBackendIntegrationTest::db));
}

std::shared_ptr<Tuple> TupleIntegrationTest::dbtuple;

using namespace SQL::Operators;


TEST_F( TupleIntegrationTest, insertFail )
{
    auto stored = std::make_tuple(true, 1, "str", true);
    ASSERT_THROW( dbtuple->store(TupleIntegrationTest::table, stored), MySQLBackendExceptions::BadColumnCount );
}

TEST_F( TupleIntegrationTest, getFail )
{
    ASSERT_THROW( dbtuple->getOne<test_tuple>(TupleIntegrationTest::table, "bool"_c == SQL::Literal(false)), std::runtime_error );
}

TEST_F( TupleIntegrationTest, insertAndGetTuple )
{
    test_tuple stored = std::make_tuple(true, 1, "str");
    dbtuple->store(TupleIntegrationTest::table, stored);

    test_tuple received = dbtuple->getOne<test_tuple>(TupleIntegrationTest::table, "bool"_c == SQL::Literal(true));

    EXPECT_EQ( stored, received );
}

TEST_F( TupleIntegrationTest, insertAndGetList )
{
    test_tuple stored1 = std::make_tuple(true, 1, "str");
    test_tuple stored2 = std::make_tuple(false, 2, "str2");
    VectorOfTuples<test_tuple>::type list;
    list.push_back(stored1);
    list.push_back(stored2);
    dbtuple->store(TupleIntegrationTest::table, list);

    auto received = dbtuple->getAsTuples<test_tuple>(TupleIntegrationTest::table);

    ASSERT_EQ( 2, received.size() );
    // takes into account ordering of primary key on first column (false < true)
    EXPECT_EQ( stored2, *received.begin() );
    EXPECT_EQ( stored1, *(++received.begin()) );
}
