#include <iostream>
#include <bitset>
#include <string>
#include <cmath>

using namespace std;

/*
 * bitset对象的定义和初始化
 *  用unsigned值初始化bitset对象
 *  用string对象初始化bitset对象
 * bitset对象上的操作
 *  测试整个bitset对象
 *  访问bitset对象中的位
 *  对整个bitset对象进行设置
 *  获取bitset对象的值
 *  输出二进制位
 */
int example1()
{
    bitset<32> a; // a的大小　32位，全部为0
    cout << a << endl;
    
    bitset<128> d(0xffff);
    cout << d << endl;  

    bitset<128> e(156);
    cout << e << endl;
    
    string str("1111110000");
    bitset<32> f(str);
    cout << str << endl;
 
    string str2("11111100001");
    bitset<32> f2(str2, str2.size()-4);
    cout << f2 << endl;
    
    string str11("1111111111100000");
    bitset<32> f11(str11, 7, 4);
    cout << f11 << endl;
    
    return 0;
}

int example2()
{
    bitset<32> a(156);
    cout << a << endl;
    
    bool is_set = a.any(); // 检查bitset是否存在为１的二进制位，　存在返回true
    cout << is_set << endl;
    if (is_set) 
        cout << "bitset a 中存在为１的biｔ位" << endl;

    bool is_not_set = a.none(); // 检查bitset是否都为０
    cout << is_not_set << endl;
    if (is_not_set)
        cout << "bitset a 中不存在为１的bit位" << endl;

    size_t bits_set = a.count(); // 统计bitset中位为１的个数
    cout << "bitset a中有" << bits_set << " 位1" << endl;

    size_t bits_size = a.size(); // bitset的大小
    cout << "bitset a的大小为" << bits_size << "位" << endl;

    return 0;
}

// change bitset
int example3()
{
    bitset<32> a;
    cout << a << endl;

    a[5] = 1;   // 将bitset第５位,设置为1
    cout << a << endl;
    
    a.set(6,1); //　将bitset第６位,设置为１
    cout << a << endl;

    a.set(); // 将bitset全部设置为１
    cout << a << endl;
    
    a.reset(5); // 将第５为设置为0
    cout << a << endl;
 
    a.flip(); // 翻转bitset, 0变1，　1变0
    cout << a << endl;
 
    a.flip(8);  // 翻转第８位
    cout << a << endl;
    
    a.reset(); // 全部设置为0
    cout << a << endl;
    
    unsigned long b = a.to_ulong();
    cout << b << endl;
    
    a.set();
    b = a.to_ulong();
    cout << b << endl;

    return 0;
}

// bit operation
int example4()
{

    bitset<12> a(string("111111111"));
    bitset<12> b(string("111010101"));

    cout << "  "<< a << endl;
    cout << "  " << b << endl;

    cout << "& " << (a & b) << endl;
    cout << "| " << (a | b) << endl;
    cout << "^ " << (a ^ b) << endl;
    return 0;
}

/*
 * bitset应用实例   艾拉托斯特尼筛选法　"筛法"
 * 质数: 只能被它本身和１整除的数, 不能被其他数整除，否则为合数，１不是质数也不是合数
 *
 * "筛法",用来查找质数,早在两千年前就被希腊数学家艾拉托斯特尼发现了
 *
 * 合数特性，任何非质数至少有一个因数不会大于它的平方根
 *
 * 先把N个自然数按次序排列起来.１不是质数,也不是合数,要划去.第二个数２是质数
 * 留下来,而把2后面所有能被２整除的数都划去.２后面第一个没划去的数是３，把３
 * 留下，再把３后面所有能被３整除的数划去。３后面第一个划去的数是５，把５留下
 * ，再把５后面所有能被５整除的数划去。这样一直做下去，就会把不超过N的全部合数
 * 筛选掉，留下来的就是不超过N的质数
 *
 */
int example5()
/* int main() */
{
    clock_t start_time, end_time;

    start_time = clock();

    int const max_number(10000000);
    int const max_test((int)sqrt((double)max_number));

    bitset<max_number + 1> numbers;
    numbers.set(); // 101个１!
    
    /* numbers[0]; */ // 忽略
    numbers[1] = 0;
    
    for (int i(1); i != max_test; ++i) {
        /* cout << "i = " << i << endl; */
        if (numbers[i]) {
            // 筛掉倍数
            for (int j(i * i); j < max_number + 1; j += i) {
                /* cout << "j = " << j << endl; */
                numbers[j] = 0;
            }
        }
    }

    cout << "the number of primes less than " << max_number 
        << " is " << numbers.count() << ".\n\n";

    for (int i(1); i != max_number + 1; i++) {
        if (numbers[i]) 
            cout << i << " ";
    }
    cout << endl;
     
    end_time = clock();
    cout << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
    return 0;
}

int main()
/* int example6() */
{
    clock_t start_time, end_time;
    start_time = clock();

    int const max_number(10000000);
    bitset<max_number + 1> numbers;

    numbers.set();
    numbers[1] = 0;

    for (int i(1); i != max_number + 1; ++i) {
        if (numbers[i]) {
            for (int j(i*2); j < max_number + 1; j += i) {
                numbers[j] = 0;
            }
        }
    }

    for (int i(1); i != max_number + 1; ++i) {
        if (numbers[i]) {
            cout << i << " ";
        }
    }
    cout << endl;

    end_time = clock();
    cout << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
    
    return 0;
}
