#include <gtest/gtest.h>
#include "../SQLConfFile.h"

TEST( SQLConfFileTest, minimal )
{
    std::stringstream stream;
    stream << "schema = db";

    auto sqlMap = File::parseToSQLConnectOptionsMap(stream);

    EXPECT_EQ( sql::SQLString("127.0.0.1"), *sqlMap["hostName"].get<sql::SQLString>() );
    EXPECT_EQ( 0, sqlMap.count("userName") );
    EXPECT_EQ( 0, sqlMap.count("password") );
    EXPECT_EQ( sql::SQLString("db"), *sqlMap["schema"].get<sql::SQLString>() );
}

TEST( SQLConfFileTest, complete )
{
    std::stringstream stream;
    stream << "hostName = localhost\n"
        << "userName = user\n"
        << "password = pass\n"
        << "schema = db\n";

    auto sqlMap = File::parseToSQLConnectOptionsMap(stream);

    EXPECT_EQ( sql::SQLString("localhost"), *sqlMap["hostName"].get<sql::SQLString>() );
    EXPECT_EQ( sql::SQLString("user"), *sqlMap["userName"].get<sql::SQLString>() );
    EXPECT_EQ( sql::SQLString("pass"), *sqlMap["password"].get<sql::SQLString>() );
    EXPECT_EQ( sql::SQLString("db"), *sqlMap["schema"].get<sql::SQLString>() );
}

TEST( SQLConfFileTest, missingSchema )
{
    std::stringstream stream;

    ASSERT_THROW( File::parseToSQLConnectOptionsMap(stream), std::invalid_argument) ;
}
