#include "Query.h"
#include "Select.h"
#include "Insert.h"
#include "Update.h"

namespace dbobject {
namespace SQL {

Select Query::select()
{
    return Select();
}

Select Query::select(const List<ColumnName>& columns)
{
    Select s;
    s.select(columns);
    return s;
}

Insert Query::insert()
{
    return Insert();
}

Insert Query::insert(const List<ColumnAssignement>& list)
{
    Insert i;
    i.insert(list);
    return i;
}

Update Query::update(const PolymorphicType<TableName>& update)
{
    Update i;
    i.update(update);
    return i;
}

bool Query::operator==(const Query& other) const
{
    return getSQL() == other.getSQL();
}

std::ostream& operator<<(std::ostream& out, const Query& query)
{
    out << query.getSQL();
    return out;
}

std::ostream& operator<<(std::ostream& out, const Select& query)
{
    out << query.getSQL();
    return out;
}

std::ostream& operator<<(std::ostream& out, const Insert& query)
{
    out << query.getSQL();
    return out;
}

std::ostream& operator<<(std::ostream& out, const Update& query)
{
    out << query.getSQL();
    return out;
}

}
}
