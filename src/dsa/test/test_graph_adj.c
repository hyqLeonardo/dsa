#include <stdio.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "graph_adj.h"

static void graph_init_test(void);
static void graph_build_test(void);

static void graph_init_test(void) {

	DirGraph *graph = (DirGraph *)malloc(sizeof(DirGraph));
	init_graph(graph);
	CU_ASSERT(graph->vertex_num == 0);
	CU_ASSERT(graph->edge_num == 0);

	free(graph);
}

static void graph_build_test(void) {

	DirGraph *graph = (DirGraph *)malloc(sizeof(DirGraph));
	init_graph(graph);
	/* no vertex or edge */
	CU_ASSERT(vertex_index(graph, 0) == -1);
	CU_ASSERT(has_edge(graph, 0, 1) == -1);
	add_vertex(graph, 0);
	/* vertex 0 is at index 0 */
	CU_ASSERT(vertex_index(graph, 0) == 0);
	add_edge(graph, 0, 1);
	/* vertex 1 added by add_edge, has index 1 */
	CU_ASSERT(vertex_index(graph, 1) == 1);
	CU_ASSERT(has_edge(graph, 0, 1) == 1);

	add_edge(graph, 0, 2);
	add_edge(graph, 1, 3);
	add_edge(graph, 2, 3);
	add_edge(graph, 3, 4);
	/* totally 5 vertices and 5 edges now */
	CU_ASSERT(graph->vertex_num == 5);
	CU_ASSERT(graph->edge_num == 5);

	free(graph);
}

int main(int argc, char *argv[]) {

	/* display info */
	printf("###############################################\n");
	size_t pointer_size = sizeof(void *);
	if (pointer_size == 4)
		printf("32-bit version, pointer size is 4 bytes\n");
	if (pointer_size == 8)
		printf("64-bit version, pointer size is 8 bytes\n");
	printf("###############################################\n\n");

	CU_pSuite suite_graph_adj;
    CU_initialize_registry();
    suite_graph_adj = CU_add_suite("graph_adj", NULL, NULL);
    /* add tests */
    CU_add_test(suite_graph_adj, "graph_init_test", graph_init_test);
    CU_add_test(suite_graph_adj, "graph_build_test", graph_build_test);
   	/* run all tests */ 
    CU_basic_run_tests();
    CU_cleanup_registry();

	return 0;
}