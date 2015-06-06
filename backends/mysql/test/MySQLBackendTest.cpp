#include <gtest/gtest.h>
#include "../MySQLBackend.h"

TEST( MySQLBackendTest, SelectQueryWhileNoConnection )
{
    dbobject::MySQLBackend backend;
    dbobject::SQL::Select query;
    ASSERT_THROW( backend.query(query), std::logic_error );
}

TEST( MySQLBackendTest, InsertQueryWhileNoConnection )
{
    dbobject::MySQLBackend backend;
    dbobject::SQL::Insert query;
    ASSERT_THROW( backend.query(query), std::logic_error );
}
TEST( MySQLBackendTest, UpdateQueryWhileNoConnection )
{
    dbobject::MySQLBackend backend;
    dbobject::SQL::Update query;
    ASSERT_THROW( backend.query(query), std::logic_error );
}
