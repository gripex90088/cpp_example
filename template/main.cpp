#include <iostream>

template <class T>
inline const T& max(const T& a, const T& b)
{
    return a < b ? b : a;
}

int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

