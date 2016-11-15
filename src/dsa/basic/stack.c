#include <stdio.h>

#include "stack.h"

void init_stack(ArrayStack *stack) {
	stack->top = -1;
}

int stack_empty(ArrayStack *stack) {
	return stack->top == -1 ? TRUE : FALSE;
}

int push(ArrayStack *stack, void *a) {
	if (stack->top == MAXSIZE-1)	/* stack is full */
		return FALSE;
	stack->data[++stack->top] = a;
	return TRUE; 
}

int pop(ArrayStack *stack, void **x) {
	if (stack->top == -1)
		return FALSE;
	*x = stack->data[stack->top--];
	return TRUE;		
}

int get_top(ArrayStack *stack, void **x) {
	if (stack->top == -1)
		return FALSE;
	*x = stack->data[stack->top];
	return TRUE;
}
