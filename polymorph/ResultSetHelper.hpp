template<typename T>
T dbobject::ResultSetHelper::get(std::shared_ptr<sql::ResultSet> db, unsigned int column)
{
    return TypeConverter::fromString<T>(dbobject::ResultSetHelper::get<std::string>(db, column));
}

template<typename T>
T dbobject::ResultSetHelper::get(std::shared_ptr<sql::ResultSet> db, const std::string& column)
{
    return TypeConverter::fromString<T>(dbobject::ResultSetHelper::get<std::string>(db, column));
}
