#ifndef DBOBJECT_MYSQLBACKEND_H
#define DBOBJECT_MYSQLBACKEND_H

#include <cppconn/connection.h>
#include "Backend.h"

namespace sql {
    class ResultSet;
}

namespace dbobject {

class MySQLBackend : public Backend
{
public:
    MySQLBackend(std::shared_ptr<sql::Connection> = nullptr);
    void setConnection(std::shared_ptr<sql::Connection>);

    virtual std::shared_ptr<sql::ResultSet> query(const SQL::Select&) override;
    virtual count query(const SQL::Insert&) override;
    virtual count query(const SQL::Update&) override;

private:
    std::shared_ptr<sql::Connection> _conn;
};

}

#endif
