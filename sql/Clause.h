#ifndef DBOBJECT_SQL_CLAUSE_H
#define DBOBJECT_SQL_CLAUSE_H

#include <string>
#include <ostream>

namespace dbobject {
namespace SQL {

class Clause
{
public:
    virtual std::string operator()() const = 0;
    friend std::ostream& operator<<(std::ostream&, const Clause&);
};
std::ostream& operator<<(std::ostream&, const Clause&);

}
}

#endif
