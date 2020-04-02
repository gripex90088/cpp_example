#include <iostream>
#include <time.h>

using namespace std;


void getTimeStampStr(string * const timeStr)
{

    char buf[50];

    time_t t_stamp = time(NULL);
    tm* local_time = localtime(&t_stamp);
    
    sprintf(buf, "%ld", t_stamp);
    *timeStr = buf;
}

int main()
{
    // Get current time stamp
    time_t t_stamp = time(NULL);
    cout << t_stamp << endl;
    
    char buf[50];
    tm* local_time = localtime(&t_stamp);
    strftime(buf, sizeof(buf), "%F %X", local_time);
    cout << buf << endl;

    char buf1[50];
    sprintf(buf1, "%ld", t_stamp);
    cout << buf1 << endl;
    
    string tim;
    getTimeStampStr(&tim);
    cout << "=====================" << endl;
    cout << tim << endl;
    return 0;
}

