add_library(backend_mysql
    MySQLBackend.cpp
)

find_package(MYSQLCONNECTORCPP REQUIRED)
include_directories(${MYSQLCONNECTORCPP_INCLUDE_DIRS})

target_link_libraries(backend_mysql
    query
    ${MYSQLCONNECTORCPP_LIBRARIES}
)


add_executable(backend_mysql_test
    test/MySQLBackendTest.cpp
)

target_link_libraries(backend_mysql_test backend_mysql gtest_main)

add_test(backend_mysql_test backend_mysql_test)

