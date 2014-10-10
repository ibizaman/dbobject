namespace dbobject {
namespace SQL {

template<typename T>
Literal::Literal(T value)
    : SimpleExpr('\''+TypeConverter::toString(value)+'\'')
{
}

}
}
