#include <stdio.h>

#include "queue.h"

/* array based queue */
void init_queue(a_queue *queue)
{
	queue->front = 0;
	queue->rear = 0;
}

int queue_empty(a_queue *queue)
{
	if (queue->front == queue->rear)
		return TRUE;
	else
		return FALSE;
}

int enqueue(a_queue *queue, void *a)
{
	if ((queue->rear+1)%MAXSIZE == queue->front)	/* queue is full */
		return FALSE;
	queue->data[queue->rear] = a;
	queue->rear = (queue->rear+1)%MAXSIZE;
	return TRUE;
}

int dequeue(a_queue *queue, void **x)
{
	if (queue_empty(queue))
		return FALSE;
	*x = queue->data[queue->front];
	queue->front = (queue->front+1)%MAXSIZE;
	return TRUE;	
}

/* link based queue, with header node which does not has data */
void init_lqueue(l_queue *queue)
{
	/* initialize header */
	l_node *header = malloc(sizeof(l_node));
	header->next = NULL;

	/* front and rear are the same, means empty queue */
	queue->front = header;
	queue->rear = header;
}

int lqueue_empty(l_queue *queue)
{
	if (queue->front == queue->rear)
		return TRUE;
	else
		return FALSE;
}

void enlqueue(l_queue *queue, void *a)
{
	/* create new node */
	l_node *node = malloc(sizeof(l_node));
	node->data = a;
	node->next = NULL;

	/* link to rear */
	queue->rear->next = node;
	queue->rear = node;
}

int delqueue(l_queue *queue, void **x)
{
	if (lqueue_empty(queue))
		return FALSE;

	l_node *first = queue->front->next;
	*x = first->data;	/* careful, frist point to l_node */

	queue->front->next = first->next;	/* get rid of original first node */
	if (queue->rear == first) 	/* only has one node */
		queue->rear = queue->front;	/* now queue is empty */
	return TRUE;
}