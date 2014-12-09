#include "VectorHelper.hxx"

namespace dbobject {
namespace VectorHelper {

std::string concat(const std::vector<std::string>& vs, const std::string& link)
{
    return concat(vs, link, std::string());
}

std::string concat(const std::vector<std::string>& vs, const std::string& link, const std::string& around)
{
    return concat(vs, link, around, around);
}

std::string concat(const std::vector<std::string>& vs, const std::string& link, const std::string& left, const std::string& right)
{
    std::string result;

    for (auto& v : vs) {
        result += left;
        result += v;
        result += right;
        result += link;
    }
    result.erase(result.size()-link.size());

    return result;
}

}
}
