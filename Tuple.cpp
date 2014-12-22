#include "Tuple.h"

namespace dbobject {

Tuple::Tuple(std::shared_ptr<Backend> backend)
    : _backend(backend)
{
}

void Tuple::setBackend(std::shared_ptr<Backend> backend)
{
    _backend = backend;
}

std::shared_ptr<sql::ResultSet> Tuple::query(const SQL::Select& select)
{
    return _backend->query(select);
}

Backend::count Tuple::query(const SQL::Insert& insert)
{
    return _backend->query(insert);
}

Backend::count Tuple::query(const SQL::Update& update)
{
    return _backend->query(update);
}

}
