#include <gtest/gtest.h>
#include "sql/All.h"

#include <stdexcept>
#include <string>
#include <sstream>

namespace dbobject {

using namespace SQL::Operators;

TEST( SQLClause, Literal )
{
    SQL::Literal l("hello");
    ASSERT_EQ( "'hello'", l() );
    
    SQL::Literal l2 = "hello"_l;
    ASSERT_EQ( "'hello'", l2() );
}

TEST( SQLClause, IntLiteral )
{
    SQL::Literal l(30);
    ASSERT_EQ( "30", l() );

    SQL::Literal l2 = 30_l;
    ASSERT_EQ( "30", l2() );
}

TEST( SQLClause, ExplicitIntLiteral )
{
    SQL::IntLiteral l(30);
    ASSERT_EQ( "30", l() );

    SQL::IntLiteral l2 = 30_l;
    ASSERT_EQ( "30", l2() );
}

TEST( SQLClause, DoubleLiteral )
{
    SQL::Literal l(303e-1);
    ASSERT_EQ( "30.3", l() );

    SQL::Literal l2 = 30.3_l;
    ASSERT_EQ( "30.3", l2() );
}

TEST( SQLClause, PolymorphicCopy )
{
    SQL::Literal l("hello");
    SQL::Literal l2(*static_cast<SQL::SimpleExpr*>(&l));
    ASSERT_EQ( "'hello'", l2() );
}

TEST( SQLClause, PolymorphicCopy2 )
{
    SQL::Literal l(1);
    SQL::Literal l2(*static_cast<SQL::SimpleExpr*>(&l));
    ASSERT_EQ( "1", l2() );
}

TEST( SQLClause, TableName )
{
    SQL::TableName t("yo");
    ASSERT_FALSE( t.hasSchema() );
    ASSERT_EQ( "`yo`", t() );
}

TEST( SQLClause, TableNameComplete )
{
    SQL::TableName t("hill", "yo");
    ASSERT_TRUE( t.hasSchema() );
    ASSERT_EQ( "`hill`", t.schema() );
    ASSERT_EQ( "`hill`.`yo`", t() );
    ASSERT_EQ( "`yo`", t.name() );
}

TEST( SQLClause, TableNameSytaxicSygar )
{
    SQL::TableName t = "hill"_s/"yo"_t;
    ASSERT_TRUE( t.hasSchema() );
    ASSERT_EQ( "`hill`", t.schema() );
    ASSERT_EQ( "`hill`.`yo`", t() );
    ASSERT_EQ( "`yo`", t.name() );
}

TEST( SQLClause, CopyTableName )
{
    SQL::TableName t1A("yo");
    SQL::TableName t1B(t1A);
    SQL::TableName t2A("hill"_s/"yo"_t);
    SQL::TableName t2B(t2A);
    ASSERT_EQ( "`yo`", t1B() );
    ASSERT_EQ( "`hill`.`yo`", t2B() );
}

TEST( SQLClause, CopyPtrTableName )
{
    SQL::TableName t1A = "yo"_t;
    SQL::TableName t1B(t1A);
    SQL::TableName t2A = "hill"_s/"yo"_t;
    SQL::TableName t2B(t2A);
    ASSERT_EQ( "`yo`", t1B() );
    ASSERT_EQ( "`hill`.`yo`", t2B() );
}

TEST( SQLClause, ColumnName )
{
    SQL::ColumnName c("yo");
    ASSERT_FALSE( c.hasSchema() );
    ASSERT_FALSE( c.hasTable() );
    ASSERT_EQ( "`yo`", c() );
    ASSERT_EQ( "`yo`", c.name() );
}

TEST( SQLClause, ColumnNameComplete )
{
    SQL::ColumnName c("hello", "hill", "yo");
    ASSERT_TRUE( c.hasSchema() );
    ASSERT_TRUE( c.hasTable() );
    ASSERT_EQ( "`hello`", c.schema() );
    ASSERT_EQ( "`hill`", c.table() );
    ASSERT_EQ( "`hello`.`hill`.`yo`", c() );
    ASSERT_EQ( "`yo`", c.name() );
}

TEST( SQLClause, ColumnNameSyntaxicSugar )
{
    SQL::ColumnName c("hello"_s/"hill"_t/"yo"_c);
    ASSERT_TRUE( c.hasSchema() );
    ASSERT_TRUE( c.hasTable() );
    ASSERT_EQ( "`hello`", c.schema() );
    ASSERT_EQ( "`hill`", c.table() );
    ASSERT_EQ( "`hello`.`hill`.`yo`", c() );
    ASSERT_EQ( "`yo`", c.name() );
}

TEST( SQLClause, Alias )
{
    SQL::Alias<SQL::Literal> alias("hello"_l, "hi");
    ASSERT_EQ( "'hello' AS `hi`", alias() );

    SQL::Alias<SQL::Literal> sugar = "hello"_l | "hi";
    ASSERT_EQ( "'hello' AS `hi`", sugar() );
}

TEST( SQLClause, AliasPolymorphism )
{
    SQL::Alias<SQL::Literal> alias(30_l, "hi");
    ASSERT_EQ( "30 AS `hi`", alias() );

    SQL::Alias<SQL::Literal> sugar = 30_l | "hi";
    ASSERT_EQ( "30 AS `hi`", sugar() );
}

TEST( SQLClause, Sort )
{
    SQL::Sort<SQL::ColumnName> ascsort("hello"_c);
    ASSERT_EQ( "`hello`", ascsort() );

    SQL::Sort<SQL::ColumnName> descsort("hello"_c, SQL::Direction::DESC);
    ASSERT_EQ( "`hello` DESC", descsort() );

    SQL::Sort<SQL::ColumnName> sugar = "hello"_c | SQL::Direction::ASC;
    ASSERT_EQ( "`hello`", sugar() );
}

TEST( SQLClause, Expression )
{
    SQL::Expression expr("hello");
    ASSERT_FALSE( expr.empty() );
    ASSERT_EQ( "hello", expr() );
}

TEST( SQLClause, Assignement )
{
    SQL::ColumnName left("hello");
    SQL::Literal right("hi");
    SQL::Assignement<SQL::ColumnName, SQL::Literal> assign(left, right);
    ASSERT_EQ( "`hello`", (*assign.left())() );
    ASSERT_EQ( "'hi'", (*assign.right())() );
    ASSERT_EQ( "`hello` = 'hi'", assign() );
}

TEST( SQLClause, AssignementWithString )
{
    SQL::ColumnName left("hello");
    SQL::Assignement<SQL::ColumnName, SQL::Literal> assign(left, "hi");
    ASSERT_EQ( "`hello`", (*assign.left())() );
    ASSERT_EQ( "'hi'", (*assign.right())() );
    ASSERT_EQ( "`hello` = 'hi'", assign() );
}

TEST( SQLClause, AssignementWithBool )
{
    SQL::ColumnName left("hello");
    SQL::Assignement<SQL::ColumnName, SQL::Literal> assign(left, true);
    ASSERT_EQ( "`hello`", (*assign.left())() );
    ASSERT_EQ( "true", (*assign.right())() );
    ASSERT_EQ( "`hello` = true", assign() );
}

TEST( SQLClause, AssignementWithInt )
{
    SQL::ColumnName left("hello");
    SQL::Assignement<SQL::ColumnName, SQL::Literal> assign(left, 1);
    ASSERT_EQ( left(), (*assign.left())() );
    ASSERT_EQ( "1", (*assign.right())() );
    ASSERT_EQ( "`hello` = 1", assign() );
}

TEST( SQLClause, AssignementSugar )
{
    auto assign = "hello"_c == SQL::Literal("hi");
    ASSERT_EQ( "`hello` = 'hi'", assign() );
}

TEST( SQLClause, AssignementSugarWithString )
{
    auto assign = "hello"_c == "hi"_l;
    ASSERT_EQ( "`hello` = 'hi'", assign() );
}

TEST( SQLClause, AssignementSugarWithBool )
{
    auto assign = "hello"_c == SQL::Literal(true);
    ASSERT_EQ( "`hello` = true", assign() );
}


TEST( SQLClause, AssignementSugarWithInt )
{
    auto assign = "hello"_c == 1_l;
    ASSERT_EQ( "`hello` = 1", assign() );
}
TEST( SQLClause, JoinedTableDefault )
{
    SQL::JoinedTable joinedTable("table"_t);
    ASSERT_EQ( "`table`", joinedTable.table() );
    ASSERT_EQ( SQL::JoinedTable::LEFT, joinedTable.joinType() );
    ASSERT_EQ( "LEFT JOIN `table`", joinedTable() );
}

TEST( SQLClause, JoinedTableSugar )
{
    SQL::JoinedTable joinedTable = "table"_t | "t" | SQL::JoinedTable::RIGHT;
    ASSERT_EQ( "`table`", joinedTable.table() );
    ASSERT_EQ( SQL::JoinedTable::RIGHT, joinedTable.joinType() );
    ASSERT_EQ( "RIGHT JOIN `table` AS `t`", joinedTable() );
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

}
