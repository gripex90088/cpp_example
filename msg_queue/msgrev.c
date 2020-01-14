#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <sys/msg.h>
#include <stdio.h>

struct msg_st
{
	long int msg_type;
	char text[BUFSIZ];
};

void main()
{
	int running = 1;
	int msgid = -1;
	struct msg_st data;
	long int msgtype = 90088;

	// establish message queue
	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	if (msgid == -1) {
		printf("msgget fail.\n");
		exit(EXIT_FAILURE);
	}

	FILE *file;
	file = fopen("process_singal_communication_test", "a+");

	while(running) {
		if (msgrcv(msgid, (void *)&data, BUFSIZ, msgtype, 0) == -1) {
			puts("msgrcv fail.\n");
			exit(EXIT_FAILURE);
		}

		printf("rev data msg_type is %ld \n.", data.msg_type);
		printf("content is %s\n", data.text);

		fprintf(file, "rev data msg_type is %ld\n content is %s\n", data.msg_type, data.text);
		fflush(file);
		if (strncmp(data.text, "end", 3) == 0)
			running = 0;
	}

	// delete message from queue
	if (msgctl(msgid, IPC_RMID, 0) == -1) {
		fprintf(stderr, "msgctl(IPC_RMID) fail.\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
	fclose(file);
}
