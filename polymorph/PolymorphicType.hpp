namespace dbobject {

template<typename Base>
template<typename Derived>
PolymorphicType<Base>::PolymorphicType(const Derived& item, typename std::enable_if<std::is_base_of<Base, Derived>::value>::type*)
    : _object(new Derived(item))
{
}

template<typename Base>
template<typename Derived>
PolymorphicType<Base>::PolymorphicType(const PolymorphicType<Derived>& item, typename std::enable_if<std::is_base_of<Base, Derived>::value>::type*)
    : _object(item._object)
{
}

template<typename Base>
template<typename Implicit>
PolymorphicType<Base>::PolymorphicType(const Implicit& item, typename std::enable_if<!std::is_base_of<Base, Implicit>::value>::type*)
    : _object(new Base(item))
{
}

template<typename Base>
template<typename Implicit>
PolymorphicType<Base>::PolymorphicType(const PolymorphicType<Implicit>& item, typename std::enable_if<!std::is_base_of<Base, Implicit>::value>::type*)
    : _object(new Base(*item._object))
{
}

template<typename Base>
Base& PolymorphicType<Base>::operator*()
{
    return *_object.get();
}

template<typename Base>
const Base& PolymorphicType<Base>::operator*() const
{
    return *_object.get();
}

template<typename Base>
Base* PolymorphicType<Base>::operator->()
{
    return _object.get();
}

template<typename Base>
const Base* PolymorphicType<Base>::operator->() const
{
    return _object.get();
}

}
