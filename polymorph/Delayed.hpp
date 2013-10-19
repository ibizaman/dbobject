namespace dbobject {

template<typename T>
Delayed<T>::Delayed()
{
}

template<typename T>
Delayed<T>::Delayed(const T& value)
{
    set(value);
}

template<typename T>
Delayed<T>::Delayed(const Delayed<T>& other)
{
    if (other.initialized()) {
        set(other.get());
    }
}

template<typename T>
bool Delayed<T>::empty() const
{
    return !initialized();
}

template<typename T>
bool Delayed<T>::initialized() const
{
    return static_cast<bool>(_value);
}

template<typename T>
void Delayed<T>::set(const T& value)
{
    _value.reset(new T(value));
}

template<typename T>
void Delayed<T>::operator=(const T& value)
{
    set(value);
}

template<typename T>
T Delayed<T>::get() const
{
    if (empty()) {
        throw non_initialized_optional("Cannot get value if not initialized");
    }
    return *_value;
}

template<typename T>
template<typename U>
typename std::enable_if<std::is_default_constructible<U>::value, T&>::type Delayed<T>::get()
{
    if (empty()) {
        set(U());
    }
    return *_value;
}

template<typename T>
template<typename U>
typename std::enable_if<!std::is_default_constructible<U>::value, T&>::type Delayed<T>::get()
{
    if (empty()) {
        throw non_initialized_optional("Cannot get value if not initialized");
    }
    return *_value;
}

}
