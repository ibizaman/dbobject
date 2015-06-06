#include <sstream>
#include <typeinfo>

template<typename T>
T TypeConverter::fromString(const std::string& s)
{
    return TypeConverter::impl::TypeConverter<T>::fromString(s, Settings());
}

template<typename T>
T TypeConverter::fromString(const std::string& s, Settings settings)
{
    return TypeConverter::impl::TypeConverter<T>::fromString(s, settings);
}

template<typename T>
T TypeConverter::fromString(const std::string& s, char separator)
{
    return TypeConverter::impl::TypeConverter<T>::fromString(s, Settings(separator));
}

template<typename T>
std::string TypeConverter::toString(T value)
{
    return TypeConverter::impl::TypeConverter<T>::toString(value, Settings());
}

template<typename T>
std::string TypeConverter::toString(T value, Settings settings)
{
    return TypeConverter::impl::TypeConverter<T>::toString(value, settings);
}

template<typename T>
std::string TypeConverter::toString(T value, char separator)
{
    return TypeConverter::impl::TypeConverter<T>::toString(value, Settings(separator));
}

template<typename T>
T TypeConverter::impl::TypeConverter<T>::fromString(const std::string& s, const Settings&)
{
    std::istringstream serializer(s);
    T value;

    if (!(serializer >> value)) {
        throw ImpossibleConversion(typeid(T).name(), s, "impossible to convert using istringstream");
    }

    return value;
}

template<typename T>
std::string TypeConverter::impl::TypeConverter<T>::toString(T value, const Settings&)
{
    std::ostringstream serializer;

    serializer << value;

    return serializer.str();
}

template<typename T>
std::vector<T> TypeConverter::impl::TypeConverter<std::vector<T>>::fromString(std::string str, const Settings& settings)
{
    str = extractFromEnclosingChars(str, '[', ']', "vector");

    std::vector<T> vec;
    size_t split = 0;
    while (split != std::string::npos) {
        split = getNextSeparator(str, settings);
        auto word = str.substr(0, split);
        if (word.size() == 0) {
            throw ImpossibleConversion(typeid(T).name(), "string", "one of the words is empty");
        }
        vec.push_back(::TypeConverter::fromString<T>(word, settings));

        str = str.substr(split + 1);
    }
    return vec;
}

template<typename T>
std::string TypeConverter::impl::TypeConverter<std::vector<T>>::toString(const std::vector<T>& vec, const Settings& settings)
{
    if (vec.size() == 0) {
        return std::string(&settings.leftVector, 1) + settings.rightVector;
    }

    std::string str(&settings.leftVector, 1);
    str += ::TypeConverter::toString(vec.at(0), settings);
    for (size_t i = 1; i < vec.size(); ++i) {
        str += settings.separator + ::TypeConverter::toString(vec.at(i), settings);
    }
    str += settings.rightVector;
    return str;
}

template<typename... T>
std::tuple<T...> TypeConverter::impl::TypeConverter<std::tuple<T...>>::fromString(std::string str, const Settings& settings)
{
    str = extractFromEnclosingChars(str, settings.leftTuple, settings.rightTuple, "tuple");
    return fromStringTyped<T...>(str, settings);
}

template<typename T>
std::tuple<T> TypeConverter::impl::fromStringTyped(const std::string& str, const Settings& settings)
{
    auto split = getNextSeparator(str, settings);
    if (split != std::string::npos) {
        throw ImpossibleConversion("string", "tuple", "did not convert all values in string");
    }
    return std::make_tuple(::TypeConverter::fromString<T>(str, settings));
}

template<typename T, typename T2, typename... Rest>
std::tuple<T, T2, Rest...> TypeConverter::impl::fromStringTyped(const std::string& str, const Settings& settings)
{
    auto split = getNextSeparator(str, settings);
    auto word = str.substr(0, split);
    auto rest = str.substr(split + 1);
    return std::tuple_cat(
            std::make_tuple(::TypeConverter::fromString<T>(word, settings)),
            fromStringTyped<T2, Rest...>(rest, settings)
        );
}

template<typename... T>
std::string TypeConverter::impl::TypeConverter<std::tuple<T...>>::toString(const std::tuple<T...>& tup, const Settings& settings)
{
    return std::string(&settings.leftTuple, 1) + toStringTyped(tup, settings) + settings.rightTuple;
}

template<typename Tup, int I>
auto TypeConverter::impl::toStringTyped(const Tup& tup, const Settings& settings)
    -> typename std::enable_if<I == std::tuple_size<Tup>::value - 1, std::string>::type
{
    typename std::tuple_element<I, Tup>::type value(std::get<I>(tup));
    return ::TypeConverter::toString(value, settings);
}

template<typename Tup, int I>
auto TypeConverter::impl::toStringTyped(const Tup& tup, const Settings& settings)
    -> typename std::enable_if<I != std::tuple_size<Tup>::value - 1, std::string>::type
{
    typename std::tuple_element<I, Tup>::type value(std::get<I>(tup));
    return ::TypeConverter::toString(value, settings) + settings.separator + toStringTyped<Tup, I+1>(tup, settings);
}

