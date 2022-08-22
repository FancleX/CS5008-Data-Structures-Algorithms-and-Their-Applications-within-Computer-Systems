// =================== Support Code =================
// Graph.
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they 
//      should be removed from your final version)
// ==================================================
#ifndef MYSHORTEST_H
#define MYSHORTEST_H

#include <stdlib.h>
#include <assert.h>
#include <limits.h>

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"
#include "my_pq.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.


// returns 1 if Dijkstra's algorithm completes successfully
// returns 0 if Dijkstra's algorithm does not complete successfully
// NOTE: Recall from our discussion, Dijkstra's algorithm does not
//       handle negative weight edges
// returns -1 if the graph is NULL
int calculate_shortest_path(graph_t * g, int source) {
	if (g == NULL) {
        return -1;
    }
    // get the source node
    graph_node_t * src = find_node(g, source);
    // if the node doesn't exist
    if (src == NULL) {
        return -1;
    }
    // create a queue
    queue_t * pq = create_queue(g->numNodes);
    if (pq == NULL) {
        return -1;
    }

    // get vertex of the graph
    dll_t * nodes = g->nodes;
    node_t * iterator = nodes->head;
    // update the cost and from
    while (iterator != NULL) {
        graph_node_t * g_node = (graph_node_t*) iterator->data;
        g_node->cost = INT_MAX;
        g_node->from = INT_MAX;
        // enqueue
        queue_enqueue(pq, g_node);
        iterator = iterator->next;
    }
    // update the source node
    src->cost = 0;

    // if the queue is not empty
    while (!queue_empty(pq)) {
        // get min cost node
        graph_node_t * u = queue_dequeue(pq);
        // get out neighbors
        dll_t * out = u->outNeighbors;
        iterator = out->head;
        while (iterator != NULL) {
            // get the vertex u cost and weight from the vertex u to its neighbors v
            graph_edge_t * v_edge = (graph_edge_t*) iterator->data;
            int weight = v_edge->cost;
            // if negative weight
            if (weight < 0) {
                return 0;
            }
            int alt = u->cost + weight;
            if (alt < v_edge->cost) {
                // update v cost
                graph_node_t * v_node = find_node(g, v_edge->to);
                v_node->cost = alt;
                v_node->from = u->data;
            }
            iterator = iterator->next;
        }
    }
    // mark source
    g->source = source;
    free_queue(pq);
    return 1;
}

// prints the shortest path from source to destination if there
// exists a path from the source to the destination. Consider
// how you can solve this recursively if you want to avoid using
// another data structure.
//
// Returns 1 if there is a path from source to destination
// Returns 0 if there is not a path from source to destination
// Returns -1 if the graph is NULL
// Returns -2 if called before `calculate_shortest_path` is called
// Note: consider the bookkeeping fields in `graph_t` struct to
//       determine whether this is true or not
int print_shortest_path(graph_t * g, int source, int dest) {
	if (g == NULL) {
        return -1;
    }
    // no shortest path data
    if (g->source == -1) {
        return -2;
    }
    // if no source or des
    // or reach bound
    graph_node_t * src = find_node(g, source);
    graph_node_t * des = find_node(g, dest);
    if (!src || !des || g->source != source) {
      	if (dest == INT_MAX) {
       	    printf("%d ", source);
	}
        return 0;
    }
	
    if (des->from != source) {
 	  print_shortest_path(g, source, des->from);
  	  printf("%d ", dest);
    }

	return 1;
}

#endif
