#ifndef SQLCONFFILE_H
#define SQLCONFFILE_H

#include <istream>
#include <cppconn/connection.h>

namespace File
{

sql::ConnectOptionsMap parseToSQLConnectOptionsMap(std::istream&);

}

#endif
