#include "MySQLBackendIntegrationTest.h"
#include <memory>
#include <stdexcept>
#include <cppconn/statement.h>
#include <mysql_driver.h>
#include "file/FileIO.h"
#include "file/SQLConfFile.h"
#include "query/Select.h"
#include "query/Insert.h"
#include "polymorph/ResultSetHelper.hxx"

MySQLBackendIntegrationTest::MySQLBackendIntegrationTest(const SQL::TableName& name)
    : table(name)
{
}

void MySQLBackendIntegrationTest::SetUpTestCase()
{
    try {
        sql::ConnectOptionsMap dbparam = File::parseToSQLConnectOptionsMap(*File::read("test/parameters.conf"));
        conn = std::shared_ptr<sql::Connection>(sql::mysql::get_driver_instance()->connect(dbparam));
        conn->setAutoCommit(0);
        db = std::shared_ptr<MySQLBackend>(new MySQLBackend(conn));
    } catch (sql::SQLException &e) {
        FAIL() << printSQLError(e);
    }
}

void MySQLBackendIntegrationTest::SetUp()
{
    ASSERT_TRUE( static_cast<bool>(conn) ) << "Cannot run tests if no connection to database";
    ASSERT_TRUE( static_cast<bool>(db) ) << "Cannot run tests if no connection to database";
    dropTableIfExists();
    createTable();
}

void MySQLBackendIntegrationTest::dropTableIfExists()
{
    std::string query = "DROP TABLE IF EXISTS "+table();
    try {
        conn->createStatement()->execute(query);
    } catch (sql::SQLException &e) {
        FAIL() << printSQLError(e) << " with query: " << query;
    }
}

void MySQLBackendIntegrationTest::createTable()
{
    std::string query = "CREATE TABLE "+table()+" (`bool` BOOL, `int` INT, `string` VARCHAR(30), PRIMARY KEY(`bool`, `int`, `string`))";
    try {
        conn->createStatement()->execute(query);
    } catch (sql::SQLException &e) {
        FAIL() << printSQLError(e) << " with query: " << query;
    }
}

std::string MySQLBackendIntegrationTest::printSQLError(sql::SQLException& e) {
    std::stringstream str;
    str << "MySQL error: " << e.what();
    str << " (MySQL error code: " << e.getErrorCode();
    str << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    return str.str();
}

std::shared_ptr<sql::Connection> MySQLBackendIntegrationTest::conn;
std::shared_ptr<MySQLBackend> MySQLBackendIntegrationTest::db;

using namespace SQL::Operators;

TEST_F( MySQLBackendIntegrationTest, insertAndGetResult )
{
    auto add = SQL::Query::insert({"bool"_c == SQL::Literal(true), "int"_c == 1_l, "string"_c == "str"_l}).into(table);
    db->query(add);

    std::shared_ptr<sql::ResultSet> res(db->query(SQL::Query::select().from(table).where({"string"_c == "str"_l})));
    ASSERT_EQ( 1, res->rowsCount() );
    res->next();
    ASSERT_TRUE( ResultSetHelper::get<bool>(res, "bool") );
    ASSERT_EQ( 1, ResultSetHelper::get<int>(res, "int") );
    ASSERT_EQ( "str", ResultSetHelper::get<std::string>(res, "string") );
}

