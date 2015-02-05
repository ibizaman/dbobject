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


set(TEST_SOURCE_FILES ${TEST_SOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/test/dummy/DummyObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/functional/MapHelperTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/functional/VectorHelperTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/polymorph/DelayedTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/polymorph/PolymorphicTypeTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/query/SQLQueryTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/sql/SQLClauseTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/MySQLBackendTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/TupleTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/ObjectTest.cpp
    PARENT_SCOPE
)

find_package(MYSQLCONNECTORCPP REQUIRED)
include_directories(${MYSQLCONNECTORCPP_INCLUDE_DIRS})

find_package(Boost REQUIRED COMPONENTS date_time)
include_directories(${Boost_INCLUDE_DIRS})

set(TEST_LINK_LIBRARIES ${TEST_LINK_LIBRARIES}
    dbobject
    ${MYSQLCONNECTORCPP_LIBRARIES}
    ${Boost_LIBRARIES}
    PARENT_SCOPE
)

