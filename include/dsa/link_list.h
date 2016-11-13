#pragma once
/* 
 * linked list implementation
 */

#include <stdio.h>
#include <stdlib.h>

/* structure of single linked list with head node */
typedef struct l_node {
	void *data;
	struct l_node *next;
} l_node;

void init_l(l_node *head);
void print_l(l_node *head);
void insert_l(l_node *head, void *a);