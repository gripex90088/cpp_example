#include <iostream>
#include <ctime>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> // thread
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>


using namespace std;

void use_spdlog();
void execSystemCommend();

int main() {

	return 0;
}

void execSystemCommend()
{
	string cmd = "pstree >> pstree_";
	int i = system(cmd.c_str());
	if (i)
	{
		cout << "system(" << cmd << ")" << " failed.\n"<< endl;
	}
}

void use_spdlog()
{
	cout << getenv("ERROR_LOG_PATh")<<endl;

	try{
		auto async_file = spdlog::basic_logger_mt<spdlog::async_factory>("Error", "/home/xuxing/projects/linux_one_cpp/src/error.log");
	    for (int i = 1; i < 101; ++i)
		{
	    	async_file->info("Request format error #{}", "{\"ID\":\"10001\",\"name\":\"Zhang San\"}");
		}
	}
	catch (const spdlog::spdlog_ex& ex)
	{
		cout << "Log initialization failed: " << ex.what() << endl;
	}
}
