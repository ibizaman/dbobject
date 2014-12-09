#ifndef DBOBJECT_BACKEND_H
#define DBOBJECT_BACKEND_H

#include <memory>
#include <cppconn/resultset.h>
#include "query/Select.h"
#include "query/Insert.h"
#include "query/Update.h"

namespace dbobject {

class Backend
{
public:
    typedef int count;

    virtual std::shared_ptr<sql::ResultSet> query(const SQL::Select&) = 0;
    virtual count query(const SQL::Insert&) = 0;
    virtual count query(const SQL::Update&) = 0;
};

}

#endif
