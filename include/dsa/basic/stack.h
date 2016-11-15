#pragma once
/* 
 * stack header, 'generic'
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 50
#define TRUE 1
#define FALSE 0

/*
 * struct definition of array based stack
 */
typedef struct ArrayStack {
	void *data[MAXSIZE];	/* void pointer can point to any struct type */
	int top;	/* position of top element */
} ArrayStack;

/* not implemented */
typedef struct LinkStack {
	void *data;
	struct l_stack *next;
} l_stack;

void init_stack(ArrayStack *stack);
int stack_empty(ArrayStack *stack);
int push(ArrayStack *stack, void *a);
int pop(ArrayStack *stack, void **x);
int get_top(ArrayStack *stack, void **x);
