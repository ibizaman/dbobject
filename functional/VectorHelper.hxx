#ifndef DBOBJECT_VECTORHELPER_H
#define DBOBJECT_VECTORHELPER_H

#include <string>
#include <vector>

namespace dbobject {

namespace VectorHelper {
    template<typename T> std::vector<T> merge(const std::vector<T>&, const std::vector<T>&);
    std::string concat(const std::vector<std::string>&, const std::string&);
    std::string concat(const std::vector<std::string>&, const std::string&, const std::string&);
    std::string concat(const std::vector<std::string>&, const std::string&, const std::string&, const std::string&);

    template<typename Traversable, typename UnaryOp>
        std::vector<typename UnaryOp::result_type> map(const Traversable&, UnaryOp);
}

}

#include "VectorHelper.hpp"

#endif
