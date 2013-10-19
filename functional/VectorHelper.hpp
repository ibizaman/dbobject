namespace dbobject {
namespace VectorHelper {

template<typename T>
std::vector<T> merge(const std::vector<T>& a, const std::vector<T>& b)
{
    std::vector<T> result;

    result.reserve(a.size() + b.size());
    result.insert(result.end(), a.begin(), a.end());
    result.insert(result.end(), b.begin(), b.end());

    return result;
}

template<typename Traversable, typename UnaryOp>
std::vector<typename UnaryOp::result_type> map(const Traversable& list, UnaryOp op)
{
    std::vector<typename UnaryOp::result_type> strings;

    for (auto elem : list)
    {
        strings.push_back(op(elem));
    }

    return strings;
}

}
}
