#include <stdio.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "queue.h"
#include "graph_adj.h"
#include "graph_algo.h"

/* helper functions */
static int int_cmp(int *a, int *b, int a_len, int b_len);
static void graph_example1(DirGraph *graph);
static void graph_example2(DirGraph *graph);
/* test functions */
static void graph_bfs_test1(void);
static void graph_dfs_test1(void);
static void graph_bfs_test2(void);
static void graph_dfs_test2(void);

/* helper functions */
static int int_cmp(int *a, int *b, int a_len, int b_len) {

	if (a_len != b_len) return FALSE;

	int i;
	for (i = 0; i < b_len; i++) {
		if (a[i] != b[i]) return FALSE;
	}
	return TRUE;
}

/**
   1
  / \
 0   3 - 4
  \ /
   2
*/
static void graph_example1(DirGraph *graph) {

	init_graph(graph);
	add_edge(graph, 0, 1);
	add_edge(graph, 0, 2);
	add_edge(graph, 1, 3);
	add_edge(graph, 2, 3);
	add_edge(graph, 3, 4);
}

static void graph_example2(DirGraph *graph) {

	init_graph(graph);
	add_edge(graph, 0, 1);
	add_edge(graph, 0, 2);
	add_edge(graph, 1, 2);
	add_edge(graph, 1, 3);
	add_edge(graph, 2, 3);
	add_edge(graph, 2, 5);
	add_edge(graph, 3, 4);
	add_edge(graph, 7, 6);
}

/* test functions */
static void graph_bfs_test1(void) {

	DirGraph *graph = (DirGraph *)malloc(sizeof(DirGraph));
	graph_example1(graph);

	/* start vertex 0 */
	int result1[graph->vertex_num];
	memset(result1, -1, (graph->vertex_num)*sizeof(int));	
	int correct1[5] = { 0, 1, 2, 3, 4 };
	graph_bfs(graph, 0, result1);
	CU_ASSERT(int_cmp(result1, correct1, graph->vertex_num, 5));
	/* start vertex 2 */
	int result2[graph->vertex_num];
	memset(result2, -1, (graph->vertex_num)*sizeof(int));
	int correct2[5] = { 2, 3, 4, -1, -1 };
	graph_bfs(graph, 2, result2);
	CU_ASSERT(int_cmp(result2, correct2, graph->vertex_num, 5));	

	free(graph);
}

static void graph_dfs_test1(void) {

	DirGraph *graph = (DirGraph *)malloc(sizeof(DirGraph));
	graph_example1(graph);

	/* start vertex 0 */
	int result1[graph->vertex_num];
	memset(result1, -1, (graph->vertex_num)*sizeof(int));	
	int correct1[5] = { 0, 1, 3, 4, 2 };
	graph_dfs(graph, 0, result1);
	CU_ASSERT(int_cmp(result1, correct1, graph->vertex_num, 5));
	/* start vertex 2 */
	int result2[graph->vertex_num];
	memset(result2, -1, (graph->vertex_num)*sizeof(int));
	int correct2[5] = { 2, 3, 4, -1, -1 };
	graph_dfs(graph, 2, result2);
	CU_ASSERT(int_cmp(result2, correct2, graph->vertex_num, 5));	

	free(graph);
}

static void graph_bfs_test2(void) {

	DirGraph *graph = (DirGraph *)malloc(sizeof(DirGraph));
	graph_example2(graph);

	/* start vertex 0 */
	int result1[graph->vertex_num];
	memset(result1, -1, (graph->vertex_num)*sizeof(int));	
	int correct1[8] = { 0, 1, 2, 3, 5, 4, -1, -1};
	graph_bfs(graph, 0, result1);
	CU_ASSERT(int_cmp(result1, correct1, graph->vertex_num, 8));

	free(graph);
}

static void graph_dfs_test2(void) {

	DirGraph *graph = (DirGraph *)malloc(sizeof(DirGraph));
	graph_example2(graph);

	/* start vertex 0 */
	int result1[graph->vertex_num];
	memset(result1, -1, (graph->vertex_num)*sizeof(int));	
	int correct1[8] = { 0, 1, 2, 3, 4, 5, -1, -1 };
	graph_dfs(graph, 0, result1);
	CU_ASSERT(int_cmp(result1, correct1, graph->vertex_num, 8));

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

	CU_pSuite suite_graph_algo;
    CU_initialize_registry();
    suite_graph_algo = CU_add_suite("graph_algo", NULL, NULL);
    /* add tests */
    CU_add_test(suite_graph_algo, "graph_bfs_test1", graph_bfs_test1);
    CU_add_test(suite_graph_algo, "graph_dfs_test1", graph_dfs_test1);
    CU_add_test(suite_graph_algo, "graph_bfs_test2", graph_bfs_test2);
    CU_add_test(suite_graph_algo, "graph_dfs_test2", graph_dfs_test2);
   	/* run all tests */ 
    CU_basic_run_tests();
    CU_cleanup_registry();

	return 0;
}