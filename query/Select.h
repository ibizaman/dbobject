#ifndef DBOBJECT_SQL_SELECT_H
#define DBOBJECT_SQL_SELECT_H

#include "Query.h"
#include "polymorph/PolymorphicType.hxx"
#include "polymorph/Delayed.hxx"

namespace dbobject {
namespace SQL {

class Select : public Query
{
public:
    typedef ColumnName GroupBy;
    typedef Sort<ColumnName> OrderBy;

    Select& select();
    Select& select(const List<ColumnName>&);
    Select& from(const PolymorphicType<TableName>&);
    Select& join(const List<Join>&);
    Select& distinct(bool = true);
    Select& where(const PolymorphicType<Expression>&);
    Select& groupBy(const List<GroupBy>&);
    Select& having(const PolymorphicType<Expression>&);
    Select& orderBy(const List<OrderBy>&);
    Select& limit(int);

    virtual std::string getSQL() const override;

private:
    Delayed<List<ColumnName>> _columns;
    Delayed<PolymorphicType<TableName>> _from;
    List<Join> _joins;
    Delayed<bool> _distinct;
    Delayed<PolymorphicType<Expression>> _where;
    List<GroupBy> _groupBy;
    Delayed<PolymorphicType<Expression>> _having;
    List<OrderBy> _orderBy;
    Delayed<IntLiteral> _limit;
};

}
}

#endif
