#include <gtest/gtest.h>
#include "sql/All.h"

#include <stdexcept>
#include <string>
#include <sstream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "lib/typeconverter/TypeConverter.h"
#include "lib/Datetime.h"

namespace dbobject {
    struct DummyLiteralObject {
        std::string s;
    };
}

namespace TypeConverter {
namespace impl {
    template<> struct TypeConverter<::dbobject::DummyLiteralObject> {
        static std::string toString(const ::dbobject::DummyLiteralObject& d, const Settings&)
        {
            return "string: " + d.s;
        }
    };
}
}

namespace dbobject {

using namespace SQL::Operators;

TEST( SQLClause, Literal )
{
    SQL::Literal l("hello");
    EXPECT_EQ( "'hello'", l() );
 
    SQL::Literal l2 = "hello"_l;
    EXPECT_EQ( "'hello'", l2() );
}

TEST( SQLClause, IntLiteral )
{
    SQL::Literal l(30);
    EXPECT_EQ( "30", l() );

    SQL::Literal l2 = 30_l;
    EXPECT_EQ( "30", l2() );
}

TEST( SQLClause, ExplicitIntLiteral )
{
    SQL::IntLiteral l(30);
    EXPECT_EQ( "30", l() );

    SQL::IntLiteral l2 = 30_l;
    EXPECT_EQ( "30", l2() );
}

TEST( SQLClause, DoubleLiteral )
{
    SQL::Literal l(303e-1);
    EXPECT_EQ( "30.3", l() );

    SQL::Literal l2 = 30.3_l;
    EXPECT_EQ( "30.3", l2() );
}

TEST( SQLClause, DateLiteral )
{
    SQL::Literal l(datetime::Date(2013, 12, 1));
    EXPECT_EQ( "'2013/12/1'", l() );
}

TEST( SQLClause, NewLiteralType )
{
    DummyLiteralObject d;
    d.s = "hello";

    SQL::Literal l(d);
    EXPECT_EQ( "'string: hello'", l() );
}

TEST( SQLClause, PolymorphicCopy )
{
    SQL::Literal l("hello");
    SQL::Literal l2(*static_cast<SQL::SimpleExpr*>(&l));
    EXPECT_EQ( "'hello'", l2() );
}

TEST( SQLClause, PolymorphicCopy2 )
{
    SQL::Literal l(1);
    SQL::Literal l2(*static_cast<SQL::SimpleExpr*>(&l));
    EXPECT_EQ( "1", l2() );
}

TEST( SQLClause, TableName )
{
    SQL::TableName t("yo");
    EXPECT_FALSE( t.hasSchema() );
    EXPECT_EQ( "`yo`", t() );
}

TEST( SQLClause, TableNameComplete )
{
    SQL::TableName t("hill", "yo");
    EXPECT_TRUE( t.hasSchema() );
    EXPECT_EQ( "`hill`", t.schema() );
    EXPECT_EQ( "`hill`.`yo`", t() );
    EXPECT_EQ( "`yo`", t.name() );
}

TEST( SQLClause, TableNameSytaxicSygar )
{
    SQL::TableName t = "hill"_s/"yo"_t;
    EXPECT_TRUE( t.hasSchema() );
    EXPECT_EQ( "`hill`", t.schema() );
    EXPECT_EQ( "`hill`.`yo`", t() );
    EXPECT_EQ( "`yo`", t.name() );
}

TEST( SQLClause, CopyTableName )
{
    SQL::TableName t1A("yo");
    SQL::TableName t1B(t1A);
    SQL::TableName t2A("hill"_s/"yo"_t);
    SQL::TableName t2B(t2A);
    EXPECT_EQ( "`yo`", t1B() );
    EXPECT_EQ( "`hill`.`yo`", t2B() );
}

TEST( SQLClause, CopyPtrTableName )
{
    SQL::TableName t1A = "yo"_t;
    SQL::TableName t1B(t1A);
    SQL::TableName t2A = "hill"_s/"yo"_t;
    SQL::TableName t2B(t2A);
    EXPECT_EQ( "`yo`", t1B() );
    EXPECT_EQ( "`hill`.`yo`", t2B() );
}

TEST( SQLClause, ColumnName )
{
    SQL::ColumnName c("yo");
    EXPECT_FALSE( c.hasSchema() );
    EXPECT_FALSE( c.hasTable() );
    EXPECT_EQ( "`yo`", c() );
    EXPECT_EQ( "`yo`", c.name() );
}

TEST( SQLClause, ColumnNameComplete )
{
    SQL::ColumnName c("hello", "hill", "yo");
    EXPECT_TRUE( c.hasSchema() );
    EXPECT_TRUE( c.hasTable() );
    EXPECT_EQ( "`hello`", c.schema() );
    EXPECT_EQ( "`hill`", c.table() );
    EXPECT_EQ( "`hello`.`hill`.`yo`", c() );
    EXPECT_EQ( "`yo`", c.name() );
}

TEST( SQLClause, ColumnNameSyntaxicSugar )
{
    SQL::ColumnName c("hello"_s/"hill"_t/"yo"_c);
    EXPECT_TRUE( c.hasSchema() );
    EXPECT_TRUE( c.hasTable() );
    EXPECT_EQ( "`hello`", c.schema() );
    EXPECT_EQ( "`hill`", c.table() );
    EXPECT_EQ( "`hello`.`hill`.`yo`", c() );
    EXPECT_EQ( "`yo`", c.name() );
}

TEST( SQLClause, Alias )
{
    SQL::Alias<SQL::Literal> alias("hello"_l, "hi");
    EXPECT_EQ( "'hello' AS `hi`", alias() );

    SQL::Alias<SQL::Literal> sugar = "hello"_l | "hi";
    EXPECT_EQ( "'hello' AS `hi`", sugar() );
}

TEST( SQLClause, AliasPolymorphism )
{
    SQL::Alias<SQL::Literal> alias(30_l, "hi");
    EXPECT_EQ( "30 AS `hi`", alias() );

    SQL::Alias<SQL::Literal> sugar = 30_l | "hi";
    EXPECT_EQ( "30 AS `hi`", sugar() );
}

TEST( SQLClause, Sort )
{
    SQL::Sort<SQL::ColumnName> ascsort("hello"_c);
    EXPECT_EQ( "`hello`", ascsort() );

    SQL::Sort<SQL::ColumnName> descsort("hello"_c, SQL::Direction::DESC);
    EXPECT_EQ( "`hello` DESC", descsort() );

    SQL::Sort<SQL::ColumnName> sugar = "hello"_c | SQL::Direction::ASC;
    EXPECT_EQ( "`hello`", sugar() );
}

TEST( SQLClause, Expression )
{
    SQL::Expression expr("hello");
    EXPECT_FALSE( expr.empty() );
    EXPECT_EQ( "hello", expr() );
}

TEST( SQLClause, Assignement )
{
    SQL::ColumnName left("hello");
    SQL::Literal right("hi");
    SQL::Assignement<SQL::ColumnName, SQL::Literal> assign(left, right);
    EXPECT_EQ( "`hello`", (*assign.left())() );
    EXPECT_EQ( "'hi'", (*assign.right())() );
    EXPECT_EQ( "`hello` = 'hi'", assign() );
}

TEST( SQLClause, AssignementWithString )
{
    SQL::ColumnName left("hello");
    SQL::Assignement<SQL::ColumnName, SQL::Literal> assign(left, "hi");
    EXPECT_EQ( "`hello`", (*assign.left())() );
    EXPECT_EQ( "'hi'", (*assign.right())() );
    EXPECT_EQ( "`hello` = 'hi'", assign() );
}

TEST( SQLClause, AssignementWithBool )
{
    SQL::ColumnName left("hello");
    SQL::Assignement<SQL::ColumnName, SQL::Literal> assign(left, true);
    EXPECT_EQ( "`hello`", (*assign.left())() );
    EXPECT_EQ( "true", (*assign.right())() );
    EXPECT_EQ( "`hello` = true", assign() );
}

TEST( SQLClause, AssignementWithInt )
{
    SQL::ColumnName left("hello");
    SQL::Assignement<SQL::ColumnName, SQL::Literal> assign(left, 1);
    EXPECT_EQ( left(), (*assign.left())() );
    EXPECT_EQ( "1", (*assign.right())() );
    EXPECT_EQ( "`hello` = 1", assign() );
}

TEST( SQLClause, AssignementSugar )
{
    auto assign = "hello"_c == SQL::Literal("hi");
    EXPECT_EQ( "`hello` = 'hi'", assign() );
}

TEST( SQLClause, AssignementSugarWithString )
{
    auto assign = "hello"_c == "hi"_l;
    EXPECT_EQ( "`hello` = 'hi'", assign() );
}

TEST( SQLClause, AssignementSugarWithBool )
{
    auto assign = "hello"_c == SQL::Literal(true);
    EXPECT_EQ( "`hello` = true", assign() );
}


TEST( SQLClause, AssignementSugarWithInt )
{
    auto assign = "hello"_c == 1_l;
    EXPECT_EQ( "`hello` = 1", assign() );
}
TEST( SQLClause, JoinedTableDefault )
{
    SQL::JoinedTable joinedTable("table"_t);
    EXPECT_EQ( "`table`", joinedTable.table() );
    EXPECT_EQ( SQL::JoinedTable::LEFT, joinedTable.joinType() );
    EXPECT_EQ( "LEFT JOIN `table`", joinedTable() );
}

TEST( SQLClause, JoinedTableSugar )
{
    SQL::JoinedTable joinedTable = "table"_t | "t" | SQL::JoinedTable::RIGHT;
    EXPECT_EQ( "`table`", joinedTable.table() );
    EXPECT_EQ( SQL::JoinedTable::RIGHT, joinedTable.joinType() );
    EXPECT_EQ( "RIGHT JOIN `table` AS `t`", joinedTable() );
}

TEST( SQLClause, Join )
{
    SQL::Join join1("table"_t | SQL::JoinedTable::LEFT, "hello"_c == "hi"_c);
    EXPECT_EQ( "LEFT JOIN `table` ON `hello` = `hi`", join1() );

    SQL::Join join2("table2"_t, "table2"_t/"c1"_c == "table1"_t/"c2"_c);
    EXPECT_EQ( "LEFT JOIN `table2` ON `table2`.`c1` = `table1`.`c2`", join2());

    SQL::Join join3("schema1"_s/"table3"_t | "t3" | SQL::JoinedTable::RIGHT, "hop"_c == "hey"_c);

    EXPECT_EQ( "RIGHT JOIN `schema1`.`table3` AS `t3` ON `hop` = `hey`", join3() );
}

TEST( SQLClause, List )
{
    SQL::List<SQL::Literal> list({"a", "b", 3});
    ASSERT_EQ( "'a', 'b', 3", list() );

    auto value = list.begin();
    EXPECT_EQ( "'a'", (**value)() );
    ++value;
    EXPECT_EQ( "'b'", (**value)() );
    ++value;
    EXPECT_EQ( "3", (**value)() );
}

TEST( SQLClause, AssignementList )
{
    SQL::List<SQL::Assignement<SQL::ColumnName, SQL::Literal>> list({"a"_c == 1_l, "b"_c == "b"_l, "c"_c == SQL::Literal(false)});
    ASSERT_EQ( "`a` = 1, `b` = 'b', `c` = false", list() );

    auto assignement = list.begin();
    EXPECT_EQ( "`a`", (*(*assignement)->left())() );
    EXPECT_EQ( "1", (*(*assignement)->right())() );
    ++assignement;
    EXPECT_EQ( "`b`", (*(*assignement)->left())() );
    EXPECT_EQ( "'b'", (*(*assignement)->right())() );
    ++assignement;
    EXPECT_EQ( "`c`", (*(*assignement)->left())() );
    EXPECT_EQ( "false", (*(*assignement)->right())() );
}

TEST( SQLClause, And )
{
    SQL::Expression expr("a"_c == 1_l && "b"_c == "b"_l);
 
    ASSERT_EQ("`a` = 1 AND `b` = 'b'", expr());
}

TEST( SQLClause, AndEmpty )
{
    SQL::Expression expr1(SQL::Expression() && "a"_c == 1_l);
    SQL::Expression expr2("a"_c == 1_l && SQL::Expression());
 
    ASSERT_EQ("`a` = 1", expr1());
    ASSERT_EQ("`a` = 1", expr2());
}

TEST( SQLClause, Or )
{
    SQL::Expression expr("a"_c == 1_l || "b"_c == "b"_l);
 
    ASSERT_EQ("`a` = 1 OR `b` = 'b'", expr());
}

TEST( SQLClause, OrEmpty )
{
    SQL::Expression expr1(SQL::Expression() || "a"_c == 1_l);
    SQL::Expression expr2("a"_c == 1_l || SQL::Expression());
 
    ASSERT_EQ("`a` = 1", expr1());
    ASSERT_EQ("`a` = 1", expr2());
}

TEST( SQLClause, Xor )
{
    SQL::Expression expr("a"_c == 1_l ^ "b"_c == "b"_l);
 
    ASSERT_EQ("`a` = 1 XOR `b` = 'b'", expr());
}

TEST( SQLClause, XorEmpty )
{
    SQL::Expression expr1(SQL::Expression() ^ "a"_c == 1_l);
    SQL::Expression expr2("a"_c == 1_l ^ SQL::Expression());
 
    ASSERT_EQ("`a` = 1", expr1());
    ASSERT_EQ("`a` = 1", expr2());
}

}
