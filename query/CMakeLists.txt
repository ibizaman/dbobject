add_subdirectory(sql)

add_library(query
    Query.cpp
    Insert.cpp
    Select.cpp
    Update.cpp
)

target_link_libraries(query
    sql
    typeconverter
)

add_executable(query_test
    test/SQLQueryTest.cpp
)

target_link_libraries(query_test query gtest_main)

add_test(query_test query_test)

