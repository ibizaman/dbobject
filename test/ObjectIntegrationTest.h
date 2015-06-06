#include <gtest/gtest.h>

#include "TupleIntegrationTest.h"
#include "Object.h"
#include <memory>

using namespace dbobject;

namespace dbobject {

typedef std::tuple<bool, int, std::string> test_tuple;

class ObjectIntegrationTest : public TupleIntegrationTest
{
public:
    ObjectIntegrationTest(const SQL::TableName& = SQL::TableName("DummyObject"));

    static void SetUpTestCase();

    static std::shared_ptr<Object> dbobject;
};

}
