/*
 * map.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: xuxing
 */

#include <iostream>
#include <map>

using namespace std;

typedef struct B{
	int a;
	int b;
	string c;
	string d;
	int e;
} Bb;

int main()
{
	map<string, Bb> aa;
	map<string, Bb> test_map;
	B b{1,2,"aaa","name is ZhangSan",3};

	test_map["aaa"] = b;
	test_map["bbb"] = b;
	test_map["ccc"] = b;


	string name ("aaa");
	cout << test_map.at(name).d << endl;

	map<string, Bb> test_map1(test_map.begin(), test_map.end());
	cout << test_map1.at(name).d << endl;

	map<string, int> ccc;
	ccc["a"] = 1;
	cout << ccc.find("a") << endl;
	return 0;
}
