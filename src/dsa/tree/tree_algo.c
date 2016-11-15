/*
 * traverse algorithms
 */

#include <stdio.h>
#include <stdlib.h>

/** "bst.h" already included from stack.h, so don't include again. 
	If included, error message : bst.h:6:16: error: redefinition of ‘struct BiTNode’
	To make it easier, just add "#pragma once" in front of every header file !
*/
#include "bst.h"	/* for Binary Search Tree */
#include "tbt.h"	/* for Threaded Binary Tree */
#include "stack.h"	/* for stack based implementation of BST traverse */
#include "queue.h"	/* for traverse tree by layer */

/* traverse using recursion */
void pre_order(BiTree T)
{
	if (T != NULL) {
		visit_bst(T);
		pre_order(T->lchild);
		pre_order(T->rchild);
	}
}

void in_order(BiTree T)
{
	if (T != NULL) {
		in_order(T->lchild);
		visit_bst(T);
		in_order(T->rchild);
	}
}

void post_order(BiTree T)
{
	if (T != NULL) {
		post_order(T->lchild);
		post_order(T->rchild);
		visit_bst(T);
	}
}

/* traverse using stack structure */
void pre_order_2(BiTree T)
{
	/* can initialize a stack first, then create a pointer to that */
	// ArrayStack s;
	// init_stack(&s);
	// ArrayStack *stack = &s;
	/* same as above, initialize, then create pointer */
	// ArrayStack s = { .top = -1 };
	// ArrayStack *stack = &s;
	/* Or, use malloc to allocate a memory size of struct 
	 * where malloc's return value is the pointer to stack struct */
	ArrayStack *stack = malloc(sizeof(ArrayStack));
	init_stack(stack);
	BiTree p = T;

	while (p || !stack_empty(stack)) {
		if (p) {
			push(stack, (void *)p);
			visit_bst(p);
			p = p->lchild;
		}
		else {
			pop(stack, (void *)&p);
			p = p->rchild;
		}
	}
}

void in_order_2(BiTree T)
{
	ArrayStack *stack = malloc(sizeof(ArrayStack));
	init_stack(stack);
	BiTree p = T;	/* traverse pointer */

	while (p || !stack_empty(stack)) {
		if (p) {	/* if node is not NULL */
			push(stack, (void *)p);
			p = p->lchild;
		} else {	/* pop and visit */	
			pop(stack, (void *)&p);
			visit_bst(p);
			p = p->rchild;
		}
	}
}

void post_order_2(BiTree T)
{
	ArrayStack *stack = malloc(sizeof(ArrayStack));
	init_stack(stack);
	BiTree p = T;
	BiTree r = NULL;	/* pointer to check */

	while (p || !stack_empty(stack)) {
		if (p) {
			push(stack, p);
			p = p->lchild;
		}
		else {
			get_top(stack, (void *)&p);	/* if rchild hasn't been visited, don't need to pop */
			if (p->rchild && r != p->rchild) 
				p = p->rchild;	/* next loop will push this into stack */
			else {
				pop(stack, (void *)&p);
				visit_bst(p);
				r = p;
				p = NULL;	
			}
		}
	}
}

/* can give the right output, but will destroy original tree structure */
// void post_order_destory(BiTree T)
// {
// 	ArrayStack *stack = malloc(sizeof(ArrayStack));
// 	init_stack(stack);
// 	BiTree p = T;

// 	while (p || !stack_empty(stack)) {
// 		if (p) {
// 			push(stack, p);
// 			p = p->lchild;
// 		}
// 		else {
// 			pop(stack, &p);
// 			if (p->rchild) {	/* if has right child, push itself and rchild */
// 				push(stack, p);
// 				BiTree temp = p->rchild;
// 				p->rchild = NULL;	/* this destory original tree! */
// 				p = temp;
// 			}
// 			else {
// 				visit_bst(p);
// 				p = NULL;	/* set p to NULL */
// 			}
// 		}
// 	}
// }

/*
 * Threaded Binary Tree in order traverse
 */
void in_order_thread(ThreadTree T)
{
	ThreadNode *p = malloc(sizeof(ThreadNode));
	for (p = first_node(T); p != NULL; p = next_node(p)) {
		visit_thread(p);
	}
}

/* 
 * Binary Search Tree traverse by layer, using array based queue
 */
void a_layer(BiTree T)
{
	ArrayQueue *queue = malloc(sizeof(ArrayQueue));
	init_queue(queue);
	enqueue(queue, (void *)T);
	BiTNode *t;

	while (!queue_empty(queue)) {
		dequeue(queue, (void *)&t);
		visit_bst(t);
		if (t->lchild != NULL)
			enqueue(queue, (void *)t->lchild);
		if (t->rchild != NULL)
			enqueue(queue, (void *)t->rchild);
	}	
}

/* 
 * Binary Search Tree traverse by layer, using link based queue
 */
void l_layer(BiTree T)
{
	LinkQueue *queue = malloc(sizeof(LinkQueue));
	init_lqueue(queue);
	enlqueue(queue, (void *)T);
	BiTNode *t = malloc(sizeof(BiTNode));

	while (!lqueue_empty(queue)) {
		delqueue(queue, (void *)&t);
		visit_bst(t);
		if (t->lchild != NULL)
			enlqueue(queue, (void *)t->lchild);
		if (t->rchild != NULL)
			enlqueue(queue, (void *)t->rchild);
	}	
}

int main(int argc, char *argv[])
{
	/* display info */
	printf("###############################################\n");
	size_t pointer_size = sizeof(void *);
	if (pointer_size == 4)
		printf("32-bit version, pointer size is 4 bytes\n");
	if (pointer_size == 8)
		printf("64-bit version, pointer size is 8 bytes\n");
	printf("###############################################\n\n");

	/* initialize toy trees */
	BiTree root = malloc(sizeof(BiTNode));
	btree_toy(root);

	BiTree root_complete = malloc(sizeof(BiTNode));
	btree_toy_complete(root_complete);

	ThreadTree root_thread = malloc(sizeof(ThreadNode));
	thread_toy(root_thread);

	BiTree bst_root = malloc(sizeof(BiTNode));
	bst_toy(bst_root);

	/* traverse */
	// printf("stack based post order traverse of complete tree\n");
	// post_order_2(root_complete);
	// printf("\n");
	printf("in order traverse of tree using stack\n");
	in_order_2(root);
	printf("\n");
	printf("recursive in order traverse of threaded tree\n");
	in_order_thread(root_thread);
	printf("\n");
	printf("traverse tree by layer, using link based queue\n");
	l_layer(root);
	printf("\n");
	printf("traverse complete tree by layer, using link based queue\n");
	l_layer(root_complete);
	printf("\n");
	printf("traverse BST tree by layer, using array based queue\n");
	a_layer(bst_root);
	printf("\n");
	printf("in order traverse of BST tree\n");
	in_order(bst_root);
	printf("\n");

	return 0;
}
