#include <stdio.h>

#include "queue.h"

/* array based queue */
void init_queue(ArrayQueue *queue) {
	queue->front = 0;
	queue->rear = 0;
}

int queue_empty(ArrayQueue *queue) {
	if (queue->front == queue->rear)
		return TRUE;
	else
		return FALSE;
}

int enqueue(ArrayQueue *queue, void *a) {
	if ((queue->rear+1)%MAXSIZE == queue->front)	/* queue is full */
		return FALSE;
	queue->data[queue->rear] = a;
	queue->rear = (queue->rear+1)%MAXSIZE;
	return TRUE;
}

int dequeue(ArrayQueue *queue, void **x) {
	if (queue_empty(queue))
		return FALSE;
	*x = queue->data[queue->front];
	queue->front = (queue->front+1)%MAXSIZE;
	return TRUE;	
}

/* link based queue, with header node which does not has data */
void init_lqueue(LinkQueue *queue) {
	/* initialize header */
	LQueueNode *header = malloc(sizeof(LQueueNode));
	header->next = NULL;

	/* front and rear are the same, means empty queue */
	queue->front = header;
	queue->rear = header;
}

int lqueue_empty(LinkQueue *queue) {
	if (queue->front == queue->rear)
		return TRUE;
	else
		return FALSE;
}

void enlqueue(LinkQueue *queue, void *a) {
	/* create new node */
	LQueueNode *node = malloc(sizeof(LQueueNode));
	node->data = a;
	node->next = NULL;

	/* link to rear */
	queue->rear->next = node;
	queue->rear = node;
}

int delqueue(LinkQueue *queue, void **x) {
	if (lqueue_empty(queue))
		return FALSE;

	LQueueNode *first = queue->front->next;
	*x = first->data;	/* careful, frist point to LQueueNode */

	queue->front->next = first->next;	/* get rid of original first node */
	if (queue->rear == first) 	/* only has one node */
		queue->rear = queue->front;	/* now queue is empty */
	return TRUE;
}