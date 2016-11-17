#include <stdio.h>
#include <stdlib.h>

#include "graph_adj.h"

void graph_bfs(DirGraph *graph, int start, int *result);
void graph_dfs_recur(DirGraph *graph, int start, int *result);
void graph_dfs(DirGraph *graph, int start, int *result);