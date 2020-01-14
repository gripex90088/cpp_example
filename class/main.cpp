#include <iostream>
#include <unistd.h>


using namespace std;

class Test 
{
public:
    Test() {
        cout << "Hello " << endl;        
    }
    ~Test() {
        cout << "destruct " << endl;
    }

    void echo() {
        cout << "echo" << endl;
    }
private:

};


int main()
{
    std::cout << "Hello world" << std::endl;
    
    Test test;
    test.echo();

    sleep(11);

    return 0;
}

