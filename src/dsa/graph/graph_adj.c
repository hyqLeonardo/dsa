#include <stdio.h>

#include "graph_adj.h"

void init_graph(DirGraph *graph) {
	graph->vertex_num = 0;
	graph->edge_num = 0;
}

void visit_vertex(VertexNode *v) {

	printf("%d ", v->data);
}

void visit_edge(VertexNode *v, EdgeNode *e) {

	printf("(%d -> %d) ", v->data, e->vertex->data);
}

void print_graph_vertex(DirGraph *graph) {

	int i;
	for (i = 0; i < graph->vertex_num; i++)		/* traverse vertex */
		visit_vertex(graph->vertices[i]);
}

void print_graph_edge(DirGraph *graph) {

	int i;
	VertexNode *vertex = NULL;
	for (i = 0; i < graph->vertex_num; i++) {	/* traverse vertex */
		vertex = graph->vertices[i];	
		EdgeNode *edge = vertex->first;
		while (edge) {							/* traverse edge */
			visit_edge(vertex, edge);
			edge = edge->next;	
		} 	
	}
}

/*
 * return value : vertex index in vertices array, -1 if not found 
 */
int vertex_index(DirGraph *graph, int v) {

	int i;
	VertexNode *vertex = NULL;
	/* traverse all vertices */
	for (i = 0; i < graph->vertex_num; i++) {	
		vertex = graph->vertices[i];
		if (vertex->data == v) return i;	/* found, return index */
	}
	return -1;
}

/*
 * return value : 1 if found, -1 if not
 */
int has_edge(DirGraph *graph, int v1, int v2) {

	/* set vertex point to v1 */
	int v1_index = vertex_index(graph, v1);
	if (v1_index == -1) return -1;	/* v does not exist */
	VertexNode *vertex = graph->vertices[v1_index];
	/* find edge */
	EdgeNode *edge = vertex->first;	/* first neighbor */
	while (edge) {
		if (edge->vertex->data == v2)	/* edge (v1, v2) found */
			return TRUE;
		edge = edge->next;
	}
	return -1;
}

/*
 * return value : first neighbor's value if found, -1 if not
 */
int first_neigh(DirGraph *graph, int v) {

	/* set vertex point to v */
	int v_index = vertex_index(graph, v);
	if (v_index == -1) return -1;	/* v does not exist */
	VertexNode *vertex = graph->vertices[v_index];

	if (vertex->first) 	/* has neighbor */
		return vertex->first->vertex->data;	/* return data of frist neighbour */
	return -1;	/* failed */
}

/*
 * return value : next neighbor's data of v if found, -1 if not
 */
int next_neigh(DirGraph *graph, int v, int c) {	/* c means current */
 
	/* set vertex point to v */
	int v_index = vertex_index(graph, v);
	if (v_index == -1) return -1;	/* v does not exist */
	VertexNode *vertex = graph->vertices[v_index];

	if (vertex->first) {	/* found vertex and has neighbor */
		EdgeNode *edge = vertex->first;	/* first neighbor */
		while (edge) {
			if (edge->vertex->data == c && edge->next)	/* c is not last neighbor of vertex */
				return edge->next->vertex->data;
		}
		return -1;
	}
	return -1;	/* failed */
}

/*
 * return new v's index if succeed
 */
int add_vertex(DirGraph *graph, int v) {

	/* create new node */
	VertexNode *node = (VertexNode *)malloc(sizeof(VertexNode));
	node->data = v;
	if (vertex_index(graph, v) != -1)	/* v already exist */
		return -1;
	// Add vertex AND update vertex count, 
	// carful, vertices are NOT indexed by its data
	graph->vertices[graph->vertex_num++] = node; 
	return graph->vertex_num - 1;		/* careful! */
}

int add_edge(DirGraph *graph, int v1, int v2) {

	if (has_edge(graph, v1, v2) != -1)	/* edge (v1, v2) already exists */
		return -1;

	/* add vertex if doesn't exists */
	int v1_index = vertex_index(graph, v1);
	int v2_index = vertex_index(graph, v2);
	if (v1_index == -1) v1_index = add_vertex(graph, v1);
	if (v2_index == -1) v2_index = add_vertex(graph, v2);

	/* create edge v1 -> v2 */
	EdgeNode *edge_v1 = (EdgeNode *)malloc(sizeof(EdgeNode));
	edge_v1->vertex = graph->vertices[v2_index];
	/* set vertex1 point to v1 */
	VertexNode *vertex1 = graph->vertices[v1_index];

	/* add edge (v1, v2) to v1's edge list */
	if (vertex1->first == NULL) {	/* if v1 has no out edge */
		vertex1->first = edge_v1;
		graph->edge_num++;
		return TRUE;	/* done */	
	} else {	/* if v1 has at least 1 out edge */
		EdgeNode *edge = vertex1->first;	
		while (edge->next) edge = edge->next;	/* insert edge node found */
		edge->next = edge_v1;	/* insert */
		graph->edge_num++;
		return TRUE;
	}
	return -1;
}