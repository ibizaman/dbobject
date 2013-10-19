#ifndef DBOBJECT_SQL_ALIAS_H
#define DBOBJECT_SQL_ALIAS_H

#include "polymorph/PolymorphicType.hxx"

namespace dbobject {
namespace SQL {

template<typename Base>
class Alias : public Base
{
public:
    template<typename Actual>
    Alias(const Actual&, const std::string&);
    template<typename Other>
    Alias(const Alias<Other>&);
    virtual std::string operator()() const override;
    template<typename> friend class Alias;
private:
    PolymorphicType<Base> _value;
    std::string _alias;
};

namespace Operators {
template<typename Actual>
Alias<Actual> operator|(const Actual&, const std::string&);
}

}
}

#include "Alias.hpp"

#endif
