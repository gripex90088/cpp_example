#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <mutex>
#include <ctime>

using namespace std;

mutex mtx;

void writePid(pid_t pid, string st_time)
{
	mtx.lock();
	fstream fout("process_exec_test", ios_base::out | ios_base::app);
	fout <<"["
		<< st_time
		<< "], [pid:"
		<< pid
		<< "] write data\n";
	fout.flush();
	sleep(3);
	fout << pid << " continue write.\n" << endl;
	fout.flush();
	fout.close();
	mtx.unlock();
}


int main()
{
	int step = 0;

	pid_t pid;
	pid = getpid();

	while(1)
	{
		time_t t = time(0);
		string str_time = asctime(localtime(&t));
		writePid(pid, str_time);
	}

	return 0;
}
