#ifndef MYSQLBACKENDINTEGRATIONTEST_H
#define MYSQLBACKENDINTEGRATIONTEST_H

#include <gtest/gtest.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <mysql_driver.h>
#include "backends/mysql/MySQLBackend.h"

using namespace dbobject;

class MySQLBackendIntegrationTest : public testing::Test
{
public:
    MySQLBackendIntegrationTest(const SQL::TableName& = SQL::TableName("MySQLBackendIntegrationTest"));

    static void SetUpTestCase();
    static std::string printSQLError(sql::SQLException&);

    virtual void SetUp();
    virtual void dropTableIfExists();
    virtual void createTable();

    SQL::TableName table;
    static std::shared_ptr<sql::Connection> conn;
    static std::shared_ptr<MySQLBackend> db;
};

#endif
