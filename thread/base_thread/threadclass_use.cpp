#include <unistd.h>
#include <iostream>
#include <thread>
#include <sstream>

using std::cout;
using std::endl;
using std::thread;
using std::string;
using std::ostringstream;

void *test1_func(int, int);
void *test2_func(unsigned long long);

int main()
{
	thread test1(test1_func, 1, 2);
	ostringstream oss;
	oss << test1.get_id();
	string stid = oss.str();
	unsigned long long test1_id = std::stoull(stid);
	test1.detach();

	thread test2(test2_func, test1_id);
	test2.join();

	for (;;) {
		sleep(1);
		cout << "main thread run " << endl;
	}

	return 0;
}

void *test1_func(int a, int b)
{
	cout << "test1 thread run, argument is " << a << " and " << b << endl;
	return nullptr;
}

void *test2_func(unsigned long long arg)
{
	cout << "test2 thread run ,argument " << arg << " is id of test1 thread " << endl;
	return nullptr;
}
