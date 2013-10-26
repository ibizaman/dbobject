#ifndef DBOBJECT_RESULTSETHELPER_H
#define DBOBJECT_RESULTSETHELPER_H

#include <string>
#include <memory>
#include <cppconn/resultset.h>
#include "TypeConverter.h"

namespace dbobject {

namespace ResultSetHelper {
    template<typename T> T get(std::shared_ptr<sql::ResultSet> db, int);
    template<typename T> T get(std::shared_ptr<sql::ResultSet> db, const std::string&);
}

}

#include "ResultSetHelper.hpp"

#endif
