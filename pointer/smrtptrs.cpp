/*
 * C++ primer plus 16.2
 * smtrptrs.cpp -- using three kinds of smart pointers
 * require support of C++11 shared_ptr and unique_ptr
 *
 *  Created on: Jul 23, 2019
 *      Author: Jian Rong
 */
#include <iostream>
#include <memory> // unique_ptr
#include <string>

using namespace std;
/**
 * auto_ptr
 * shared_ptr
 * unique_ptr
 * weak_ptr
 */

class Report
{
private:
	std::string str;
public:
	Report(const string s) : str(s)
			{ cout << "Object created!\n"; }
	~Report() { std::cout << "Object delete！\n"; }
	void comment() const { cout << str << "\n"; }
};

unique_ptr<string> demo(const char * s)
{
	unique_ptr<string> temp(new string(s));
	return temp;
}

int main()
{
	{
		auto_ptr<Report> ps (new Report("using auto_ptr"));
		ps->comment();
	}

	{
		shared_ptr<Report> ps (new Report("using shared_ptr"));
		ps->comment();
	}

	{
		unique_ptr<Report> ps (new Report("using unique_tr"));
		ps->comment();
	}


	// careful
	/*
	 * 1.pvac过期时， 程序将把delete运算符用于堆内存，这是错误的
	 * 		string vacation("I wandered lonely as a cloud.");
	 *  	shared_ptr<string> pvac(&vacation);
	 *
	 */
	// error example
	auto_ptr<string> films[5] =
	{
			auto_ptr<string> (new string("Fowl Balls")),
			auto_ptr<string> (new string("Duck Wallks")),
			auto_ptr<string> (new string("Chicken Runs")),
			auto_ptr<string> (new string("Turkey Errors")),
			auto_ptr<string> (new string("Goose Eggs"))
 	};
	auto_ptr<string> pwin;
	pwin = films[2]; // films[2] loses ownership

	cout << "The nominees for best avian baseball film are\n";
	for (int i = 0; i < 5; i++)
		cout << *films[i] << endl;
	cout << "The winner is  " << *pwin << "!\n";
	cin.get();
	/**
	 * output
	 * The nominees for best avian baseball film are
	 * Fowl Balls
	 * Duck Wallks
	 * Segmentation fault (core dumped)
	 * 错误的使用auto_ptr可能导致问题（这种代码的行为是不确定的，其行为可能随系统而异
	 * 这里的问题在于pwin = films[2]将所有权从fimls[2]转移给pwin,导致films[2]不再
	 * 引用该字符串，在auto_ptr放弃对象的所有权后，便可能使用他来访问该对象，当程序打印
	 * films[2]时，却发现这是一个空指针 (悬挂指针)。
	 */


	/**
	 * unique_ptr
	 * 有时候一个智能指针赋值给另一个并不会留下危险的悬挂指针
	 */
	// example 1
	unique_ptr<string> ps;
	ps = demo("Uniquely special");
	// example 2
/*
	unique_ptr<std::string> pu1(new string ("Hi ho!"));
	unique_ptr<string> pu2;
	pu2 = pu1; // not allowed
*/
	unique_ptr<string> pu3;
	pu3 = unique_ptr<string>(new string("Yo!")); // allowed
	/**
	 * 程序试图将一个unique_ptr赋给另一个时，如果源unique_ptr是个临时右值，编译器
	 * 允许这样做，如果源unique_ptr将存在一段时间，编译器将禁止这样做
	 */


	/**
	* unique_ptr的另一个优点，他有一个可用于数组的变体，auto_ptr使用delete而不是delete[]
	* 因此只能与new一起使用，unique_ptr有new[]和delete[]的版本
	*/
	unique_ptr<double[]> pda(new double(5));
	/**
	 * 使用new分配内存时，才能使用auto_ptr和share_ptr,使用new[]分配内存时，不能使用，
	 * 不使用new分配内存时，不能使用auto_ptr和shared_ptr；
	 * 不使用new或new[]分配内存时，不能使用unique_ptr
	 */
	return 0;
}




