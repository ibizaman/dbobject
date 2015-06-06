# - Try to find Mysql-Connector-C++
# Once done, this will define
#
#  MYSQLCONNECTORCPP_FOUND - system has Mysql-Connector-C++ installed
#  MYSQLCONNECTORCPP_INCLUDE_DIRS - the Mysql-Connector-C++ include directories
#  MYSQLCONNECTORCPP_LIBRARIES - link these to use Mysql-Connector-C++
#
# The user may wish to set, in the CMake GUI or otherwise, this variable:
#  MYSQLCONNECTORCPP_ROOT_DIR - path to start searching for the module

set(MYSQLCONNECTORCPP_ROOT_DIR
        "${MYSQLCONNECTORCPP_ROOT_DIR}"
        CACHE
        PATH
        "Where to start looking for this component.")

if(WIN32)
    find_path(MYSQLCONNECTORCPP_INCLUDE_DIR
            NAMES
            mysql_connection.h
            PATHS
            "C:\\Program Files"
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            include)

    find_library(MYSQLCONNECTORCPP_LIBRARY
            NAMES
            mysqlcppconn
            mysqlcppconn-static
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            lib)

else()
    find_path(MYSQLCONNECTORCPP_INCLUDE_DIR
            mysql_connection.h
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            include)

    find_library(MYSQLCONNECTORCPP_LIBRARY
            NAMES
            mysqlcppconn
            mysqlcppconn-static
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            lib64
            lib)
endif()

include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(MysqlConnectorCpp
            DEFAULT_MSG
            MYSQLCONNECTORCPP_INCLUDE_DIR
            MYSQLCONNECTORCPP_LIBRARY)

if(MYSQLCONNECTORCPP_FOUND)
    set(MYSQLCONNECTORCPP_INCLUDE_DIRS
            "${MYSQLCONNECTORCPP_INCLUDE_DIR}")
    set(MYSQLCONNECTORCPP_LIBRARIES
            "${MYSQLCONNECTORCPP_LIBRARY}")
    mark_as_advanced(MYSQLCONNECTORCPP_ROOT_DIR)
endif() 

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MysqlConnectorCpp
    FOUND_VAR MysqlConnectorCpp_FOUND
    REQUIRED_VARS
    MysqlConnectorCpp_LIBRARY
    MysqlConnectorCpp_INCLUDE_DIR
    VERSION_VAR MysqlConnectorCpp_VERSION
    )

if(MysqlConnectorCpp_FOUND)
    set(MysqlConnectorCpp_LIBRARIES ${MysqlConnectorCpp_LIBRARY})
    set(MysqlConnectorCpp_INCLUDE_DIRS ${MysqlConnectorCpp_INCLUDE_DIR})
    set(MysqlConnectorCpp_DEFINITIONS ${PC_MysqlConnectorCpp_CFLAGS_OTHER})
endif()

mark_as_advanced(MysqlConnectorCpp_INCLUDE_DIR MysqlConnectorCpp_LIBRARY MYSQLCONNECTORCPP_ROOT_DIR)
