#include <iostream>
#include <thread>

using namespace std;


// using initialization function create thread
void print1()
{
    cout << "print1_1 线程执行" << endl;
    cout << "print1_2 线程执行" << endl;
    cout << "print1_3 线程执行" << endl;
}

int call_print1()
{
    thread mythread1(print1);
    mythread1.join();

    cout << "主线程执行" << endl;
    
    return 0;
}


// using class object create an thread
class T
{
public:
    int it;
    T(int m_it) :it(m_it)
    {
        cout << "构造函数被执行" << endl;
    }
    
    T(const T &t) :it(t.it) {
        cout << "拷贝构造函数执行" << endl;
    }

    ~T()
    {
        cout << "析构函数被执行" << endl;
    }

    void operator()() {
        cout << "it 值: " << it << endl;
    }
};


int main()
{
    int itm = 8;
    T t(itm);
    thread mythread(t);
    mythread.join();
    cout << "主线程执行" << endl;

    return 0;
}
