add_library(polymorph
    ResultSetHelper.cpp
)

add_executable(polymorph_test
    test/DelayedTest.cpp
    test/PolymorphicTypeTest.cpp
)

target_link_libraries(polymorph_test polymorph gtest_main)

add_test(polymorph_test polymorph_test)

