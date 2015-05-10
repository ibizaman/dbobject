#include <sstream>
#include <algorithm>

namespace dbobject {
namespace SQL {

template<typename From, typename To>
To toPolymorphicType(const From& from)
{
    return PolymorphicType<To>(from);
}

template<typename T>
List<T>::List() {
}

template<typename T>
List<T>::List(std::initializer_list<PolymorphicType<T>> other)
{
    for (auto o : other) {
        _list.push_back(o);
    }
}

template<typename T>
template<typename U>
List<T>::List(const std::vector<U>& other)
{
    for (auto o : other) {
        _list.push_back(o);
    }
}

template<typename T>
template<typename U>
List<T>::List(const List<U>& other)
{
    for (auto o : other) {
        _list.push_back(o);
    }
}


template<typename T>
std::string List<T>::operator()() const
{
    std::stringstream s;

    if (_list.cbegin() != _list.cend()) {
        s << **_list.cbegin();

        for (auto i = _list.cbegin()+1; i != _list.cend(); ++i) {
            s << ", " << **i;
        }
    }

    return s.str();
}

template<typename T>
void List<T>::insert(const_iterator position, const T& value)
{
    _list.insert(position, value);
}

template<typename T>
template<typename U>
void List<T>::push_back(const U& value)
{
    _list.push_back(value);
}

template<typename T>
void List<T>::clear()
{
    return _list.clear();
}

template<typename T>
bool List<T>::empty() const
{
    return _list.empty();
}

template<typename T>
typename List<T>::iterator List<T>::begin()
{
    return _list.begin();
}

template<typename T>
typename List<T>::const_iterator List<T>::begin() const
{
    return _list.begin();
}

template<typename T>
typename List<T>::iterator List<T>::end()
{
    return _list.end();
}

template<typename T>
typename List<T>::const_iterator List<T>::end() const
{
    return _list.end();
}

}
}
