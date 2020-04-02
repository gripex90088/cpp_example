#include <iostream>
#include <strstream>
#include <fstream>
#include <vector>
#include <string>
#include <iosfwd>
#include <sstream>
#include <assert.h>

using namespace std;

int main()
{
    string strs;
    stringstream ims;
    ifstream ifs("./1.png");
    assert(ifs);
    ims << ifs.rdbuf();
    strs = ims.str();
    vector<u_char> uchar_a(strs.begin(), strs.end());
    
    cout << "Hello" << endl;
    return 0;
}

