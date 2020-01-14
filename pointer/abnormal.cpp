/*
 * abnormal.cpp
 * C++ primer plus 6, 15.3
 *  Created on: Jul 24, 2019
 *      Author: Jian Rong
 *
 */
#include <iostream>
#include <cstdlib> // C <stdlib.h>
#include <unistd.h>
/**
 * Abort() 典型实现是向标准错误流（err使用的错误流）发送消息
 * abnormal program termination（程序异常终止），然后终止程序
 * 还返回一个随实现而异的值，告诉操作系统（如果程序由另一个程序调用，
 * 则告诉父进程），处理失败，abort（）是否刷新文件缓冲区（用于存储
 * 读写到文件中的数据的内存区域）取决于实现。如果愿意，也可以使用exit()
 * ，该函数刷新文件缓冲区，但不显示消息
 */
#include <cfloat> // (or float.h) for DBL_MAX
#include <cmath>

// abort
double hmean_abort(double, double);
void test_hmean_abort();

// return error code
bool hmean(double, double, double *);
void test_hmean();

// try {} catch {}
double hmean_try_catch(double, double);
void try_catch();

/***
 * keyword
 * 	noexcept :
 * 	C++11特殊的异常规范，关键字noexcept，用来指出函数不会引发异常
 */
// 将对象用作异常类型
class bad_hmean
{
private:
	double v1;
	double v2;
public:
	bad_hmean(int a = 0, int b = 0) : v1(a), v2(b) {}
	void mesg();
};

inline void bad_hmean::mesg()
{
	std::cout << "hmean(" << v1 << ", " << v2 << "): "
			<< "invalid arguments: a = -b\n";
}

class bad_gmean
{
public:
	double v1;
	double v2;
	bad_gmean(double a = 0, double b = 0) : v1(a), v2(b) {}
	const char * mesg();
};

inline const char * bad_gmean::mesg()
{
	return "*gmean() arguments should be >= 0\n";
}

double hmean_c(double a, double b)
{
	if (a == -b)
		throw bad_hmean(a,b);
	return 2.0 * a * b / (a + b);
}

double gmean_c(double a, double b)
{
	if (a < 0 || b < 0)
		throw bad_gmean(a, b);
	return std::sqrt(a * b);
}

void call_h_g_mean()
{
	using std::cout;
	using std::endl;

	double x, y, z;

	cout << "Enter two numbers: ";
	while(std::cin >> x >> y)
	{
		try { // start of try block
			z = hmean_c(x, y);
			cout << "Harmonic mean of " << x << " and " << y
					<< " is " << z << endl;
			cout << "Geometric mean of " << x << " and " << y
					<< " is " << gmean_c(x,y) << endl;
			cout << "Enter next set of numbers <q to quit>: ";
		} // end of try block
		catch(bad_hmean &bg)
		{
			bg.mesg();
			cout << "Try again.\n";
			continue;
		}
		catch (bad_gmean &hg)
		{
			cout << hg.mesg();
			cout << "Values used:" << hg.v1 << ", "
					<< hg.v2 << endl;
			cout << "Sorry, you don't get to play any more.\n";
			break;
		}
	}
	cout << "Bye!\n";
}

int main()
{
//	test_hmean_abort();
//	test_hmean();
//	try_catch();
	call_h_g_mean();
	return 0;
}

double hmean_abort(double a, double b)
{
	if (a == -b)
	{
		std::cout << "untenable arguments to hmean()\n";
		std::abort();
	}
	return 2.0 * a * b / (a + b);
}

void test_hmean_abort()
{
	double x, y, z;
	std::cout << "Enter two numbers: ";
	while(std::cin >> x >> y)
	{
		z = hmean_abort(x,y);
		double a;
		hmean(1,2,&a);
		std::cout << "Harmonic mean of " << x << " and " << y
				<< " is " << z << std::endl;
		std::cout << "Enter next set of numbers <q to quit>: ";
	}
	std::cout << "Bye!\n";
}

bool hmean(double a, double b, double *ans)
{
	if (a == -b)
	{
		*ans = DBL_MAX;
		return false;
	}
	else
	{
		*ans = 2.0 * a * b / (a + b);
		return true;
	}
}

void test_hmean()
{
	double x, y, z;
	std::cout << "Enter two numbers: ";
	while(std::cin >> x >> y)
	{
		if (hmean(x,y,&z))
			std::cout << "Harmonic mean of " << x << " and " << y
					<< " is " << z << std::endl;
		else
			std::cout << "One value should not be the negative "
				<< "of the other - try again.\n";

		std::cout << "Enter next set of numbers <q to quit>: ";
	}

	std::cout << "Bye!\n";
}


double hmean_try_catch(double a, double b)
{
	if (a == -b)
		/*
		 * throw类似于执行返回语句，因为他也将终止函数执行；但throw
		 * 不是将控制权返回给调用程序，而是导致程序沿函数调用序列后退，
		 * 直到找到try块的函数
		 */
		throw "bad hmean() argument: a = -b not allowed";

	return 2.0 * a * b / (a+b);
}


void try_catch()
{
	double x, y, z;
	std::cout << "Enter two numbers: ";
	while (std::cin >> x >> y)
	{
		try {					// start of try block
			z = hmean_try_catch(x, y);
		}						// end of try block
		catch (const char * s) // start of exception handler
		{
				std::cout << s << std::endl;
				std::cout << "Enter a new pair of numbers: ";
				continue;
		} 					// end of handler
		std::cout << "Harmonic mean of " << x << " and " << y
				<< " is " << z << std::endl;
		std::cout << "Enter next set of numbers <q to quit>: ";
	}

	std::cout << "Bye!\n";
}
