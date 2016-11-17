#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "graph_adj.h"

void graph_bfs(DirGraph *graph, int start, int *result) {	/* start is the data in start vertex */

	int i = 0;	/* next result array index to put in */
	int v_num = graph->vertex_num;	
	int visited[v_num];	/* indexed by graph->vertices[index] */
	// v_num is NOT a compile time constant, manually initialize, 
	// array initialized with all -1
	memset(visited, FALSE, v_num*sizeof(int));	
	LinkQueue *queue = (LinkQueue *)malloc(sizeof(LinkQueue));
	init_lqueue(queue);
	/* enqueue start vertex */
	int start_index = vertex_index(graph, start);
	enlqueue(queue, (void *)graph->vertices[start_index]);

	VertexNode *vertex = (VertexNode *)malloc(sizeof(VertexNode));
	while (!lqueue_empty(queue)) {	/* traverse from start vertex */
		delqueue(queue, (void *)&vertex);
		int v_index = vertex_index(graph, vertex->data);
		EdgeNode *edge = vertex->first;
		/* add all neighbors of vertex in queue */
		while (edge) {
			int neigh_index = vertex_index(graph, edge->vertex->data);	
			enlqueue(queue, (void *)graph->vertices[neigh_index]);
			edge = edge->next;
		}
		/* visit vertex */
		if (!visited[v_index]) {
			visited[v_index] = TRUE;
			visit_vertex(vertex, 0);
			result[i++] = vertex->data;
		}
	}
}

void graph_dfs_recur(DirGraph *graph, int start, int *result, int *visited) {

	int v_index = vertex_index(graph, start);
	VertexNode *vertex = graph->vertices[v_index];
	visit_vertex(vertex, 0);
	visited[v_index] = TRUE;
	int i = 0;
	while (result[i] != -1)	i++;	/* get index for result, -1 is initial value */
	result[i] = vertex->data;

	EdgeNode *edge = vertex->first;
	while (edge) {	/* traverse all neighbors */
		if (visited[vertex_index(graph, edge->vertex->data)]) break;
		graph_dfs_recur(graph, edge->vertex->data, result, visited);
		edge = edge->next;
	}
}

void graph_dfs(DirGraph *graph, int start, int *result) {

	int v_num = graph->vertex_num;	
	int visited[v_num];	/* indexed by graph->vertices[index] */
	memset(visited, FALSE, v_num*sizeof(int));	/* v_num is NOT a compile time constant, manually initialize */

	graph_dfs_recur(graph, start, result, visited);
}

