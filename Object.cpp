
#include "Object.h"

namespace dbobject {

Object::Object(std::shared_ptr<Tuple> db)
    : _db(db)
{
}

void Object::setBackend(std::shared_ptr<Tuple> db)
{
    Object::setBackend(db);
}

}
