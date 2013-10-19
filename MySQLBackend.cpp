#include "MySQLBackend.h"
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

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
    return std::shared_ptr<sql::ResultSet>(_conn->createStatement()->executeQuery(query.getSQL()));
}

Backend::count MySQLBackend::query(const SQL::Insert& query)
{
    if (!_conn) {
        throw std::logic_error(std::string("Cannot execute insert query since connection is not set (query : " + query.getSQL() + ")"));
    }
    return _conn->createStatement()->executeUpdate(query.getSQL());
}

Backend::count MySQLBackend::query(const SQL::Update& query)
{
    if (!_conn) {
        throw std::logic_error(std::string("Cannot execute update query since connection is not set (query : " + query.getSQL() + ")"));
    }
    return _conn->createStatement()->executeUpdate(query.getSQL());
}

}
