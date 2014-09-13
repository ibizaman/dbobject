#include "MySQLBackend.h"
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <sql/TableName.h>
#include <sql/ColumnName.h>
#include <sstream>

namespace dbobject {

MySQLBackend::MySQLBackend(std::shared_ptr<sql::Connection> conn)
{
    setConnection(conn);
}

void MySQLBackend::setConnection(std::shared_ptr<sql::Connection> conn)
{
    _conn = conn;
}

std::shared_ptr<sql::ResultSet> MySQLBackend::query(const SQL::Select& query)
{
    if (!_conn) {
        throw std::logic_error(std::string("Cannot execute select query since connection is not set (query : " + query.getSQL() + ")"));
    }

    std::shared_ptr<sql::ResultSet> result;
    try {
        result = std::shared_ptr<sql::ResultSet>(_conn->createStatement()->executeQuery(query.getSQL()));
    } catch (sql::SQLException& e) {
        manageError(e, query.getSQL(), (*query._from.get())());
    }

    return result;
}

Backend::count MySQLBackend::query(const SQL::Insert& query)
{
    if (!_conn) {
        throw std::logic_error(std::string("Cannot execute insert query since connection is not set (query : " + query.getSQL() + ")"));
    }

    Backend::count c;
    try {
        c = _conn->createStatement()->executeUpdate(query.getSQL());
    } catch (sql::SQLException& e) {
        manageError(e, query.getSQL(), (*query._into.get())());
    }

    return c;
}

Backend::count MySQLBackend::query(const SQL::Update& query)
{
    if (!_conn) {
        throw std::logic_error(std::string("Cannot execute update query since connection is not set (query : " + query.getSQL() + ")"));
    }

    Backend::count c;
    try {
        c = _conn->createStatement()->executeUpdate(query.getSQL());
    } catch (sql::SQLException& e) {
        manageError(e, query.getSQL(), (*query._update.get())());
    }

    return c;
}

void MySQLBackend::manageError(const sql::SQLException& e, const std::string& query, const std::string& table)
{
    switch (e.getErrorCode()) {
    case 1136:
    {
        std::string tableName = table;
        std::shared_ptr<sql::ResultSet> tableDescription(_conn->createStatement()->executeQuery("DESCRIBE "+tableName));
        std::stringstream error;
        error << "Tried to insert bad columns number"
              << " in table " << tableName
              << " which has "
              << tableDescription->rowsCount()
              << " columns\n"
              << "Query : " << query;
        throw MySQLBackendExceptions::BadColumnCount(error.str());
        break;
    }
    default:
        throw e;
    }
}

}
