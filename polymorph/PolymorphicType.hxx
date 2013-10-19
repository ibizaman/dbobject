#ifndef DBOBJECT_POLYMORPHICTYPE_H
#define DBOBJECT_POLYMORPHICTYPE_H

#include <memory>

namespace dbobject {

template<typename Base>
class PolymorphicType
{
public:
    template<typename Derived>
    PolymorphicType(const Derived&, typename std::enable_if<std::is_base_of<Base, Derived>::value>::type* = 0);
    template<typename Derived>
    PolymorphicType(const PolymorphicType<Derived>&, typename std::enable_if<std::is_base_of<Base, Derived>::value>::type* = 0);

    template<typename Implicit>
    PolymorphicType(const Implicit&, typename std::enable_if<!std::is_base_of<Base, Implicit>::value>::type* = 0);
    template<typename Implicit>
    PolymorphicType(const PolymorphicType<Implicit>&, typename std::enable_if<!std::is_base_of<Base, Implicit>::value>::type* = 0);

    Base& operator*();
    const Base& operator*() const;
    Base* operator->();
    const Base* operator->() const;

private:
    template<typename Other>
    friend class PolymorphicType;

    std::shared_ptr<Base> _object;
};

}

#include "PolymorphicType.hpp"

#endif
