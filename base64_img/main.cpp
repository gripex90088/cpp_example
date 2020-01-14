#include <string>
#include <iostream>
#include "Base64.h"
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{

    fstream f;
    f.open("test.jpeg", ios::in | ios::binary);
    if (false == f.good()) {
    	cout << "file open failed" << endl;
    	exit(EXIT_FAILURE);
    }

    f.seekg(0, std::ios_base::end);
    std::streampos sp = f.tellg();
    int size = sp;
    char* buffer = (char*)malloc(sizeof(char)*size);
    f.read(buffer,size);

    cout << "file size:" << size << endl;
    string imgBase64 = base64_encode(buffer, size);
    cout << "img base64 encode size:" << imgBase64.size() << endl;

//    cout << imgBase64 << endl;
    string imgdecode64 = base64_decode(imgBase64);
    cout << "img decode size:" << imgdecode64.size() << endl;

    ofstream fout("a.jpeg", ios_base::out | ios_base::binary);
    fout << imgdecode64;

    return 0;
}

