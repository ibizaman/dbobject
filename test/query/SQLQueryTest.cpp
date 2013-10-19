#include <gtest/gtest.h>
#include "query/Query.h"
#include "query/Select.h"
#include "query/Insert.h"
#include "query/Update.h"

#include <stdexcept>
#include <string>

namespace dbobject {

using namespace SQL::Operators;

TEST( SQLSelectTest, defaults )
{
    SQL::Select query;
    ASSERT_THROW( query.getSQL(), SQL::malformed_sql );
}

TEST( SQLSelectTest, from )
{
    auto query = SQL::Query::select().from("table");
    std::string sql = "SELECT * FROM `table`";

    ASSERT_EQ( sql, query.getSQL() );
}

TEST( SQLSelectTest, select )
{
    SQL::Select query;

    query.select({"colA"});
    ASSERT_THROW( query.getSQL(), SQL::malformed_sql );
}

TEST( SQLSelectTest, selectFrom )
{
    SQL::Select query;

    query.from("table").select({"colA","colB"});
    std::string sql = "SELECT `colA`, `colB` FROM `table`";

    ASSERT_EQ( sql, query.getSQL() );
}

TEST( SQLSelectTest, where )
{
    SQL::Select query;

    query.where("colA"_c == "valA"_l);
    ASSERT_THROW( query.getSQL(), SQL::malformed_sql );
}

TEST( SQLSelectTest, fromWhereEmpty )
{
    SQL::Select query;

    query.from("table").where(SQL::Expression());
    std::string sql = "SELECT * FROM `table`";

    ASSERT_EQ( sql, query.getSQL() );
}

TEST( SQLSelectTest, fromWhere )
{
    SQL::Select query;

    query.from("table").where(("colA"_c == "A"_l && "colB"_c == "B"_l) || "colC"_c == "C"_l);
    std::string sql = "SELECT * FROM `table` WHERE `colA` = 'A' AND `colB` = 'B' OR `colC` = 'C'";

    ASSERT_EQ( sql, query.getSQL() );
}

TEST( SQLSelectTest, orderby )
{
    SQL::Select query;

    query.orderBy({"colA"_c});
    ASSERT_THROW( query.getSQL(), SQL::malformed_sql );
}

TEST( SQLSelectTest, fromOrderby )
{
    SQL::Select query;

    query.from("table").orderBy({
            "colA"_c,
            "colB"_c | SQL::Direction::DESC,
            "colC"_c | SQL::Direction::ASC
        });
    std::string sql = "SELECT * FROM `table` ORDER BY `colA`, `colB` DESC, `colC`";

    ASSERT_EQ( sql, query.getSQL() );
}

TEST( SQLInsertTest, insert )
{
    SQL::Insert query;

    query.insert({"a"_c == "vala"_l, "b"_c == "valb"_l});
    ASSERT_THROW( query.getSQL(), SQL::malformed_sql );
}

TEST( SQLInsertTest, into )
{
    SQL::Insert query;

    query.into("a");
    ASSERT_THROW( query.getSQL(), SQL::malformed_sql );
}

TEST( SQLInsertTest, insertOnlyColumnNames )
{
    SQL::Insert query;

    query.columnNames({"a"_c, "b"_c}).into("a");
    ASSERT_THROW( query.getSQL(), SQL::malformed_sql );
}

TEST( SQLInsertTest, insertIntoOnlyValues )
{
    SQL::Insert query;

    query.addValues({"vala"_l, "valb"_l}).into("a");
    std::string sql = "INSERT INTO `a` VALUES ('vala', 'valb')";

    ASSERT_EQ( sql, query.getSQL() );
}

TEST( SQLInsertTest, insertIntoMultipleValues )
{
    SQL::Insert query;

    query.addValues({"vala"_l, "valb"_l}).into("a").addValues({"valc"_l, "vald"_l});
    std::string sql = "INSERT INTO `a` VALUES ('vala', 'valb'), ('valc', 'vald')";

    ASSERT_EQ( sql, query.getSQL() );
}

TEST( SQLInsertTest, insertInto )
{
    SQL::Insert query;

    query.insert({"a"_c == "vala"_l, "b"_c == "valb"_l}).into("a");
    std::string sql = "INSERT INTO `a` SET `a` = 'vala', `b` = 'valb'";

    ASSERT_EQ( sql, query.getSQL() );
}

TEST( SQLInsertTest, insertIntoColumnNamesAndValues )
{
    SQL::Insert query;

    query.columnNames({"a"_c, "b"_c}).addValues({"vala"_l, "valb"_l}).into("a");
    std::string sql = "INSERT INTO `a` SET `a` = 'vala', `b` = 'valb'";

    ASSERT_EQ( sql, query.getSQL() );
}

TEST( SQLInsertTest, insertIntoColumnNamesWithMultipleValues )
{
    SQL::Insert query;

    query.columnNames({"a"_c, "b"_c}).addValues({"vala"_l, "valb"_l}).addValues({"valc"_l, "vald"_l}).into("a");
    std::string sql = "INSERT INTO `a`(`a`, `b`) VALUES ('vala', 'valb'), ('valc', 'vald')";

    ASSERT_EQ( sql, query.getSQL() );
}

TEST( SQLInsertTest, insertIntoOrUpdate )
{
    SQL::Insert query;

    query.insert({"a"_c == "vala"_l, "b"_c == "valb"_l}).into("a").orUpdate();
    std::string sql = "INSERT INTO `a` SET `a` = 'vala', `b` = 'valb' ON DUPLICATE KEY UPDATE `a` = VALUES(`a`), `b` = VALUES(`b`)";

    ASSERT_EQ( sql, query.getSQL() );
}

TEST( SQLInsertTest, insertIntoOnlyValuesOrUpdate)
{
    SQL::Insert query;

    query.columnNames({"a"_c, "b"_c}).into("a").orUpdate();

    ASSERT_THROW( query.getSQL(), SQL::malformed_sql );
}

TEST( SQLInsertTest, insertIntoOrUpdateSeparated )
{
    SQL::Insert query;

    query.columnNames({"a"_c, "b"_c}).addValues({"vala"_l, "valb"_l}).into("a").orUpdate();
    std::string sql = "INSERT INTO `a` SET `a` = 'vala', `b` = 'valb' ON DUPLICATE KEY UPDATE `a` = VALUES(`a`), `b` = VALUES(`b`)";

    ASSERT_EQ( sql, query.getSQL() );
}

TEST( SQLInsertTest, insertIntoOrUpdateOther )
{
    SQL::Insert query;

    query.insert({"a"_c == "vala"_l, "b"_c == "valb"_l}).into("a").orUpdate({"c"_c == "b"_c});
    std::string sql = "INSERT INTO `a` SET `a` = 'vala', `b` = 'valb' ON DUPLICATE KEY UPDATE `c` = `b`";

    ASSERT_EQ( sql, query.getSQL() );
}

TEST( SQLInsertTest, insertIntoMultipleValuesOrUpdate )
{
    SQL::Insert query;

    query.addValues({"vala"_l, "valb"_l}).addValues({"vala"_l, "valb"_l}).into("a").orUpdate();

    ASSERT_THROW( query.getSQL(), SQL::malformed_sql );
}

TEST( SQLInsertTest, insertIntoColumnNamesAndMultipleValuesOrUpdate )
{
    SQL::Insert query;

    query.columnNames({"a"_c, "b"_c}).addValues({"vala"_l, "valb"_l}).addValues({"valc"_l, "vald"_l}).into("a").orUpdate();
    std::string sql = "INSERT INTO `a`(`a`, `b`) VALUES ('vala', 'valb'), ('valc', 'vald') ON DUPLICATE KEY UPDATE `a` = VALUES(`a`), `b` = VALUES(`b`)";

    ASSERT_EQ( sql, query.getSQL() );
}

TEST( SQLUpdateTest, update )
{
    SQL::Update query;

    query.update("update");

    ASSERT_THROW( query.getSQL(), SQL::malformed_sql );
}

TEST( SQLUpdateTest, set )
{
    SQL::Update query;

    query.set({"a"_c == "vala"_l});

    ASSERT_THROW( query.getSQL(), SQL::malformed_sql );
}

TEST( SQLUpdateTest, updateSet )
{
    SQL::Update query;

    query.update("update").set({"a"_c == "vala"_l});
    std::string sql = "UPDATE `update` SET `a` = 'vala'";

    ASSERT_EQ( sql, query.getSQL() );
}

TEST( SQLUpdateTest, where )
{
    SQL::Update query;

    query.select({"colA"});
    ASSERT_THROW( query.getSQL(), SQL::malformed_sql );
}

TEST( SQLUpdateTest, orderBy )
{
    SQL::Update query;

    query.orderBy({"colA"_c});
    ASSERT_THROW( query.getSQL(), SQL::malformed_sql );
}

}
