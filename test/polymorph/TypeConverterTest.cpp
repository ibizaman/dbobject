#include <gtest/gtest.h>
#include "polymorph/TypeConverter.h"
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace dbobject;

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

TEST( TypeConverterTest, boostTime )
{
    boost::posix_time::time_duration time(14,30,0);
    std::string time_str = "14:30:00";

    EXPECT_EQ( time_str, TypeConverter::toString(time) );
    EXPECT_EQ( time, TypeConverter::fromString<boost::posix_time::time_duration>(time_str) );
}

TEST( TypeConverterTest, boostDate )
{
    boost::gregorian::date date(2002,1,10);
    std::string date_str = "2002-1-10";

    EXPECT_EQ( date_str, TypeConverter::toString(date) );
    EXPECT_EQ( date, TypeConverter::fromString<boost::gregorian::date>(date_str) );
}

TEST( TypeConverterTest, boostDatetime )
{
    boost::posix_time::ptime datetime(
            boost::gregorian::date(2002,1,10),
            boost::posix_time::time_duration(14,30,0)
        );
    std::string datetime_str = "2002-1-10T14:30:00";

    EXPECT_EQ( datetime_str, TypeConverter::toString(datetime) );
    EXPECT_EQ( datetime, TypeConverter::fromString<boost::posix_time::ptime>(datetime_str) );
}

