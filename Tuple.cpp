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

}
