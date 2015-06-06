namespace dbobject {
namespace SQL {

template<typename Base>
template<typename Actual>
Alias<Base>::Alias(const Actual& name, const std::string& alias)
    : Base(name),
      _value(name),
      _alias(alias)
{
}

template<typename Base>
template<typename Other>
Alias<Base>::Alias(const Alias<Other>& other)
    : Base(*other._value),
      _value(other._value),
      _alias(other._alias)
{
}

template<typename Base>
std::string Alias<Base>::operator()() const
{
    return (*_value)() + " AS `" + _alias + '`';
}

namespace Operators {

template<typename Actual>
Alias<Actual> operator|(const Actual& value, const std::string& alias)
{
    return Alias<Actual>(value, alias);
}

}

}
}
