#include "TypeConverter.h"
#include <typeinfo>

TypeConverter::Settings::Settings()
{
}

TypeConverter::Settings::Settings(char separator)
    : separator(separator)
{
}

TypeConverter::Settings::Settings(char separator, char leftVector, char rightVector, char leftTuple, char rightTuple)
    : separator(separator)
    , leftVector(leftVector)
    , rightVector(rightVector)
    , leftTuple(leftTuple)
    , rightTuple(rightTuple)
{
}

TypeConverter::ImpossibleConversion::ImpossibleConversion(std::string conversionType, std::string givenValue, std::string reason)
    : std::logic_error(
            std::string("Cannot convert from type \"") + typeid(givenValue).name() + "\" and value (" + givenValue + ")"
            + " to a " + conversionType + " because: " + reason + "."
        )
    , conversionType(conversionType)
    , givenValue(givenValue)
    , reason(reason)
{
}

bool TypeConverter::impl::TypeConverter<bool>::fromString(const std::string& s, const Settings&)
{
    std::istringstream serializer(s);
    serializer.setf(std::ios::boolalpha);

    bool b;
    if (!(serializer >> b)) {
        throw ImpossibleConversion(typeid(bool).name(), s, "impossible to convert using istringstream");
    }
    return b;
}

std::string TypeConverter::impl::TypeConverter<bool>::toString(bool b, const Settings&)
{
    std::ostringstream serializer;
    serializer << std::boolalpha;

    serializer << b;
    return serializer.str();
}

size_t TypeConverter::impl::getNextSeparator(const std::string& str, const Settings& settings)
{
    size_t split = 0;
    if (str.size() == 0) {
        return std::string::npos;
    }

    auto first_non_blank_pos = str.find_first_not_of(' ');
    if (first_non_blank_pos == std::string::npos) {
        return std::string::npos;
    }

    size_t offset = 0;
    auto first_non_blank = str.at(first_non_blank_pos);
    if (first_non_blank == settings.leftVector) {
        offset = str.find(settings.rightVector) + 1;
    } else if (first_non_blank == settings.leftTuple) {
        offset = str.find(settings.rightTuple) + 1;
    }

    split = str.find(settings.separator, offset);
    return split;
}

std::string TypeConverter::impl::extractFromEnclosingChars(std::string str, char left, char right, std::string typeName)
{
    size_t leftPos = str.find(left);
    if (leftPos == std::string::npos) {
        throw ImpossibleConversion("string", typeName,
                std::string("malformed string, cannot find left char: '") + left + "'");
    }
    if (str.find_first_not_of(' ') < leftPos) {
        throw ImpossibleConversion("string", typeName,
                std::string("malformed string, left char badly positionned: '") + left + "' is at pos " + ::TypeConverter::toString(leftPos) + "");
    }
    str.erase(0, leftPos + 1);

    size_t rightPos = str.find(right);
    if (rightPos == std::string::npos) {
        throw ImpossibleConversion("string", typeName,
                std::string("malformed string, cannot find right char: '") + right + "'");
    }
    if (str.find_last_not_of(' ') > rightPos) {
        throw ImpossibleConversion("string", typeName,
                std::string("malformed string, right char badly positionned: '") + right + "' is at pos " + ::TypeConverter::toString(rightPos) + "");
    }
    str.erase(rightPos);

    return str;
}

