#include "ResultSetHelper.hxx"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace dbobject {
namespace ResultSetHelper {

template<>
std::istream* get<std::istream*>(std::shared_ptr<sql::ResultSet> db, const std::string& column)
{
    return db->getBlob(column);
}

template<>
std::istream* get<std::istream*>(std::shared_ptr<sql::ResultSet> db, int column)
{
    return db->getBlob(column);
}

template<>
bool get<bool>(std::shared_ptr<sql::ResultSet> db, const std::string& column)
{
    return db->getBoolean(column);
}

template<>
bool get<bool>(std::shared_ptr<sql::ResultSet> db, int column)
{
    return db->getBoolean(column);
}

template<>
long double get<long double>(std::shared_ptr<sql::ResultSet> db, const std::string& column)
{
    return db->getDouble(column);
}

template<>
long double get<long double>(std::shared_ptr<sql::ResultSet> db, int column)
{
    return db->getDouble(column);
}

template<>
int32_t get<int32_t>(std::shared_ptr<sql::ResultSet> db, const std::string& column)
{
    return db->getInt(column);
}

template<>
int32_t get<int32_t>(std::shared_ptr<sql::ResultSet> db, int column)
{
    return db->getInt(column);
}

template<>
uint32_t get<uint32_t>(std::shared_ptr<sql::ResultSet> db, const std::string& column)
{
    return db->getUInt(column);
}

template<>
uint32_t get<uint32_t>(std::shared_ptr<sql::ResultSet> db, int column)
{
    return db->getUInt(column);
}

template<>
int64_t get<int64_t>(std::shared_ptr<sql::ResultSet> db, const std::string& column)
{
    return db->getInt64(column);
}

template<>
int64_t get<int64_t>(std::shared_ptr<sql::ResultSet> db, int column)
{
    return db->getInt64(column);
}

template<>
uint64_t get<uint64_t>(std::shared_ptr<sql::ResultSet> db, const std::string& column)
{
    return db->getUInt64(column);
}

template<>
uint64_t get<uint64_t>(std::shared_ptr<sql::ResultSet> db, int column)
{
    return db->getUInt64(column);
}

template<>
sql::SQLString get<sql::SQLString>(std::shared_ptr<sql::ResultSet> db, const std::string& column)
{
    return db->getString(column);
}

template<>
sql::SQLString get<sql::SQLString>(std::shared_ptr<sql::ResultSet> db, int column)
{
    return db->getString(column);
}

template<>
std::string get<std::string>(std::shared_ptr<sql::ResultSet> db, const std::string& column)
{
    return db->getString(column).asStdString();
}

template<>
std::string get<std::string>(std::shared_ptr<sql::ResultSet> db, int column)
{
    return db->getString(column).asStdString();
}

}
}
