#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

#define MAX_TEXT 512

struct msg_st
{
	long int msg_type;
	char text[MAX_TEXT];
};

void main()
{

	int running = 1;
	struct msg_st data;

	char buffer[BUFSIZ]; // stdio.h

}

void main_struct()
{
	int running	= 1;
	struct msg_st data;

	char buffer[BUFSIZ];
	int msgid = 1;

	// establish message queue
	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	if (msgid == -1) {
		puts("msgget fail\n");
		exit(EXIT_FAILURE);
	}

	//write message to message queue, until end
	while(running) {
		// output data
		puts("input data:");
		fgets(buffer, BUFSIZ, stdin);
		data.msg_type = 90088;
		strcpy(data.text, buffer);

		// send message to message queue
		if (msgsnd(msgid, (void *)&data, MAX_TEXT, 0) == -1) {
			puts("send msg fail\n");
			exit(EXIT_FAILURE);
		}

		// input end stop
		if (strncmp(buffer, "end", 3) == 0) {
			running = 0;
		}
//		sleep(1);
	}

	puts("exit success");
	exit(EXIT_SUCCESS);

}



