#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int fps = 600;
    int current_fps = 300;
    float rate;
    rate = ((float)current_fps / (float)fps) * 100;
    cout <<  rate << endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}