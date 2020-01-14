#include <iostream>
#include <thread>
#include <string>
#include <mutex>

using namespace std;


mutex mut;

void shared_print(string msg, int id) {
    mut.lock();
    cout << msg << id << endl;
    mut.unlock();
}

void function_1() {
    for (int i = 0; i> -10; i--) {
//        cout << "From t1: " << i << endl;
        shared_print("From t1: ", i);
    }
}

int main() {

    thread t1(function_1);

    for (int i = 0; i < 10; i++) {
//        cout << "From main: " << i << endl;
        shared_print("From main: ", i);
    }

    t1.join();
    return 0;
}