#include <gtest/gtest.h>
#include <stdexcept>
#include "polymorph/Delayed.hxx"

namespace dbobject {

class NotDefaultConstructible
{
public:
    NotDefaultConstructible() = delete;
};

TEST( DelayedTest, EmptyContructionForDefaultConstructible )
{
    Delayed<int> o;
    ASSERT_TRUE( o.empty() );
    ASSERT_FALSE( o.initialized() );
}

TEST( DelayedTest, EmptyContructionForNotDefaultConstructible )
{
    Delayed<NotDefaultConstructible> o;
    ASSERT_TRUE( o.empty() );
    ASSERT_FALSE( o.initialized() );
    ASSERT_THROW( o.get(), non_initialized_optional );
}

TEST( DelayedTest, PostInitialisation )
{
    Delayed<int> o;
    o.set(3);
    ASSERT_EQ( 3, o.get() );
    o = 4;
    ASSERT_EQ( 4, o.get() );
}

TEST( DelayedTest, PostAssignementForDefaultConstructible )
{
    Delayed<int> o;
    ASSERT_EQ( int(), o.get() );
    ASSERT_TRUE( o.initialized() );
}

TEST( DelayedTest, RValueContruction )
{
    Delayed<int> o(3);
    ASSERT_TRUE( o.initialized() );
    ASSERT_EQ( 3, o.get() );
}

TEST( DelayedTest, LValueContruction )
{
    int i = 3;
    Delayed<int> o(i);
    ASSERT_TRUE( o.initialized() );
    ASSERT_EQ( 3, o.get() );
}

TEST( DelayedTest, Copy )
{
    Delayed<int> o(3);
    Delayed<int> p(o);
    Delayed<int> q = o;
    ASSERT_EQ( o.get(), p.get() );
    ASSERT_EQ( o.get(), q.get() );
}

TEST( DelayedTest, EmptyCopy )
{
    Delayed<int> o;
    ASSERT_FALSE( o.initialized() );
    Delayed<int> o2(o);
    ASSERT_FALSE( o2.initialized() );
}

TEST( DelayedTest, CopyAssignement )
{
    Delayed<int> o(3);
    Delayed<int> p(o);

    o.set(4);

    ASSERT_NE( o.get(), p.get() );
}

TEST( DelayedTest, SharedAssignement )
{
    Delayed<std::shared_ptr<int>> o(std::shared_ptr<int>(new int(3)));
    Delayed<std::shared_ptr<int>> p(o);

    *o.get() = 4;

    ASSERT_EQ( *o.get(), *p.get() );
}

}
