// vector type 
#include <iostream>
#include <vector> // vector header file
#include <string>   

using std::vector;
using std::string;
using std::cout;
using std::endl;

/*
 * vector 是一个动态数组
 * vector 是一个类模板 class template
 */
struct Custom_type {
    int a;
    double b;
};

int init_vector1()
{
    vector<int> ivec; // storage integer type  
    vector<double> dvec;    // storage double type
    vector<string> svec;    // storage string type
    vector<Custom_type> cvec;   // storage custom type 
    
    vector<int> a;  // a是一个容器
    vector<int> b(10, 2); // b 是一个容器， 里面有10个2

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    b.push_back(3);
    b.push_back(4);

    std::cout << a.size() << std::endl;
    std::cout << b.size() << std::endl;

    for (vector<int>::size_type i = 0; i != a.size(); i++) 
        std::cout << a[i] << std::endl;

    for (vector<int>::size_type i = 0; i != b.size(); i++) 
        std::cout << b[i] << std::endl;

    return 0;
}

int init_vector2()
{
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(11);
    v1.push_back(12);
    
    vector<int> v2(v1);
    
    vector<int> v4(10, -1);
    vector<string> v5(10, "hi");
    vector<int> v6(10); // 10个0
    vector<string> v7(10); // 10个空串

    std::cout << v1[0] << std::endl;
    std::cout << v2[0] << std::endl;
    std::cout << v4[0] << std::endl;
    std::cout << v5[0] << std::endl;
    std::cout << v6[0] << std::endl;
    std::cout << v7[0] << std::endl;
    
    v1[0] = 100;
    std::cout << v1[0] << std::endl;
    v7[0] = "Hello";
    std::cout << v7[0] << std::endl;

    return 0;
}

int init_vector3()
{
    vector<int> v;
    int k;
    string word;

    cout << v.size() << endl; 

    for (vector<int>::size_type i = 0; i < 5; i++) 
    {
        std::cin >> k;
        v.push_back(k);
    }

    cout << "print int vector" << endl;
    for (vector<int>::size_type i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }

    vector<string> text;
    while(std::cin >> word) {
        text.push_back(word);
    }

    for (vector<string>::size_type i = 0; i < text.size(); i++) {
        cout << text[i] + " ";
    }
    
    return 0;
}

// 相邻数相加
int example1()
{
    int ival;
    vector<int> ivec;

    cout << "Enter numbers(Ctrl+Z to end): " << endl;
    while(std::cin >> ival) 
        ivec.push_back(ival);

    if (ivec.empty()) {
        cout << "No element?!" << endl;
    }

    // 计算相邻的两数之和
    cout << "Sum of each pair of adjacent elements in the vector: " << endl;
    for (vector<int>::size_type ix = 0; ix < ivec.size() - 1; ix = ix + 2)
    {
        // 相邻两数和
        cout << ivec[ix] + ivec[ix+1] << endl;
    }

    if (ivec.size() % 2 != 0) 
        cout << endl
            << "The last element is not been summed "
            << " and  its  value is " 
            << ivec[ivec.size() - 1] << endl;
    
    return 0;
}

// 头尾相加
int example2()
{
    int ival;
    vector<int> ivec;
    
    cout << "Enter numbers(Ctrl+D to end): " << endl;
    while(std::cin >> ival)
        ivec.push_back(ival);

    if (ivec.empty()) {
        cout << "No element?!" << endl;
    }

    // 计算首尾之和
    cout << "Sum of each pair of counterpart element  in the vector: " << endl;

    vector<int>::size_type cnt = 0;
    vector<int>::size_type first, last;
    for (first = 0, last = ivec.size() - 1; first < last; ++first, --last) {
        cout << ivec[first] + ivec[last] << " ";
        ++cnt;
        if (cnt % 6 == 0) // 每行６个
            cout << endl;
    }

    if (first == last) 
        cout << endl 
            << "The center element is not been summed "
            << ivec[first] << endl;

    return 0;
}

int all2upper(string &str)
{
    for (string::size_type i = 0; i < str.size(); i++) {
        str[i] = toupper(str[i]);
    }

}

int 
main()
{
    string word;
    vector<string>::size_type cnt = 0;
    vector<string> text;

    while(std::cin >> word)
        text.push_back(word);

    if (text.empty()) {
        cout << "No element?!" << endl;
        return -1;
    }

    cout << "Transformed elements from the vector: " << endl;

    for (vector<string>::size_type i = 0; i < text.size(); i++) {
        for (string::size_type j = 0; j != text[i].size(); j++) {
          text[i][j] = toupper(text[i][j]); 
        }
        //all2upper(text[i]);
    }

    for (vector<string>::size_type i = 0; i < text.size(); i++) {
        cout << text[i] << " ";
        cnt++;
        if (cnt % 8 == 0) {
            cout << endl;
        }
    }
}
