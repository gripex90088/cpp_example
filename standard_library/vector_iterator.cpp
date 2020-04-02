#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v(10, 8);

    // begin()返回一个迭代器，　指向第一个元素
    vector<int>::iterator iter = v.begin();

    *iter = 9; // 迭代器实际是一个指针

    iter++;

    for (vector<int>::size_type i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }

    cout << "iterator print" << endl;
    // end(超出末端迭代器) 指向最后一个元素的下一个，　　
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }
    return 0;
}

