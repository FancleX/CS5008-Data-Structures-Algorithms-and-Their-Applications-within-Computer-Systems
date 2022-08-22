// Zhicun Chen
// 8/2/2022
//
// Compile this assignment with: gcc -Wall main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"


// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

int main(int argc, const char * argv[]) {

    graph_t * graph = create_graph();

    graph_add_node(graph, 1);
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);
    graph_add_edge(graph, 1, 2);

    printf("in neighbors: %d\n", getNumInNeighbors(graph, 2));
    printf("total nodes: 2==%d\n", graph_num_nodes(graph));

    free_graph(graph);

    return 0;
}
