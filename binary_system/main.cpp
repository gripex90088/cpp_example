#include <iostream>

/*
 * 进制　例如十进制　
 *
 * 权值：
 *  十进制
 *  　1 + 9 = 10　逢10进１ 权值 万，千，百, 十，个
 *  八进制
 *  　20 2表示２个8
 *  二进制　
 *   权值 128, 64, 32, 16, 8, 4, 2, 1
 *    
 *  十六进制和二进制之间完美的转换关系
 *
 *
 */

int main()
{
    int a = 12;
    printf("%d\n", a);

    int b = 0x12;
    printf("%d\n", b);
    
    int c = 0x1a;
    printf("%d\n", c);

    std::cout << "Hello world" << std::endl;
    return 0;
}

