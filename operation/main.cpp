#include <iostream>

using namespace std;

int main()
{

    int a = 101;
    int b = a >> 2;
    
    // 位与运算符
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    
    cout << "a1 = " <<  a1 << " a2 = " << a2 << " a3 =" << a3 << endl;
    cout << "& " << endl;
    cout << "a1 & a2 = " << (a1 & a2) << endl;
    cout << "a2 & a3 = " << (a2 & a3) << endl;
    

    cout << "| " << endl;
    cout << "a1 | a2 = " << (a1 | a2) << endl;  
    cout << "a2 | a3 = " << (a2 | a3) << endl;
    
    cout << "^ " << endl;
    cout << "a1 ^ a2 = " << (a1 ^ a2) << endl;
    cout << "a2 ^ a3 = " << (a2 ^ a3) << endl;

    
    cout << "~ " << endl;
    cout << "~128 = " << ~128 << endl;
    cout << "~5 = " << ~5 << endl;
    cout << "~a1 = " << (~a1) << endl;
    cout << "~a2 = " << ~a2 << endl;
    cout << "~a3 = " << ~a3 << endl;

    cout << "<< " << endl;
    cout << "a1 << 1 = " << (a1 << 1) << endl;
    cout << "a1 << 8 = " << (a1 << 8) << endl;
    cout << "a1 << 1 = " << (a1 << 1) << endl;
    cout << "a2 << 1 = " << (a2 << 1) << endl;
    cout << "a3 << 1 = " << (a3 << 1) << endl;


    // >> 右移运算符
    cout << ">> " << endl;
    cout << "1 >> 3 = " << ~(1 >> 3) << endl; 
    cout << "10 >> 12 = " << (10 >> 12) << endl;
    cout << "a1 >> 1 = " << (a1 >> 1) << endl;
    cout << "a2 >> 1 = " << (a2 >> 1) <<  endl;
    cout << "a3 >> 1 = " << (a3 >> 1) << endl;
    
    // 位或运算符
    cout << (a1 | a2) << endl;


    // 位异或运算符
    cout << (a1 ^ a2) << endl;

    // 二进制补码运算符
    cout << (~a1) << endl;

    // 二进制左移运算符
    cout << (a2 << 1) << endl;
    
    // 二进制右移运算符
    cout << (a2 >> 1) << endl;
    
    std::cout << "Hello world" << std::endl;
    return 0;
}

