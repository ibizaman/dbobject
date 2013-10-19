#include <algorithm>

namespace dbobject {
namespace MapHelper {

template<typename InputIteratorK, typename InputIteratorV>
auto zip(const InputIteratorK& kbegin, const InputIteratorK& kend, const InputIteratorV& vbegin, const InputIteratorV& vend)
    -> std::map<typename std::iterator_traits<InputIteratorK>::value_type, typename std::iterator_traits<InputIteratorV>::value_type>
{
    typedef typename std::iterator_traits<InputIteratorK>::value_type K;
    typedef typename std::iterator_traits<InputIteratorV>::value_type V;
    std::map<K,V> map;

    auto k = kbegin;
    auto v = vbegin;
    for (; (k != kend) && (v != vend); ++k, ++v) {
        map.insert(std::pair<K,V>(*k,*v));
    }

    return map;
}

template<typename K, typename V>
std::vector<K> keys(const std::map<K,V>& map)
{
    std::vector<K> ks;
    ks.reserve(map.size());

    for (auto& pair : map) {
        ks.push_back(pair.first);
    }

    return ks;
}

template<typename K, typename V>
std::vector<V> values(const std::map<K,V>& map)
{
    std::vector<V> vs;
    vs.reserve(map.size());

    for (auto& pair : map) {
        vs.push_back(pair.second);
    }

    return vs;
}

template<typename K, typename V>
std::map<K,V> only(const std::map<K,V>& map, const std::vector<K>& keys)
{
    std::map<K,V> ret;

    for (auto& key : keys) {
        ret.insert(*map.find(key));
    }

    return ret;
}

template<typename K, typename V>
std::map<K,V> exclude(const std::map<K,V>& map, const std::vector<K>& keys)
{
    std::map<K,V> ret;

    for (auto& pair : map) {
        if (find(keys.begin(), keys.end(), pair.first) == keys.end()) {
            ret.insert(pair);
        }
    }

    return ret;
}

template<typename K, typename V>
std::string concat(const std::map<K,V>& map, const std::string& center, const std::string& link)
{
    return concat(map, center, link, std::string(), std::string());
}

template<typename K, typename V>
std::string concat(const std::map<K,V>& map, const std::string& center, const std::string& link, const std::string& key, const std::string& value)
{
    return concat(map, center, link, key, key, value, value);
}

template<typename K, typename V>
std::string concat(const std::map<K,V>& map, const std::string& center, const std::string& link, const std::string& lkey, const std::string& rkey, const std::string& lvalue, const std::string& rvalue)
{
    std::string result;

    for (auto pair : map) {
        result += lkey;
        result += pair.first;
        result += rkey;
        result += center;
        result += lvalue;
        result += pair.second;
        result += rvalue;
        result += link;
    }
    result.erase(result.end()-link.size(), result.end());

    return result;
}

}
}
