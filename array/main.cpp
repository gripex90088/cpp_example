#include <iostream>

/**
 *
 * 数组缺点
 *      长度固定
 *      
 *
 */

unsigned get_size()
{
    int a(100);
    int b(200);

    return a + b;
}

int main()
{
    int a[100];

    const unsigned buf_size = 512, max_files = 20;
    int staff_size  = 27;

    const unsigned sz = get_size();

    std::cout << "Hello world" << std::endl;
    return 0;
}

