#ifndef DBOBJECT_DELAYED_H
#define DBOBJECT_DELAYED_H

#include <memory>
#include <stdexcept>
#include <type_traits>

namespace dbobject {

class non_initialized_optional : public std::logic_error
{
public:
    using std::logic_error::logic_error;
};

template<typename T>
class Delayed
{
public:
    Delayed();
    Delayed(const T& value);
    Delayed(const Delayed<T>&);
    bool empty() const;
    bool initialized() const;
    void set(const T& value);
    void operator=(const T& value);
    T get() const;
    template<typename U = T> typename std::enable_if<std::is_default_constructible<U>::value, T&>::type get();
    template<typename U = T> typename std::enable_if<!std::is_default_constructible<U>::value, T&>::type get();
private:
    std::unique_ptr<T> _value;
};

}

#include "Delayed.hpp"

#endif
