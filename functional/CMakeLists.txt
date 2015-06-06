add_library(functional
    VectorHelper.cpp
)

add_executable(functional_test
    test/MapHelperTest.cpp
    test/VectorHelperTest.cpp
)

target_link_libraries(functional_test functional gtest_main)

add_test(functional_test functional_test)

