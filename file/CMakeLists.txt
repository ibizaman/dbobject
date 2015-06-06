add_library(file
    CSVParser.cpp
    FileIO.cpp
    SQLConfFile.cpp
)

find_package(Boost REQUIRED COMPONENTS date_time system filesystem thread)
include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(file ${Boost_LIBRARIES})


add_executable(file_test
    test/CSVParserTest.cpp
    test/FileIOTest.cpp
    test/SQLConfFileTest.cpp
)

target_link_libraries(file_test file gtest_main)

add_test(file_test file_test)

