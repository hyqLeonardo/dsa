/* 
 * graph header, not 'generic'
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE -1
#define MAX_VERTICES 100	/* max number of vertices graph can hold */
// #define INFOTYPE int

/* 
 * struct of edge node
 */
typedef struct EdgeNode {
	int vertex;	/* vertex this edge point to */
	struct EdgeNode *next;	/* next edge from same vertex node */
	// INFOTYPE info;	/* edge weight */
} EdgeNode;

/*
 * struct of vertex node 
 */
typedef struct VertexNode {
	int data;
	EdgeNode *first;	/* first edge node pointed by this vertex */	
} VertexNode;

/* 
 * struct of adjacent list graph
 */
typedef struct DirGraph {
	VertexNode *vertices[MAX_VERTICES];	/* adjacent list, all vertices */
	int vertex_num;	/* number of vertices contained in graph */
	int edge_num;	/* number of edges contained in graph */
} DirGraph;

void init_graph(DirGraph *graph);
int vertex_index(DirGraph *graph, int v);
int has_edge(DirGraph *graph, int v1, int v2);
int first_neigh(DirGraph *graph, int v);
int next_neigh(DirGraph *graph, int v, int c);
int add_vertex(DirGraph *graph, int v);
int add_edge(DirGraph *graph, int v1, int v2);
