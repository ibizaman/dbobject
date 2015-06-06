#ifndef TYPECONVERTERTEST_H
#define TYPECONVERTERTEST_H

#include "../TypeConverter.h"
#include "test/Utils.h"
#include <functional>
#include <string>

using std::placeholders::_1;

template<typename T>
void test_conversions_from_string(std::initializer_list<std::pair<std::string, T>> list)
{
    expect_equals<std::string, T>(std::bind(
            static_cast<T(*)(const std::string&, TypeConverter::Settings)>(TypeConverter::fromString<T>), _1, TypeConverter::Settings()
        ), list);
}

template<typename T>
void test_conversions_to_string(std::initializer_list<std::pair<T, std::string>> list)
{
    expect_equals<T, std::string>(std::bind(
            static_cast<std::string(*)(T, TypeConverter::Settings)>(TypeConverter::toString<T>), _1, TypeConverter::Settings()
        ), list);
}

template<typename T>
void test_bad_conversions_from_str(std::initializer_list<std::string> list)
{
    expect_thrown<std::string, TypeConverter::ImpossibleConversion>(std::bind(
            static_cast<T(*)(const std::string&, TypeConverter::Settings)>(TypeConverter::fromString<T>), _1, TypeConverter::Settings()
        ), list);
}

#endif
