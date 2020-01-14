#include <iostream>

using namespace std;

double pam(int);

void estamite(int l, double (*pf)(int));

long summation(const long a[], int a_len);

const double *f1(const double ar[], int n);

int main()
{
	int code = 2;
	estamite(2, pam);

	/* summation */
	long a[10] = {1,2,3,4,5};
	int len = 10;

	long (*sum)(const long *, int) = summation;
	cout << (*sum)(a, len) << endl;

	double av[3] = {1.1, 1.2, 1.3};
	const double *(*p1)(const double *, int) = f1;
	cout << (*p1)(av, 3) << ": " << *(p1)(av, 3) << endl;

	return 0;
}

const double *f1(const double ar[], int n)
{
	return ar;
}

double pam(int l)
{
	return l * 0.2;
}

void estamite(int l, double (*pf)(int))
{
	cout << l << endl;
	cout << (*pf)(l) << endl;
}

long summation(const long a[], int a_len)
{
	int sum = 0;
	for (int i = 0; i < a_len; i++) {
		sum += a[i];
	}
	return sum;
}
