#ifndef DBOBJECT_TYPECONVERTER_H
#define DBOBJECT_TYPECONVERTER_H

#include <string>

namespace dbobject {

namespace TypeConverter {
    enum ConversionType { BOOLALPHA, BOOLNUM };

    template<typename T> T fromString(const std::string&, ConversionType = BOOLALPHA);
    template<typename T> std::string toString(const T&, ConversionType = BOOLALPHA);
}

}

#include "TypeConverter.hpp"

#endif
