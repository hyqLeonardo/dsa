#include <stdio.h>

#include "link_list.h"

void init_l(l_node *head) {
	head->data = NULL;
	head->next = NULL;
}

void print_l(l_node *head) {
	while (head->next != NULL) {
		head = head->next;
		printf("-> %d ", head->data);
	}
	printf("\n\n");
}

void insert_l(l_node *head, void *a) {
	while (head->next != NULL) 
		head = head->next;	/* now head is at the end */
	/* create new node */
	l_node *new = (l_node *)malloc(sizeof(l_node));
	new->data = a;
	new->next = NULL;

	head->next = new;	/* append to end */
}
