#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <initializer_list>


template<typename L, typename R, typename Fun>
void expect_equals(Fun fun, std::initializer_list<std::pair<L,R>> list)
{
    int i = 0;
    std::for_each(begin(list), end(list), [fun, &i](const std::pair<L,R>& pair){
            std::ostringstream s;
            s << "iteration " << i;
            SCOPED_TRACE( s.str() );
            EXPECT_EQ( pair.second, fun(pair.first) );
            ++i;
        });
}


template<typename T, typename Exc, typename Fun>
void expect_thrown(Fun fun, std::initializer_list<T> list)
{
    int i = 0;
    std::for_each(begin(list), end(list), [fun, &i](const T& value){
            std::ostringstream s;
            s << "iteration " << i;
            SCOPED_TRACE( s.str() );
            EXPECT_THROW( fun(value), Exc );
            ++i;
        });
}

#endif
