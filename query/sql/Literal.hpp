namespace dbobject {
namespace SQL {

template<typename T>
Literal::Literal(T value)
    : SimpleExpr(TypeConverter::toString(value))
{
}

template<typename T>
ValueLiteral<T>::ValueLiteral(const T& value)
    : Literal(value),
      _typedValue(value)
{
}

template<typename T>
void ValueLiteral<T>::setValue(const T& value)
{
    _typedValue = value;
    _value = TypeConverter::toString(value);
}

template<typename T>
T ValueLiteral<T>::value() const
{
    return _typedValue;
}

}
}
