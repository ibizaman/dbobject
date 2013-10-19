#include <sstream>

namespace dbobject {
namespace TypeConverter {

template<typename T>
T fromString(const std::string& s, ConversionType type)
{
    std::istringstream serializer(s);

    if (type == BOOLALPHA) {
        serializer.setf(std::ios::boolalpha);
    }

    T value;
    serializer >> value;
    return value;
}

template<typename T>
std::string toString(const T& value, ConversionType type)
{
    std::ostringstream serializer;

    if (type == BOOLALPHA) {
        serializer << std::boolalpha;
    }

    serializer << value;
    return serializer.str();
}

}
}
