#include <gtest/gtest.h>
#include "polymorph/PolymorphicType.hxx"

#include <string>

namespace dbobject {

class Implicit
{
public:
    Implicit(const std::string& name) : _name(name) {}
    virtual std::string name() const {return _name;}
    virtual std::string operator()() const {return "implicit "+name();}
protected:
    std::string _name;
};

class Base
{
public:
    Base(const std::string& name) : _name(name) {}
    Base(const Implicit& i) : _name(i.name()) {}
    virtual std::string name() const {return _name;}
    virtual std::string operator()() const {return _name;}
private:
    std::string _name;
};

class Derived : public Base
{
public:
    using Base::Base;
    virtual std::string operator()() const {return "derived "+name();}
};

TEST( PolymorphicTypeTest, Construction )
{
    PolymorphicType<Base> p(Base("hello"));
    ASSERT_EQ( "hello", (*p).name() );
    ASSERT_EQ( "hello", p->name() );
    ASSERT_EQ( "hello", (*p)() );

    PolymorphicType<Derived> p2(Derived("hello"));
    ASSERT_EQ( "hello", (*p2).name() );
    ASSERT_EQ( "hello", p2->name() );
    ASSERT_EQ( "derived hello", (*p2)() );
}

TEST( PolymorphicTypeTest, DerivedCopy )
{
    Derived d("hello");
    PolymorphicType<Base> p(d);
    ASSERT_EQ( "derived hello", (*p)() );
}

TEST( PolymorphicTypeTest, PolymorphicDerivedCopy )
{
    PolymorphicType<Derived> d("hello");
    PolymorphicType<Base> p(d);
    ASSERT_EQ( "derived hello", (*p)() );
}

TEST( PolymorphicTypeTest, ImplicitCopy )
{
    Implicit i("hello");
    PolymorphicType<Base> p(i);
    ASSERT_EQ( "hello", (*p)() );
}

TEST( PolymorphicTypeTest, PolymorphicImplicitCopy )
{
    PolymorphicType<Implicit> i("hello");
    PolymorphicType<Base> p(i);
    ASSERT_EQ( "hello", (*p)() );
}

}
