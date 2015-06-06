#pragma once

#include <string>
#include <stdexcept>
#include <tuple>
#include <vector>


namespace TypeConverter {
    struct Settings {
        Settings();
        Settings(char separator);
        Settings(char separator, char leftVector, char rightVector, char leftTuple, char rightTuple);

        char separator = ',';
        char leftVector = '[';
        char rightVector = ']';
        char leftTuple = '<';
        char rightTuple = '>';
    };

    struct ImpossibleConversion : public std::logic_error {
        ImpossibleConversion(std::string conversionType, std::string givenValue, std::string reason);
        const std::string conversionType;
        const std::string givenValue;
        const std::string reason;
    };

    // these functions can throw an ImpossibleConversion exception if
    // the string is not in the expected format
    template<typename T>
    T fromString(const std::string&);
    template<typename T>
    T fromString(const std::string&, Settings);
    template<typename T>
    T fromString(const std::string&, char separator);

    template<typename T>
    std::string toString(T);
    template<typename T>
    std::string toString(T, Settings);
    template<typename T>
    std::string toString(T, char separator);

namespace impl {

    template<typename T> struct TypeConverter {
        static T fromString(const std::string&, const Settings&);
        static std::string toString(T, const Settings&);
    };

    template<> struct TypeConverter<bool> {
        static bool fromString(const std::string&, const Settings&);
        static std::string toString(bool, const Settings&);
    };

    template<typename T> struct TypeConverter<std::vector<T>> {
        static std::vector<T> fromString(std::string, const Settings&);
        static std::string toString(const std::vector<T>&, const Settings&);
    };

    template<typename... T> struct TypeConverter<std::tuple<T...>> {
        static std::tuple<T...> fromString(std::string, const Settings&);
        static std::string toString(const std::tuple<T...>&, const Settings&);
    };

    template<typename T>
    std::tuple<T> fromStringTyped(const std::string&, const Settings&);
    template<typename T, typename T2, typename... Rest>
    std::tuple<T, T2, Rest...> fromStringTyped(const std::string&, const Settings&);

    template<typename Tup, int I = 0>
    auto toStringTyped(const Tup&, const Settings&)
        -> typename std::enable_if<I == std::tuple_size<Tup>::value - 1, std::string>::type;
    template<typename Tup, int I = 0>
    auto toStringTyped(const Tup&, const Settings&)
        -> typename std::enable_if<I != std::tuple_size<Tup>::value - 1, std::string>::type;

    size_t getNextSeparator(const std::string&, const Settings&);
    std::string extractFromEnclosingChars(std::string, char, char, std::string);

}
}

#include "TypeConverter.hpp"
