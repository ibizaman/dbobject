namespace dbobject {
namespace SQL {

namespace Operators {

template<typename T>
Sort<T> operator|(const T& sorted, const Direction& direction)
{
    return Sort<T>(sorted, direction);
}

}

}
}
