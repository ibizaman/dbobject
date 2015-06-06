#include "SQLConfFile.h"
#include "FileIO.h"
#include <stdexcept>

namespace File
{

sql::ConnectOptionsMap parseToSQLConnectOptionsMap(std::istream& file)
{
    auto properties = parseToPropertiesMap(file);

    sql::ConnectOptionsMap map;

    // Does not work with try/catch around properties.at because it
    // still creates an empty entry in the map variable
    if (properties.count("hostName")) {
        map["hostName"] = properties.at("hostName");
    } else {
        map["hostName"] = sql::SQLString("127.0.0.1");
    }

    if (properties.count("userName")) {
        map["userName"] = properties.at("userName");
    }

    if (properties.count("password")) {
        map["password"] = properties.at("password");
    }

    if (properties.count("schema")) {
        map["schema"] = properties.at("schema");
    } else {
        throw std::invalid_argument("schema not found");
    }

    return map;
}

}
