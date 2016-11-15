#pragma once
/* 
 * queue implementation
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 50
#define TRUE 1
#define FALSE 0

/*
 * struct definition of array based queue
 */
typedef struct ArrayQueue {
	void *data[MAXSIZE];
	int front;	/* position of head element */
	int rear;	/* position of tail element */
} ArrayQueue;


void init_queue(ArrayQueue *queue);
int queue_empty(ArrayQueue *queue);
int enqueue(ArrayQueue *queue, void *a);
int dequeue(ArrayQueue *queue, void **x);

/* 
 * strcut definition of link based queue 
 */
typedef struct LQueueNode {
	void *data;
	struct LQueueNode *next;
} LQueueNode;

typedef struct LinkQueue {
	struct LQueueNode *front;
	struct LQueueNode *rear;
} LinkQueue;

void init_lqueue(LinkQueue *queue);
int lqueue_empty(LinkQueue *queue);
void enlqueue(LinkQueue *queue, void *a);	/* can't fail, no need to reture TRUE/FALSE */
int delqueue(LinkQueue *queue, void **x);
