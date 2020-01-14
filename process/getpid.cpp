#include <iostream>
#include <fstream> // file I/O
#include <unistd.h>


void getPid()
{
	using std::ofstream;
	using std::cout;
	pid_t getpid(void); // get process id
	pid_t  getppid(void); // get parent process id

	/*
	 *if parent pid exit
	 *then pid after call ppid return 1
	 */
	ofstream fout("./_pid", std::ios_base::out | std::ios_base::app);
	fout << "_pid is " << getpid();
	fout << "_ppid is " << getppid();
	fout.close();
}
