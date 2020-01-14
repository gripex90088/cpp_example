#include <iostream>
#include <json/json.h>
#include <cstring>

using namespace std;

void test(const char  a[][5], int arr_len, char * c);
void test(const char aa[][5], int arr_len, char * c) {
    
	string aaaaa="{\"id\":1,\"name\":\"kurama\"}";
 
    char ret[6] = "sadf";
    Json::Value value;
    Json::Reader reader;
    reader.parse(aaaaa, value, true);
    
    for (int i = 0; i < arr_len; i++) {
        
        if (!value.isMember(aa[0])) {
            strcpy(c, aa[i]);
            return ;
        }
    }

    return;
}


int main()
{

    char b[2][5] = {{"aid"}, {"name"}};
    char * c = nullptr;
    test(b, 2, c);
    
    cout << c << endl;   
    if (c) {
        cout << c << endl;
    }
    return 0;
}

