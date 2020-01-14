#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include "base64.h"

int main()
{

    std::ifstream in("./a.png");
    std::ostringstream tmp;
    tmp << in.rdbuf();
    std::cout << tmp.str().length() << std::endl;
    base64_encrypt_text(tmp.str().c_str(), tmp.str().length() + 1);
    
    in.close();
    return 0;
}

