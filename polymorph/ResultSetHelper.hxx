#ifndef DBOBJECT_RESULTSETHELPER_H
#define DBOBJECT_RESULTSETHELPER_H

#include <string>
#include <memory>
#include <cppconn/resultset.h>
#include "lib/TypeConverter.h"

namespace dbobject {

namespace ResultSetHelper {
    template<typename T>
    T get(std::shared_ptr<sql::ResultSet>, unsigned int);
    template<typename T>
    T get(std::shared_ptr<sql::ResultSet>, const std::string&);
    template<>
    std::istream* get<std::istream*>(std::shared_ptr<sql::ResultSet>, const std::string&);
    template<>
    std::istream* get<std::istream*>(std::shared_ptr<sql::ResultSet>, unsigned int);
    template<>
    bool get<bool>(std::shared_ptr<sql::ResultSet>, const std::string&);
    template<>
    bool get<bool>(std::shared_ptr<sql::ResultSet>, unsigned int);
    template<>
    long double get<long double>(std::shared_ptr<sql::ResultSet>, const std::string&);
    template<>
    long double get<long double>(std::shared_ptr<sql::ResultSet>, unsigned int);
    template<>
    int32_t get<int32_t>(std::shared_ptr<sql::ResultSet>, const std::string&);
    template<>
    int32_t get<int32_t>(std::shared_ptr<sql::ResultSet>, unsigned int);
    template<>
    uint32_t get<uint32_t>(std::shared_ptr<sql::ResultSet>, const std::string&);
    template<>
    uint32_t get<uint32_t>(std::shared_ptr<sql::ResultSet>, unsigned int);
    template<>
    int64_t get<int64_t>(std::shared_ptr<sql::ResultSet>, const std::string&);
    template<>
    int64_t get<int64_t>(std::shared_ptr<sql::ResultSet>, unsigned int);
    template<>
    uint64_t get<uint64_t>(std::shared_ptr<sql::ResultSet>, const std::string&);
    template<>
    uint64_t get<uint64_t>(std::shared_ptr<sql::ResultSet>, unsigned int);
    template<>
    sql::SQLString get<sql::SQLString>(std::shared_ptr<sql::ResultSet>, const std::string&);
    template<>
    sql::SQLString get<sql::SQLString>(std::shared_ptr<sql::ResultSet>, unsigned int);
    template<>
    std::string get<std::string>(std::shared_ptr<sql::ResultSet>, const std::string&);
    template<>
    std::string get<std::string>(std::shared_ptr<sql::ResultSet>, unsigned int);
}

}

#include "ResultSetHelper.hpp"

#endif
