#include <stdio.h>

#include "adj_graph.h"

void init_graph(DirGraph *graph) {
	graph->vertex_num = 0;
	graph->edge_num = 0;
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
		if (vertex->data == v)
			return i;
		vertex = vertex->next;
	}
	return FALSE;
}

/*
 * return value : 1 if found, -1 if not
 */
int has_edge(DirGraph *graph, int v1, int v2) {

	/* set vertex point to v1 */
	int v1_index = vertex_index(graph, v1);
	if (!v1_index) return FALSE;	/* v does not exist */
	VertexNode *vertex = graph->vertices[v1_index];
	/* find edge */
	EdgeNode *edge = vertex->edge_node;
	while (edge) {
		if (edge->vertex == v2)	/* edge (v1, v2) found */
			return TRUE;
		edge = edge->next;
	}
	return FALSE;
}

/*
 * return value : first neighbor's value if found, -1 if not
 */
int first_neigh(DirGraph *graph, int v) {

	/* set vertex point to v */
	int v_index = vertex_index(graph, v1);
	if (!v_index) return FALSE;	/* v does not exist */
	VertexNode *vertex = graph->vertices[v_index];

	if (vertex->edge_node) 	/* has neighbor */
		return vertex->edge_node->vertex;	/* return data of frist neighbour */
	return FALSE;	/* failed */
}

/*
 * return value : next neighbor's value of v if found, -1 if not
 */
int next_neigh(DirGraph *graph, int v, int c) {	/* c means current */
 
	/* set vertex point to v */
	int v_index = vertex_index(graph, v);
	if (!v_index) return FALSE;	/* v does not exist */
	VertexNode *vertex = graph->vertices[v_index];

	if (vertex->edge_node) {	/* found vertex and has neighbor */
		EdgeNode *edge = vertex->edge_node;
		while (edge) {
			if (edge->vertex == c && edge->next)	/* c is not last neighbor of vertex */
				return edge->next->vertex;
		}
		return FALSE;
	}
	return FALSE;	/* failed */
}

/*
 * return new v's index if succeed
 */
int add_vertex(DirGraph *graph, int v) {

	/* create new node */
	VertexNode *node = (VertexNode)malloc(sizeof(VertexNode));
	node->data = v;
	if (vertex_index(graph, v))	/* v already exist */
		return FALSE;
	// Add vertex AND update vertex count, 
	// carful, vertices are NOT indexed by its data
	graph->vertices[graph->vertex_num++] = node; 
	return graph->vertex_num;
}

int add_edge(DirGraph *graph, int v1, int v2) {

	if (has_edge(graph, v1, v2))	/* edge (v1, v2) already exists */
		return FALSE;

	/* add vertex if doesn't exists */
	int v1_index = vertex_index(graph, v1);
	int v2_index = vertex_index(graph, v2);
	if (!v1_index) v1_index = add_vertex(graph, v1);
	if (!v2_index) v2_index = add_vertex(graph, v2);

	/* create edge v1 -> v2 */
	EdgeNode *edge_v1 = (edge_node)malloc(sizeof(edge_node));
	edge_v1->vertex = v2;
	/* set vertex point to v1 */
	VertexNode *vertex = graph->vertices[v1_index];

	/* add edge (v1, v2) to v1's edge list */
	if (vertex->first == NULL) {	/* if v1 has no out edge */
		vertex->first = edge_v1;
		return TRUE;	/* done */	
	} else {	/* if v1 has at least 1 out edge */
		EdgeNode *edge = vertex->first;	
		while (edge->next) edge = edge->next;	/* insert edge node found */
		edge->next = edge_v1;	/* insert */
		graph->edge_num++;
	}
}