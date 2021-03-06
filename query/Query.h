#ifndef DBOBJECT_SQL_QUERY_H
#define DBOBJECT_SQL_QUERY_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "sql/All.h"

namespace dbobject {
namespace SQL {

class malformed_sql : public std::logic_error
{
public:
    using std::logic_error::logic_error;
};

class Select;
class Insert;
class Update;

class Query
{
public:
    typedef Assignement<ColumnName,SimpleExpr> ColumnAssignement;

    static Select select();
    static Select select(const List<SimpleExpr>&);
    static Insert insert();
    static Insert insert(const List<ColumnAssignement>&);
    static Update update(const PolymorphicType<TableName>&);
    virtual std::string getSQL() const = 0;
    bool operator==(const Query&) const;
};

::std::ostream& operator<<(::std::ostream&, const Query&);
::std::ostream& operator<<(::std::ostream&, const Select&);
::std::ostream& operator<<(::std::ostream&, const Insert&);
::std::ostream& operator<<(::std::ostream&, const Update&);

}
}

#endif
