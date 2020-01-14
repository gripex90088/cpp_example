#include <iostream>
#include <cstdlib>
#include <ctime>


int main()
{
//	using namespace std;
	long i = 100000000L;
	clock_t start, finish;
	double  duration;

	/* 测量一个事件持续的时间*/
	printf( "Time to do %ld empty loops is ", i );
	start = clock();
	int a = 0;
	int b = 1;
	while( i-- )
	{
	    a = 0;
	    a = a * 3;
	    b = a * a;
	    b += b;
	    a -= a;
	}
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf( "%f seconds\n", duration );
}
