#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef int Elementype;

typedef struct Node {
	Elementype Element;
	struct Node *next;
} NODE, *PNODE;

typedef struct QNode {
	PNODE front, Rear;
} Queue, PQueue;



void InitQueue() {};
#endif
