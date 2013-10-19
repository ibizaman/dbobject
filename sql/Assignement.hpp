namespace dbobject {
namespace SQL {

namespace AssignementImpl {

template<typename Base, typename Type>
auto print(const Type& value) -> typename std::enable_if<std::is_base_of<PolymorphicType<Base>, Type>::value, std::string>::type
{
    return (*value)();
}

template<typename Base, typename Type>
auto print(const Type& value) -> typename std::enable_if<std::is_base_of<Base, Type>::value, std::string>::type
{
    return value();
}

template<typename Base, typename Type>
auto print(const Type& value) -> typename std::enable_if<!std::is_base_of<PolymorphicType<Base>, Type>::value && !std::is_base_of<Base, Type>::value, std::string>::type
{
    return Base(value)();
}

}

template<typename Left, typename Right>
template<typename L, typename R>
Assignement<Left, Right>::Assignement(const L& left, const R& right)
    : Expression(AssignementImpl::print<Left>(left) + " = " + AssignementImpl::print<Right>(right)),
      _left(left),
      _right(right)
{
}

template<typename Left, typename Right>
template<typename L, typename R>
Assignement<Left, Right>::Assignement(const Assignement<L,R>& other)
    : Expression(other()),
      _left(other.left()),
      _right(other.right())
{
}

template<typename Left, typename Right>
PolymorphicType<Left> Assignement<Left, Right>::left() const
{
    return _left;
}

template<typename Left, typename Right>
PolymorphicType<Right> Assignement<Left, Right>::right() const
{
    return _right;
}

}
}
