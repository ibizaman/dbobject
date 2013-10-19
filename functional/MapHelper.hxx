#ifndef DBOBJECT_MAPHELPER_H
#define DBOBJECT_MAPHELPER_H

#include <string>
#include <map>
#include <vector>

namespace dbobject {

namespace MapHelper {
    template<typename InputIteratorK, typename InputIteratorV>
    auto zip(const InputIteratorK&, const InputIteratorK&, const InputIteratorV&, const InputIteratorV&)
        -> std::map<typename std::iterator_traits<InputIteratorK>::value_type, typename std::iterator_traits<InputIteratorV>::value_type>;
    template<typename K, typename V> std::vector<K> keys(const std::map<K,V>&);
    template<typename K, typename V> std::vector<V> values(const std::map<K,V>&);
    template<typename K, typename V> std::map<K,V> only(const std::map<K,V>&, const std::vector<K>&);
    template<typename K, typename V> std::map<K,V> exclude(const std::map<K,V>&, const std::vector<K>&);

    template<typename K, typename V>
    std::string concat(const std::map<K,V>&, const std::string&, const std::string&);
    template<typename K, typename V>
    std::string concat(const std::map<K,V>&, const std::string&, const std::string&, const std::string&, const std::string&);
    template<typename K, typename V>
    std::string concat(const std::map<K,V>&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
}

}

#include "MapHelper.hpp"

#endif
