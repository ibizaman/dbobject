#include "DummyObject.h"

namespace dbobject {

const SQL::List<SQL::ColumnName> Object::Properties<DummyObject>::fields = {
    "bool", "int", "string"
};
const SQL::TableName Object::Properties<DummyObject>::table("DummyObject");

}
