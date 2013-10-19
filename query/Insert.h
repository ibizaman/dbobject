#ifndef DBOBJECT_SQL_INSERT_H
#define DBOBJECT_SQL_INSERT_H

#include "Query.h"
#include "polymorph/PolymorphicType.hxx"
#include "polymorph/Delayed.hxx"

namespace dbobject {
namespace SQL {

class Insert : public Query
{
public:
    typedef Query::ColumnAssignement ColumnAssignement;

    Insert& insert(const List<ColumnAssignement>&);
    Insert& columnNames(const List<ColumnName>&);
    Insert& addValues(const List<Literal>&);
    Insert& into(const PolymorphicType<TableName>&);
    Insert& orUpdate();
    Insert& orUpdate(const List<ColumnAssignement>&);

    virtual std::string getSQL() const override;

private:
    Delayed<List<ColumnName>> _columns;
    std::vector<List<Literal>> _values;
    Delayed<PolymorphicType<TableName>> _into;
    Delayed<List<ColumnAssignement>> _onDuplicate;

    std::string zipColumnNameLiteral(const List<ColumnName>&, const List<Literal>&) const;
};

}
}

#endif
