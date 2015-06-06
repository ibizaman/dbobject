add_library(typeconverter
    TypeConverter.cpp
    Datetime.cpp
)

find_package(Boost REQUIRED COMPONENTS date_time)
include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(typeconverter
    ${Boost_LIBRARIES}
)

add_executable(typeconverter_test
    test/TypeConverterTest.cpp
)

target_link_libraries(typeconverter_test typeconverter gtest_main)

add_test(typeconverter_test typeconverter_test)

