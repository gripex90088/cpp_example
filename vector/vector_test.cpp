/*
 * vector_test.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: xuxing
 */

#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

void push_back_vector()
{
	int myint, sum (0);
	std::vector<int> int_vector;

	do {
		std::cin >> myint;
		int_vector.push_back(myint);
	} while(myint);
	std::cout << "myvector stores " << int(int_vector.size()) << " numbers\n";

	while(!int_vector.empty())
	{
		cout << int_vector.back() << endl;
		sum += int_vector.back();
		int_vector.pop_back();
	}
	cout << "The elements of int_vectors add up to " << sum << "\n";

}

void insert()
{
	std::vector<int> myvector (3,100);
	std::vector<int>::iterator it;
	for (it = myvector.begin(); it < myvector.end(); it++)
	{
		cout << " " << *it;
	}

	cout << " \n";

	/* insert a two 400 */
	std::vector<int> anothervector(2,400);
	it = myvector.begin();
	myvector.insert(it, anothervector.begin(), anothervector.end());
	for (it = myvector.begin(); it < myvector.end(); it++)
	{
		cout << " " << *it;
	}
	cout << " \n";

	/* insert a two 400 */
	it = myvector.begin();
	it = myvector.insert(it,3, 200);
	for (it = myvector.begin(); it < myvector.end(); it++)
	{
		cout << " " << *it;
	}
	cout << " \n";

	myvector.insert(it, 2, 300);
	for (it = myvector.begin(); it < myvector.end(); it++)
	{
		cout << " " << *it;
	}
	cout << " \n";

	int myarray[] = {501,502,503};
	myvector.insert(myvector.begin(), myarray, myarray+3);
	std::cout << "myvector contains:";
	for (it = myvector.begin(); it < myvector.end(); it++)
	{
		cout << " " << *it;
	}
	cout << "\n";
}

struct A{
	int a;
	string b;
};
int main()
{
	//cout << a.front() << endl;
	return 0;
}



