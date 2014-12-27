include_directories(../..) #/lib

add_library(dbobject
    functional/VectorHelper.cpp

    polymorph/ResultSetHelper.cpp

    query/Query.cpp
    query/Insert.cpp
    query/Select.cpp
    query/Update.cpp

    sql/Assignement.cpp
    sql/Clause.cpp
    sql/ColumnName.cpp
    sql/Expression.cpp
    sql/Function.cpp
    sql/Join.cpp
    sql/JoinedTable.cpp
    sql/Literal.cpp
    sql/SchemaName.cpp
    sql/SimpleExpr.cpp
    sql/Sort.cpp
    sql/TableName.cpp

    MySQLBackend.cpp
    Object.cpp
    Tuple.cpp
)

target_link_libraries(dbobject utils typeconverter)


enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
find_package(GMock REQUIRED)
include_directories(${GMOCK_INCLUDE_DIRS})

set(TEST_SOURCE_FILES
    test/dummy/DummyObject.cpp
    test/functional/MapHelperTest.cpp
    test/functional/VectorHelperTest.cpp
    test/polymorph/DelayedTest.cpp
    test/polymorph/PolymorphicTypeTest.cpp
    test/query/SQLQueryTest.cpp
    test/sql/SQLClauseTest.cpp
    test/MySQLBackendTest.cpp
    test/TupleTest.cpp
    test/ObjectTest.cpp
)

find_package(MYSQLCONNECTORCPP REQUIRED)
include_directories(${MYSQLCONNECTORCPP_INCLUDE_DIRS})

find_package(Boost REQUIRED COMPONENTS date_time)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(dbobjectTest ${TEST_SOURCE_FILES})
target_link_libraries(dbobjectTest 
    dbobject
    ${MYSQLCONNECTORCPP_LIBRARIES}
    ${GTEST_BOTH_LIBRARIES}
    ${Boost_LIBRARIES}
    ${GMOCK_LIBRARIES}
    -lpthread
)
gtest_add_tests(dbobjectTest "" ${TEST_SOURCE_FILES})

