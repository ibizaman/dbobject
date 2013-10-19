#ifndef DBOBJECT_SQL_UPDATE_H
#define DBOBJECT_SQL_UPDATE_H

#include "Query.h"
#include "polymorph/PolymorphicType.hxx"

namespace dbobject {
namespace SQL {

class Update : public Query
{
public:
    typedef Query::ColumnAssignement ColumnAssignement;
    typedef Sort<ColumnName> OrderBy;

    Update& update(const PolymorphicType<TableName>&);
    Update& set(const List<ColumnAssignement>&);
    Update& where(const PolymorphicType<Expression>&);
    Update& orderBy(const List<OrderBy>&);
    Update& limit(int);

    virtual std::string getSQL() const override;

private:
    Delayed<PolymorphicType<TableName>> _update;
    Delayed<List<ColumnAssignement>> _set;
    Delayed<PolymorphicType<Expression>> _where;
    List<OrderBy> _orderBy;
    Delayed<IntLiteral> _limit;
};

}
}

#endif
