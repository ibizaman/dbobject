#include <sstream>
#include "TypeConverter.h"

namespace dbobject {
namespace MySQLTypeConverter {

template<typename T>
T fromString(const std::string& str)
{
    return TypeConverter::fromString<T>(str, TypeConverter::BOOLNUM);
}

template<typename T>
std::string toString(const T& value)
{
    return TypeConverter::toString(value, TypeConverter::BOOLNUM);
}

}
}
