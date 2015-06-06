#include <gtest/gtest.h>
#include "functional/MapHelper.hxx"

using namespace dbobject;

TEST( MapHelperTest, zipIntInt )
{
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {1, 2, 3};
    std::map<int,int> zip = {{1,1}, {2,2}, {3,3}};

    auto result = MapHelper::zip(a.begin(), a.end(), b.begin(), b.end());
    EXPECT_EQ( zip, result );
}

TEST( MapHelperTest, zipIntString )
{
    std::vector<int> a = {1, 2, 3};
    std::vector<std::string> b = {"a", "b", "c"};
    std::map<int,std::string> zip = {{1,"a"}, {2,"b"}, {3,"c"}};

    auto result = MapHelper::zip(a.begin(), a.end(), b.begin(), b.end());
    EXPECT_EQ( zip, result );
}

TEST( MapHelperTest, zipASmaller )
{
    std::vector<int> a = {1, 2};
    std::vector<std::string> b = {"a", "b", "c"};
    std::map<int,std::string> zip = {{1,"a"}, {2,"b"}};

    auto result = MapHelper::zip(a.begin(), a.end(), b.begin(), b.end());
    EXPECT_EQ( zip, result );
}

TEST( MapHelperTest, zipBSmaller )
{
    std::vector<int> a = {1, 2, 3};
    std::vector<std::string> b = {"a", "b"};
    std::map<int,std::string> zip = {{1,"a"}, {2,"b"}};

    auto result = MapHelper::zip(a.begin(), a.end(), b.begin(), b.end());
    EXPECT_EQ( zip, result );
}

TEST( MapHelperTest, keys )
{
    std::map<int,std::string> map = {{1,"a"}, {2,"b"}, {3,"c"}};
    std::vector<int> keys = {1, 2, 3};

    auto result = MapHelper::keys(map);
    EXPECT_EQ( keys, result );
}

TEST( MapHelperTest, values )
{
    std::map<int,std::string> map = {{1,"a"}, {2,"b"}, {3,"c"}};
    std::vector<std::string> values = {"a", "b", "c"};

    auto result = MapHelper::values(map);
    EXPECT_EQ( values, result );
}

TEST( MapHelperTest, only )
{
    std::map<int,std::string> map = {{1,"a"}, {2,"b"}, {3,"c"}};
    std::vector<int> keys = {1};
    std::map<int,std::string> only = {{1,"a"}};

    auto result = MapHelper::only(map, keys);
    EXPECT_EQ( only, result );
}

TEST( MapHelperTest, exclude )
{
    std::map<int,std::string> map = {{1,"a"}, {2,"b"}, {3,"c"}};
    std::vector<int> keys = {1};
    std::map<int,std::string> exclude = {{2,"b"}, {3,"c"}};

    auto result = MapHelper::exclude(map, keys);
    EXPECT_EQ( exclude, result );
}

TEST( MapHelperTest, concat2 )
{
    std::map<std::string,std::string> map = {{"1","a"}, {"2","b"}, {"3","c"}};
    std::string concat = "1=a,2=b,3=c";

    auto result = MapHelper::concat(map, "=", ",");
    EXPECT_EQ( concat, result );
}

TEST( MapHelperTest, concat4 )
{
    std::map<std::string,std::string> map = {{"1","a"}, {"2","b"}, {"3","c"}};
    std::string concat = "||1||=.a.,||2||=.b.,||3||=.c.";

    auto result = MapHelper::concat(map, "=", ",", "||", ".");
    EXPECT_EQ( concat, result );
}

TEST( MapHelperTest, concat6 )
{
    std::map<std::string,std::string> map = {{"1","a"}, {"2","b"}, {"3","c"}};
    std::string concat = "||1|=..a.,||2|=..b.,||3|=..c.";

    auto result = MapHelper::concat(map, "=", ",", "||", "|", "..", ".");
    EXPECT_EQ( concat, result );
}
