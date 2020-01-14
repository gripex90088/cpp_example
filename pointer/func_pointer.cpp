/*
 * func_pointer.cpp
 * C++ primer plus 6, 7.1
 *
 *  Created on: Jul 23, 2019
 *      Author: Jian Rong
 */


// basic knowledge
/**
 * 使用函数指针
 * 1. 获取函数的地址  process(func):传递函数名,   process(func()): 这是传递返回值
 * 2. 声明一个函数指针
 * 		double pam(int);		// prototaype
 *		double (*pf) (int);		// pf points to a function that takes
 *								// one int argument and that
 *								// return type double
 * 3. 使用函数指针来调用函数
 */

// function pointer example
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

double betsy(int);
double pam(int);
// second argument is pointer to a type double function that
// takes a type int argument
void estimate(int lines, double (*pf)(int));

// various notations, same signatures
const double * f1(const double ar[], int n);
const double * f2(const double [], int);
const double * f3(const double *, int);

// 使用typedef进行简化
// p_fun now a type name
typedef const double * (*p_fun) (const double *, int);
p_fun p1 = f1;	// p1 points to the f1() function

p_fun pa[3] = { f1, f2, f3}; // pa an array of 3 function pointers
p_fun (*pb)[3] = &pa; 		// pb points to an array of 3 function pointers

/***
 * Exercises
 */

/**
 * 1 使用函数指针的3个步骤
 * 	a) 获取函数地址
 * 	b) 声明函数指针
 * 	c) 使用函数指针调用函数
 *
 * C++3种C风格字符串
 * 	a) 字符数组
 * 	b) 字符串常量
 * 	c) 字符串指针
 * 	他们的类型都是char*，因此被作为char*类型参数传递给函数
 */

long summation(const long a[], int a_len)
{
	return 111;
}

int main()
{
	long a[10] = {1,2,3,4,5};
	int len = 10;
	long (*sum)(const long *, int) = summation;
	cout << (*sum)(a, len) << endl;
	return 0;
/*
	int code;
	cout << "How many lines of code do you need?";
	cin >> code;
	cout << "Here's Betsy's estimate:\n";
	estimate(code, betsy);
	cout << "Here's Pam's estimate:\n";
	estimate(code, pam);
*/
	double av[3] = {1112.3, 1542.6, 2227.9};

	// pointer to a function
	const double *(*p1)(const double *, int) = f1;
	auto p2 = f2;	// C+=11 automatic type deduction
	// pre-C++111 can use the following code instead
	// const double *(*p2)(const double *, int) = f2;
	cout << "Using pointers to functions:\n";
	cout << " Address Value\n";
	cout << (*p1)(av,3) << ": " << *(p1)(av, 3) << endl;
	cout << p2(av,3) << ": " << *p2(av,3) << endl;

	// pa an array of pointers
	// auto doesn't work with list initialization
	const double *(*pa[3]) (const double *, int) = {f1, f2, f3};
	// but it does work for initializing to a single value
	// pb a pointer to first element of pa
	auto pb = pa;
	// pre-C++11 can use the following code instead
	// const double *(**pb) (const doubele *, int) = pa
	cout << "\nUsing an array of pointers to functions:\n";
	cout << " Address Value\n";
	for (int i = 0; i < 3; i++)
		cout << pa[i](av,3) << ": " << *pa[i](av,3) << endl;
	cout << "\nUsing a pointer to a pointer to a function\n";
	cout << " Address Value\n";
	for (int i = 0; i < 3; i++)
		cout << pb[i](av,3) << ": " << *pb[i](av,3) << endl;

	// what about a pointer to an array of function pointers
	cout << "\nUsing pointers to an array of pointers:\n";
	cout << " Address Value\n";
	/*
	 * auto pc = &pa;	// C++ automatic type deduction
	 * const double *(*(*pd)[3]) (const double *, int) = &pa; // C++ 98 do it yourself
	 */
	// easy way to declare pc
	auto pc = &pa;
	// pre-C++11 can use the following code instead
	// const double *(*(*pc)[3]) (const double *, int) = &pa;
	cout << (*pc)[0](av,3) << ": " << *(*pc)[0](av,3) << endl;
	// hard way to declare pd
	const double *(*(*pd)[3]) (const double *, int) = &pa;
	// store return value in pdb
	const double * pdb = (*pd)[1](av,3);
	cout << pdb << ": " << *pdb << endl;

	// altrenative notation
	cout << (*(*pd)[2])(av,3) << ": " <<*(*(*pd)[2])(av,3) << endl;
	// cin.get();
	return 0;
}

double betsy(int lns)
{
	return 0.05 * lns;
}

double pam(int lns)
{
	return 0.03 * lns + 0.0004 * lns * lns;
}

void estimate(int lines, double (*pf)(int))
{
	cout << lines << "Lines will take ";
	cout << (*pf)(lines) << " hour(s)\n";
}

const double * f1 (const double * ar, int n)
{
	return ar;
}

const double * f2(const double ar[], int n)
{
	return ar+1;
}

const double * f3(const double ar[], int n)
{
	return ar + 2;
}
