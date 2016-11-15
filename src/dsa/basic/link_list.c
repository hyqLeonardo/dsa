#include <stdio.h>

#include "link_list.h"

void init_l(LNode *head) {
	head->data = NULL;
	head->next = NULL;
}

void print_l(LNode *head) {
	while (head->next != NULL) {
		head = head->next;
		printf("-> %d ", head->data);
	}
	printf("\n\n");
}

void insert_l(LNode *head, void *a) {
	while (head->next != NULL) 
		head = head->next;	/* now head is at the end */
	/* create new node */
	LNode *new = (LNode *)malloc(sizeof(LNode));
	new->data = a;
	new->next = NULL;

	head->next = new;	/* append to end */
}
