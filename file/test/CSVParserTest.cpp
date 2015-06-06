#include <gtest/gtest.h>
#include <memory>
#include "../CSVParser.h"

class CSVParserTest : public testing::Test
{
public:
    void SetUp()
    {
        std::stringstream file;
        file << "# this, is, a, comment\n"
            << "A,\"B Bp\",C\n"
            << "\n"
            << "    \n"
            << "E,F,G #This is a comment\n"
            << "  ,H,I\n"
            << "J,  ,L M N\n"
            << ",,O\n"
            << "P,#Q,R";
        csv = std::unique_ptr<File::CSVParser>(new File::CSVParser(file));
    }

    std::unique_ptr<File::CSVParser> csv;
};

TEST_F( CSVParserTest, parseWithQuotes )
{
    auto line = csv->begin();
    auto word = line->begin();
    EXPECT_EQ("A", *word);
    EXPECT_EQ("B Bp", *(++word));
    EXPECT_EQ("C", *(++word));
    ASSERT_EQ( line->end(), ++word );
}

TEST_F( CSVParserTest, parseLineWithComment )
{
    auto line = csv->begin();
    ++line;
    auto word = line->begin();
    EXPECT_EQ("E", *word);
    EXPECT_EQ("F", *(++word));
    EXPECT_EQ("G", *(++word));
    ASSERT_EQ( line->end(), ++word );
}

TEST_F( CSVParserTest, parseEmptyColumn )
{
    auto line = csv->begin();
    ++line;
    ++line;
    auto word = line->begin();
    EXPECT_EQ("", *word);
    EXPECT_EQ("H", *(++word));
    EXPECT_EQ("I", *(++word));
    ASSERT_EQ( line->end(), ++word );
}

TEST_F( CSVParserTest, parseWithUnquotedSpaces )
{
    auto line = csv->begin();
    ++line;
    ++line;
    ++line;
    auto word = line->begin();
    EXPECT_EQ("J", *word);
    EXPECT_EQ("", *(++word));
    EXPECT_EQ("L M N", *(++word));
    ASSERT_EQ( line->end(), ++word );
}

TEST_F( CSVParserTest, parseWithTwoIncompleteColumns )
{
    auto line = csv->begin();
    ++line;
    ++line;
    ++line;
    ++line;
    auto word = line->begin();
    EXPECT_EQ("", *word);
    EXPECT_EQ("", *(++word));
    EXPECT_EQ("O", *(++word));
    ASSERT_EQ( line->end(), ++word );
}

TEST_F( CSVParserTest, parseWithMisleadingComment )
{
    auto line = csv->begin();
    ++line;
    ++line;
    ++line;
    ++line;
    ++line;
    auto word = line->begin();
    EXPECT_EQ("P", *word);
    EXPECT_EQ("", *(++word));
    ASSERT_EQ( line->end(), ++word );
}
