#pragma once
/* 
 * stack implementation, 'generic'
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 50
#define TRUE 1
#define FALSE 0

/*
 * struct definition of array based stack
 */
typedef struct a_stack {
	void *data[MAXSIZE];	/* void pointer can point to any struct type */
	int top;	/* position of top element */
} a_stack;

/* not implemented */
typedef struct l_stack {
	void *data;
	struct l_stack *next;
} l_stack;

void init_stack(a_stack *stack);
int stack_empty(a_stack *stack);
int push(a_stack *stack, void *a);
int pop(a_stack *stack, void **x);
int get_top(a_stack *stack, void **x);
