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

target_link_libraries(dbobject utils)
