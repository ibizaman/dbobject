#ifndef DBOBJECT_BACKENDMOCK_H
#define DBOBJECT_BACKENDMOCK_H

#include <gmock/gmock.h>
#include "backends/Backend.h"

namespace dbobject {

class BackendMock : public Backend
{
public:
    MOCK_METHOD1(query, std::shared_ptr<sql::ResultSet>(const SQL::Select&));
    MOCK_METHOD1(query, Backend::count(const SQL::Insert&));
    MOCK_METHOD1(query, Backend::count(const SQL::Update&));
};

}

#endif
