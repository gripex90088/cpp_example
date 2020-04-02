#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>

int main()
{
    std::cout << "Hello world" << std::endl;
 
    char filepath[50];
    std::ofstream of("./test_write_aaa.txt");

    // 
    if (daemon(1, 0) < 0) {
        perror("error daemon\n");
        exit(1);
    } 

    //chdir("/home/debian/Cprojects/daemon");
    if (getcwd(filepath, 50) == NULL) {
        perror("error getcwd");
        exit(1);
    }

    of << filepath << std::endl;
    std::cout << filepath << std::endl;
    
  //  while(true) {
  //      std::cout << 11111 << std::endl;
  //      sleep(1);
  //  }

    of.close(); 
    return 0;
}

