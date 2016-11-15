#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "adj_graph.h"

int main(int argc, char *argv[]) {
	/* display info */
	printf("###############################################\n");
	size_t pointer_size = sizeof(void *);
	if (pointer_size == 4)
		printf("32-bit version, pointer size is 4 bytes\n");
	if (pointer_size == 8)
		printf("64-bit version, pointer size is 8 bytes\n");
	printf("###############################################\n\n");

	/* create graph */
	//	 1
	//  / \
	// 0   3 - 4
	//  \ /
	// 	 2
	DirGraph *graph = (DirGraph *)malloc(sizeof(DirGraph));
	init_graph(graph);
	add_edge(graph, 0, 1);
	add_edge(graph, 0, 2);
	add_edge(graph, 1, 3);
	add_edge(graph, 2, 3);
	add_edge(graph, 3, 4);
	/* graph info */
	printf("Vertices : \n");
	print_graph_vertex(graph);
	printf("\n\n");
	printf("Edges : \n");
	print_graph_edge(graph);
	printf("\n\n");
	printf("Totally %d vertices and %d edges.\n", 
		graph->vertex_num, graph->edge_num);

	return 0;
}