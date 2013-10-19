#include <gtest/gtest.h>
#include "polymorph/TypeConverter.h"

namespace dbobject {

TEST( TypeConverterTest, fromString )
{
    int a = 3;
    double b = 4.4;
    char c = 'a';

    EXPECT_EQ( a, TypeConverter::fromString<int>("3") );
    EXPECT_EQ( b, TypeConverter::fromString<double>("4.4") );
    EXPECT_EQ( c, TypeConverter::fromString<char>("a") );
}

TEST( TypeConverterTest, boolFromString )
{
    bool d = true;

    EXPECT_EQ( d, TypeConverter::fromString<bool>("true") );
    EXPECT_EQ( !d, TypeConverter::fromString<bool>("false") );
    EXPECT_EQ( d, TypeConverter::fromString<bool>("1", TypeConverter::BOOLNUM) );
    EXPECT_EQ( !d, TypeConverter::fromString<bool>("0", TypeConverter::BOOLNUM) );
}

TEST( TypeConverterTest, toString )
{
    int a = 3;
    double b = 4.4;
    char c = 'a';

    EXPECT_EQ( "3", TypeConverter::toString(a) );
    EXPECT_EQ( "4.4", TypeConverter::toString(b) );
    EXPECT_EQ( "a", TypeConverter::toString(c) );
}

TEST( TypeConverterTest, boolToString )
{
    bool d = true;

    EXPECT_EQ( "true", TypeConverter::toString(d) );
    EXPECT_EQ( "false", TypeConverter::toString(!d) );
    EXPECT_EQ( "1", TypeConverter::toString(d, TypeConverter::BOOLNUM) );
    EXPECT_EQ( "0", TypeConverter::toString(!d, TypeConverter::BOOLNUM) );
}

}
