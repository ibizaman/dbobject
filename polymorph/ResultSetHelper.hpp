namespace dbobject {
namespace ResultSetHelper {

template<typename T>
T get(std::shared_ptr<sql::ResultSet> db, int column)
{
    return TypeConverter::fromString<T>(get<std::string>(db, column));
}

template<typename T>
T get(std::shared_ptr<sql::ResultSet> db, const std::string& column)
{
    return TypeConverter::fromString<T>(get<std::string>(db, column));
}

}
}
