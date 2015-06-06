#include <gtest/gtest.h>
#include "TypeConverterTest.h"

TEST( TypeConverterTest, intFromString )
{
    test_conversions_from_string<int>({
        { "3",     3    },
        { "-3",    -3   },
        { "-0",    0    },
        { "0",     0    },
        { "125",   125  },
        { "-125",  -125 },
        { "3.3",   3    },
        { "3,3",   3    },
        { "3-3",   3    },
        { "3 - 3", 3    },
        { "3 3",   3    },
    });
}

TEST( TypeConverterTest, intToString )
{
    test_conversions_to_string<int>({
        { 3,    "3"    },
        { -3,   "-3"   },
        { -0,   "0"    },
        { 0,    "0"    },
        { 125,  "125"  },
        { -125, "-125" },
    });
}

TEST( TypeConverterTest, intBadFormat )
{
    test_bad_conversions_from_str<int>({
        "a",
    });
}

TEST( TypeConverterTest, doubleFromString )
{
    test_conversions_from_string<double>({
        { "3",        3.0      },
        { "3.2",      3.2      },
        { "125.125",  125.125  },
        { "-3",       -3.0     },
        { "-3.2",     -3.2     },
        { "-125.125", -125.125 },
        { "1.1.1",    1.1      },
        { "0.-3",     0        },
        { "3-3",      3        },
        { "3 - 3",    3        },
        { "3 3",      3        }
    });
}

TEST( TypeConverterTest, doubleToString )
{
    test_conversions_to_string<double>({
        { 3.0,      "3"        },
        { 3.2,      "3.2"      },
        { 125.125,  "125.125"  },
        { -3.0,     "-3"       },
        { -3.2,     "-3.2"     },
        { -125.125, "-125.125" }
    });
}

TEST( TypeConverterTest, doubleBadFormat )
{
    test_bad_conversions_from_str<double>({
        "a",
    });
}

TEST( TypeConverterTest, charFromString )
{
    test_conversions_from_string<char>({
        { "a",  'a' },
        { "2",  '2' },
        { "&",  '&' },
        { "ab", 'a' },
    });
}

TEST( TypeConverterTest, charToString )
{
    test_conversions_to_string<char>({
        { 'a', "a" },
        { '2', "2" },
        { '&', "&" }
    });
}

TEST( TypeConverterTest, boolFromString )
{
    test_conversions_from_string<bool>({
        { "true",  true  },
        { "false", false }
    });
}

TEST( TypeConverterTest, boolToString )
{
    test_conversions_to_string<bool>({
        { true,  "true"  },
        { false, "false" }
    });
}

TEST( TypeConverterTest, boolBadFormat )
{
    test_bad_conversions_from_str<bool>({
        "wtf"
    });
}

TEST( TypeConverterTest, vectorFromString )
{
    using TypeConverter::fromString;
    typedef std::vector<std::tuple<int,char>> vec_tup;
    EXPECT_EQ( (std::vector<int>{1, 2, 3}), (fromString<std::vector<int>>("  [1,2,3]")) );
    EXPECT_EQ( (std::vector<int>{1}),       (fromString<std::vector<int>>("[1]  "))     );
    EXPECT_EQ( (vec_tup{std::make_tuple(1,'a'), std::make_tuple(2,'b'), std::make_tuple(3,'c')}), (fromString<vec_tup>("  [<1, a>, < 2,b > , <3,c>]  ")) );
}

TEST( TypeConverterTest, vectorToString )
{
    using TypeConverter::toString;
    EXPECT_EQ( "[1,2,3]", (toString(std::vector<int>{1, 2, 3})) );
    EXPECT_EQ( "[]",      (toString(std::vector<int>{})) );
    EXPECT_EQ( "[<1,a>,<2,b>,<3,c>]", (toString(std::vector<std::tuple<int,char>>{std::make_tuple(1,'a'), std::make_tuple(2,'b'), std::make_tuple(3,'c')})) );
}

