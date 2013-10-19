#include <sstream>

namespace dbobject {
namespace SQL {

template<typename T>
std::string List<T>::operator()() const
{
    std::stringstream s;

    if (V::cbegin() != V::cend()) {
        s << **V::cbegin();

        for (auto i = V::cbegin()+1; i != V::cend(); ++i) {
            s << ", " << **i;
        }
    }

    return s.str();
}

}
}
