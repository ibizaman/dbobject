#include <gtest/gtest.h>

#include "MySQLBackendIntegrationTest.h"
#include "Tuple.h"
#include <memory>

using namespace dbobject;

typedef std::tuple<bool, int, std::string> test_tuple;

class TupleIntegrationTest : public MySQLBackendIntegrationTest
{
public:
    TupleIntegrationTest(const SQL::TableName& = SQL::TableName("TupleIntegrationTest"));

    static void SetUpTestCase();

    static std::shared_ptr<Tuple> dbtuple;
};
