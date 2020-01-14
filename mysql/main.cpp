#include <iostream>
#include <mysql++/mysql++.h>

using namespace std;

int main()
{

    const char *db = 0, *server = 0, *user = 0, *password = "";

    db = "test";
    server = "localhost";
    user = "root";
    password = "1234567";

    mysqlpp::Connection conn(false);

    std::cout << "Hello world" << std::endl;
    return 0;
}

