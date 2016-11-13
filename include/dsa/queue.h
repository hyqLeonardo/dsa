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
typedef struct a_queue {
	void *data[MAXSIZE];
	int front;	/* position of head element */
	int rear;	/* position of tail element */
} a_queue;


void init_queue(a_queue *queue);
int queue_empty(a_queue *queue);
int enqueue(a_queue *queue, void *a);
int dequeue(a_queue *queue, void **x);

/* 
 * strcut definition of link based queue 
 */
typedef struct l_node {
	void *data;
	struct l_node *next;
} l_node;

typedef struct l_queue {
	struct l_node *front;
	struct l_node *rear;
} l_queue;

void init_lqueue(l_queue *queue);
int lqueue_empty(l_queue *queue);
void enlqueue(l_queue *queue, void *a);	/* can't fail, no need to reture TRUE/FALSE */
int delqueue(l_queue *queue, void **x);
