#include <iostream>
#include <stdlib.h>

using std::cout;
using std::endl;

extern char **environ;

int main()
{
    for (int i = 0; environ[i]; i++) {
        cout << environ[i] << endl;
    }
    return 0;
}
