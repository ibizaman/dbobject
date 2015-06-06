cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(dbobject)


if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# export for vim's youcompleteme plugin
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)


set(CMAKE_CXX_FLAGS "-std=c++11")
add_subdirectory(test/gmock-1.7.0)

include_directories(SYSTEM ${gtest_SOURCE_DIR}/include)
include_directories(SYSTEM ${gmock_SOURCE_DIR}/include)


enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wmissing-include-dirs -Wextra -Wcast-qual -Wwrite-strings -Wconversion -pedantic -Winit-self -Wunused -Wfloat-equal -Wcast-align")

include_directories(.)
add_subdirectory(backends)
add_subdirectory(file)
add_subdirectory(functional)
add_subdirectory(polymorph)
add_subdirectory(query)
add_subdirectory(typeconverter)

add_library(dbobject
    Object.cpp
    Tuple.cpp
)

target_link_libraries(dbobject
    backend_mysql
    file
    functional
    polymorph
    query
    typeconverter
)


add_executable(dbobject_test
    test/dummy/DummyObject.cpp
    test/TupleTest.cpp
    test/ObjectTest.cpp

    test/MySQLBackendIntegrationTest.cpp
    test/TupleIntegrationTest.cpp
    test/ObjectIntegrationTest.cpp
)

add_test(dbobject_test dbobject_test)

target_link_libraries(dbobject_test dbobject gmock gtest_main)


# copy parameters for tests in build directory
add_custom_command(TARGET dbobject_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/test/parameters.conf $<TARGET_FILE_DIR:dbobject_test>/test/parameters.conf)