TEST( TypeConverterTest, vectorBadFormat )
{
    using TypeConverter::fromString;
    using TypeConverter::ImpossibleConversion;
    //EXPECT_THROW( (fromString<std::vector<int>>("[1, 2, 3", ',')),  ImpossibleConversion );
    //EXPECT_THROW( (fromString<std::vector<int>>("1, 2, 3]", ',')),  ImpossibleConversion );
    //EXPECT_THROW( (fromString<std::vector<int>>("[1, , 3]", ',')),  ImpossibleConversion );
    EXPECT_THROW( (fromString<std::vector<int>>("[1, 2, ]", ',')),  ImpossibleConversion );
    //EXPECT_THROW( (fromString<std::vector<int>>("[1, 2, a]", ',')), ImpossibleConversion );
    //EXPECT_THROW( (fromString<std::vector<int>>("[, ]", ',')),      ImpossibleConversion );
}

TEST( TypeConverterTest, tupleFromString )
{
    typedef std::tuple<int, char, bool> tuple_1;
    typedef std::tuple<int, std::vector<double>, bool> tuple_2;
    using TypeConverter::fromString;

    auto tup1 = std::make_tuple(2, 'b', true);
    EXPECT_EQ( tup1, (fromString<tuple_1>("<2,b,true>", ',')) );
    EXPECT_EQ( tup1, (fromString<tuple_1>("<2, b, true>", ',')) );
    EXPECT_EQ( tup1, (fromString<tuple_1>("<2,   b,  true>", ',')) );

    auto tup2 = std::make_tuple(2, std::vector<double>{1.2, 2.3}, true);
    EXPECT_EQ( tup2, (fromString<tuple_2>("<2+[1.2+2.3]+true>", '+')) );
    EXPECT_EQ( tup2, (fromString<tuple_2>("  <  2  +  [    1.2 +  2.3  ]  + true >  ", '+')) );
}

TEST( TypeConverterTest, tupleToString )
{
    using TypeConverter::toString;

    auto tup1 = std::make_tuple(2, 'b', true);
    EXPECT_EQ( "<2+b+true>",  toString(tup1, '+') );

    auto tup2 = std::make_tuple(2, true);
    EXPECT_EQ( "<2,true>",       toString(tup2, ',') );

    auto tup3 = std::make_tuple(2, std::vector<int>{1,2,3}, 1.2);
    EXPECT_EQ( "<2,[1,2,3],1.2>", toString(tup3, ',') );
}

TEST( TypeConverterTest, tupleBadFormat )
{
    typedef std::tuple<int, char, bool> tuple_1;
    typedef std::tuple<int, std::vector<double>, bool> tuple_v;

    using TypeConverter::fromString;
    using TypeConverter::ImpossibleConversion;
    EXPECT_THROW( (fromString<tuple_1>("<2, a, true", ',')),         ImpossibleConversion );
    EXPECT_THROW( (fromString<tuple_1>("2, a, true>", ',')),         ImpossibleConversion );
    EXPECT_THROW( (fromString<tuple_1>("<a, a, a>", ',')),           ImpossibleConversion );
    EXPECT_THROW( (fromString<tuple_1>("<a, a, true>", ',')),        ImpossibleConversion );
    EXPECT_THROW( (fromString<tuple_1>("<2, a, true,>", ',')),       ImpossibleConversion );
    EXPECT_THROW( (fromString<tuple_1>("<2, a, true, >", ',')),      ImpossibleConversion );
    EXPECT_THROW( (fromString<tuple_1>("<2, a, a>", ',')),           ImpossibleConversion );
    EXPECT_THROW( (fromString<tuple_1>("<2, a>", ',')),              ImpossibleConversion );
    EXPECT_THROW( (fromString<tuple_1>("<2, a, true, 3>", ',')),     ImpossibleConversion );
    EXPECT_THROW( (fromString<tuple_v>("<2, [1.2, a], true>", ',')), ImpossibleConversion );
}

