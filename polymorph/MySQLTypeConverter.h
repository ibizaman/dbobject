#ifndef DBOBJECT_MYSQLTYPECONVERTER_H
#define DBOBJECT_MYSQLTYPECONVERTER_H

#include <string>

namespace dbobject {

namespace MySQLTypeConverter {
    template<typename T> T fromString(const std::string&);
    template<typename T> std::string toString(const T&);
}

}

#include "MySQLTypeConverter.hpp"

#endif
