#include <gtest/gtest.h>
#include "../FileIO.h"

TEST( FileIOTest, stripComments )
{
    std::string str = " hello # you ";
    std::string expect = " hello ";

    ASSERT_EQ( expect, File::stripComments(str) );
}

TEST( FileIOTest, stripCommentsNo )
{
    std::string str = " hello  ";
    std::string expect = " hello  ";

    ASSERT_EQ( expect, File::stripComments(str) );
}

TEST( FileIOTest, stripWhitespace )
{
    std::string str = "  hello # you  ";
    std::string expect = "hello # you";

    ASSERT_EQ( expect, File::stripWhitespace(str) );
}

TEST( FileIOTest, stripWhitespaceNoWhitespace )
{
    std::string str = "hello # you";
    std::string expect = "hello # you";

    ASSERT_EQ( expect, File::stripWhitespace(str) );
}

TEST( FileIOTest, stripWhitespaceOnly )
{
    std::string str = "    ";
    std::string expect = "";

    ASSERT_EQ( expect, File::stripWhitespace(str) );
}

TEST( FileIOTest, stripWhitespaceEmpty )
{
    std::string str = "";
    std::string expect = "";

    ASSERT_EQ( expect, File::stripWhitespace(str) );
}

TEST( FileIOTest, parseSuccess )
{
    std::stringstream raw;
    raw << "varA = valueA\n"
        << "varB= valueB";

    auto map = File::parseToPropertiesMap(raw);

    ASSERT_EQ(1, map.count("varA"));
    EXPECT_EQ("valueA", map.at("varA"));

    ASSERT_EQ(1, map.count("varB"));
    EXPECT_EQ("valueB", map.at("varB"));
}

TEST( FileIOTest, parseEmpty )
{
    std::stringstream raw;

    auto map = File::parseToPropertiesMap(raw);

    ASSERT_EQ( 0, map.size() );
}

TEST( FileIOTest, parseCorruptNoEqual )
{
    std::stringstream raw;
    raw << "varA=valueA\n"
        << "varB\n"
        << "varC=valueC\n";

    auto map = File::parseToPropertiesMap(raw);

    ASSERT_EQ(1, map.count("varA"));
    EXPECT_EQ("valueA", map.at("varA"));

    ASSERT_EQ(0, map.count("varB"));

    ASSERT_EQ(1, map.count("varC"));
    EXPECT_EQ("valueC", map.at("varC"));
}

TEST( FileIOTest, parseCorruptOnlyValue )
{
    std::stringstream raw;
    raw << "varA=valueA\n"
        << "=valueB\n"
        << "varC=valueC\n";

    auto map = File::parseToPropertiesMap(raw);

    ASSERT_EQ(1, map.count("varA"));
    EXPECT_EQ("valueA", map.at("varA"));

    ASSERT_EQ(0, map.count("varB"));

    ASSERT_EQ(0, map.count("valueB"));

    ASSERT_EQ(1, map.count("varC"));
    EXPECT_EQ("valueC", map.at("varC"));
}

TEST( FileIOTest, parseWithSpace )
{
    std::stringstream raw;
    raw << "varA=valueA\n"
        << ""
        << "varC=valueC\n";

    auto map = File::parseToPropertiesMap(raw);

    ASSERT_EQ(1, map.count("varA"));
    EXPECT_EQ("valueA", map.at("varA"));

    ASSERT_EQ(1, map.count("varC"));
    EXPECT_EQ("valueC", map.at("varC"));
}

TEST( FileIOTest, parseWithComments )
{
    std::stringstream raw;
    raw << "# This is a comment\n"
        << "varA=valueA  # Second comment\n"
        << "   # This is another comment\n"
        << "varC=valueC#This is a comment\n"
        << "#This is a third comment\n";

    auto map = File::parseToPropertiesMap(raw);

    ASSERT_EQ(1, map.count("varA"));
    EXPECT_EQ("valueA", map.at("varA"));

    ASSERT_EQ(1, map.count("varC"));
    EXPECT_EQ("valueC", map.at("varC"));
}

TEST( FileIOTest, safeGetline )
{
    std::string line;
    std::stringstream stream;
    stream << "line feed\nline feed2\n"
           << "cariage\rreturn\r\n"
           << "last line";
 
    File::safeGetline(stream, line);
    EXPECT_EQ("line feed", line);
 
    File::safeGetline(stream, line);
    EXPECT_EQ("line feed2", line);
 
    File::safeGetline(stream, line);
    EXPECT_EQ("cariage", line);
 
    File::safeGetline(stream, line);
    EXPECT_EQ("return", line);
 
    File::safeGetline(stream, line);
    EXPECT_EQ("last line", line);
}
