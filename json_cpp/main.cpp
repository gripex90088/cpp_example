/*
 * main.cpp
 *
 *  Created on: Aug 5, 2019
 *      Author: JianRong
 */
#include <iostream>
#include <string.h>
//#include <json/json.h>
#include <string>
#include <cstring>
#include <jsoncpp/json/json.h>

using namespace std;

#define foo(arr) (sizeof(arr)/sizeof(arr[0]))

void test_aaaaa(const string strs[]);

template<class T>
int getLength(const T &arr) {
    return sizeof(arr) / sizeof(arr[0]);
}

int main()
{
	string aaaaa="{\"id\":1,\"name\":\"kurama\"}";
    int d[] = {1,2,3,4,5,6,7};
 
    Json::Reader reader;
    Json::Value value;
    if (reader.parse(aaaaa, value, true)) {
 
        Json::Value::Members arrayMembers = value.getMemberNames();
        for (Json::Value::Members::iterator iter = arrayMembers.begin(); iter != arrayMembers.end(); ++iter ) {
            cout << *iter << endl;
        }
    }
   
    /*
    cout << foo(c) << endl;
    cout << foo(d) << endl;
    cout << getLength(c) << endl;
    cout << getLength(d) << endl;
	*/
    return 0;
}
