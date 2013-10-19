#include <gtest/gtest.h>
#include <functional>
#include "functional/VectorHelper.hxx"

TEST( VectorHelperTest, concat )
{
    std::vector<std::string> a = {"a", "b", "c"};
    std::vector<std::string> b = {"1", "2", "3"};
    std::vector<std::string> merge = {"a", "b", "c", "1", "2", "3"};

    auto result = dbobject::VectorHelper::merge(a, b);
    EXPECT_EQ( merge, result );
}

TEST( VectorHelperTest, concat1 )
{
    std::vector<std::string> v = {"a", "b", "c"};
    std::string concat = "a,,b,,c";

    auto result = dbobject::VectorHelper::concat(v, ",,");
    EXPECT_EQ( concat, result );
}

TEST( VectorHelperTest, concat2 )
{
    std::vector<std::string> v = {"a", "b", "c"};
    std::string concat = "|a|,,|b|,,|c|";

    auto result = dbobject::VectorHelper::concat(v, ",,", "|");
    EXPECT_EQ( concat, result );
}

TEST( VectorHelperTest, concat3 )
{
    std::vector<std::string> v = {"a", "b", "c"};
    std::string concat = "'a|,,'b|,,'c|";

    auto result = dbobject::VectorHelper::concat(v, ",,", "'", "|");
    EXPECT_EQ( concat, result );
}

TEST( VectorHelperTest, map )
{
    std::vector<int> v = {1, 2, 3};
    std::vector<int> expect = {3, 4, 5};

    auto result = dbobject::VectorHelper::map(v, std::bind(std::plus<int>(), std::placeholders::_1, 2));
    EXPECT_EQ( expect, result );
}
