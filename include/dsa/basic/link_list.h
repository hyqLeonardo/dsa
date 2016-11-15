#pragma once
/* 
 * linked list implementation
 */

#include <stdio.h>
#include <stdlib.h>

/* structure of single linked list with head node */
typedef struct LNode {
	void *data;
	struct LNode *next;
} LNode;

void init_l(LNode *head);
void print_l(LNode *head);
void insert_l(LNode *head, void *a);