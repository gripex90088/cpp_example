#include <iostream>
#include <ctime>
#include <cstring>
#include "md5.h"

using namespace std;
string getTimeStampStr()
{
    char buf[50];
    time_t t_stamp = time(NULL);
    sprintf(buf, "%ld", t_stamp);

    cout << buf << endl;
    return buf;
}

int main()
{
    char a[100];
    char b[100] = "Hello World"; 
    char sign[300] = "b10a8db164e0754105b7a99be72e3fe5";
   
    string check_ = "421b47ffd946ca083b65cd668c6b17e6"; 
    
    getmd5(a, (getTimeStampStr().c_str() + check_).c_str());
    cout << a << endl;

/*
    getmd5(a, b); string si = a;
    if (si != sign) {
        cout << "sign error" << endl;
    }

    std::cout << "Hello world" << std::endl;
  */
    return 0;
}

