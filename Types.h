#ifndef DBOBJECT_DBTYPES_H
#define DBOBJECT_DBTYPES_H

#include <memory>
#include <vector>

namespace dbobject {

template<typename T> struct Ptr
{
    typedef std::shared_ptr<T> type;
};

template<typename T> struct List
{
    typedef std::vector<typename Ptr<T>::type> type;
};

}

#endif
