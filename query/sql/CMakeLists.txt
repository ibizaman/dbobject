add_library(sql
    Assignement.cpp
    Clause.cpp
    ColumnName.cpp
    Expression.cpp
    Function.cpp
    Join.cpp
    JoinedTable.cpp
    Literal.cpp
    SchemaName.cpp
    SimpleExpr.cpp
    Sort.cpp
    TableName.cpp
)

target_link_libraries(sql typeconverter)

add_executable(sql_test
    test/SQLClauseTest.cpp
)

target_link_libraries(sql_test sql gtest_main)

add_test(sql_test sql_test)

