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
#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
// Create a graph data structure
typedef struct graph{
    int numNodes;
    int numEdges;
    dll_t* nodes;     //an array of nodes storing all of our nodes.
} graph_t;

typedef struct graph_node{
    int data;
    dll_t* inNeighbors;
    dll_t* outNeighbors;
} graph_node_t;

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
// Returns NULL if we cannot allocate memory.
graph_t* create_graph(){
    // Modify the body of this function as needed.
    graph_t* myGraph= malloc(sizeof(graph_t));
    if (myGraph == NULL) {
        return NULL;
    }
    myGraph->nodes = create_dll();
    if (myGraph->nodes == NULL) {
        return NULL;
    }
    myGraph->numEdges = 0;
    myGraph->numNodes = 0;
    return myGraph;
}

// Returns the node pointer if the node exists.
// Returns NULL if the node doesn't exist or the graph is NULL
graph_node_t* find_node( graph_t * g, int value){
    // if graph is null or dll is empty
    if (g == NULL || g->nodes->count == 0) {
        return NULL;
    }
    // get head pt
    node_t* iterator = g->nodes->head;
    // traversal from head to the tail
    while (iterator != NULL) {
        // cast the graph node
        graph_node_t* node = (graph_node_t*) iterator->data;
        if (node->data == value) {
            return node;
        }
        iterator = iterator->next;
    }
    return NULL;
}

// Creates a graph node
// Note: This relies on your dll implementation.
graph_node_t * create_graph_node(int value){
    graph_node_t * graph_node = malloc(sizeof(graph_node_t));
    
    if ( graph_node == NULL ) return NULL;
    
    graph_node->data = value;
    graph_node->inNeighbors = create_dll();
    graph_node->outNeighbors = create_dll();
    
    return graph_node;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node already exists )
// Returns -1 if the graph is NULL.
int graph_add_node(graph_t* g, int value){
    if ( g == NULL ) return -1;
    
    if (find_node(g, value) != NULL) return -1;
    
    graph_node_t * newNode = create_graph_node(value);
    if ( newNode == NULL ) return -1;
    
    assert(g->nodes);
    dll_push_back(g->nodes, newNode);
    g->numNodes++;
    
    return 1;
}

// Returns dll_t* of all the in neighbors of this node.
// Returns NULL if the node doesn't exist or if the graph is NULL.
dll_t* getInNeighbors( graph_t * g, int value ){
    if (g == NULL) {
        return NULL;
    }
    graph_node_t * res = find_node(g, value);
    return res == NULL ? NULL : res->inNeighbors;
}

// Returns dll_t* of all the out neighbors of this node.
// Returns NULL if the node doesn't exist or if the graph is NULL.
dll_t* getOutNeighbors( graph_t * g, int value ){
    if (g == NULL) {
        return NULL;
    }
    graph_node_t * res = find_node(g, value);
    return res == NULL ? NULL : res->outNeighbors;
}


// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist )
// Returns -1 if the graph is NULL.
int contains_edge( graph_t * g, int source, int destination){
    if (g == NULL) {
        return -1;
    }
    // check if the src and des do exist
    graph_node_t * src = find_node(g, source);
    graph_node_t * des = find_node(g, destination);
    if (src == NULL || des == NULL) {
        return 0;
    }
    // get out neighbors of src
    dll_t * src_out = src->outNeighbors;
    // get in neighbors of des
    dll_t * des_in = des->inNeighbors;
    // check if the edge exists
    if (!isContain(src_out, des) || !isContain(des_in, src)) {
        return 0;
    }
    return 1;
}


// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge doesn't exists )
// Returns -1 if the graph is NULL.
int graph_remove_edge(graph_t * g, int source, int destination){
    //The function removes an edge from source to destination but not the other way.
    //Make sure you remove destination from the out neighbors of source.
    //Make sure you remove source from the in neighbors of destination.
    if (g == NULL) {
        return -1;
    }
    // check if the src and des do exist
    graph_node_t * src = find_node(g, source);
    graph_node_t * des = find_node(g, destination);
    if (src == NULL || des == NULL) {
        return 0;
    }
    // check if the edge exists
    if (contains_edge(g, source, destination) != 1) {
        return 0;
    }
    // get out neighbors of src
    dll_t * src_out = getOutNeighbors(g, source);
    // get in neighbors of des
    dll_t * des_in = getInNeighbors(g, destination);
    // get the index of the node in the dll
    // the destination index in the src_out dll
    int src_index = getIndex(src_out, des);
    // the source index in the des_in dll
    int des_index = getIndex(des_in, src);
    // update in and out neighbors
    dll_remove(src_out, src_index);
    dll_remove(des_in, des_index);
    // update the edges of the graph
    g->numEdges--;
    return 1;
}


// Returns 1 on success
// Returns 0 on failure ( or if the node doesn't exist )
// Returns -1 if the graph is NULL.
int graph_remove_node(graph_t* g, int value){
    // The function removes the node from the graph along with any edges associated with it.
    // That is, this node would have to be removed from all the in and out neighbor's lists that contain it.
    if (g == NULL) {
        return -1;
    }
    // get in
    dll_t * in = getInNeighbors(g, value);
    // get out
    dll_t * out = getOutNeighbors(g, value);
    // if the node doesn't exist
    if (in == NULL || out == NULL) {
        return 0;
    }
    // copy the in and out neighbors to new dlls
    // because nodes will be removed during the iteration
    // to avoid pt missing
    dll_t * in_copy = replicate(in);
    dll_t * out_copy = replicate(out);

    // remove out neighbors of the value, those links will be
    // the node of the value -> destination nodes
    node_t * iterator = out_copy->head;
    while (iterator != NULL) {
        graph_node_t * des = (graph_node_t*) iterator->data;
        graph_remove_edge(g, value, des->data);
        iterator = iterator->next;
    }
    // remove in neighbors of the value, those links will be
    // destination nodes -> the node of the value
    iterator = in_copy->head;
    while (iterator != NULL) {
        graph_node_t * src = (graph_node_t*) iterator->data;
        graph_remove_edge(g, src->data, value);
        iterator = iterator->next;
    }
    // free the node and its relevant resources
    free_dll(in);
    free_dll(out);
    free_dll(in_copy);
    free_dll(out_copy);
    // get the graph node
    graph_node_t * g_node = (graph_node_t*) find_node(g, value);
    // remove the node from the graph nodes list
    int index = getIndex(g->nodes, g_node);
    // free the graph node
    free(g_node);
    // remove the node from graph nodes list
    dll_remove(g->nodes, index);
    g->numNodes--;
    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge already exists )
// Returns -1 if the graph is NULL.
int graph_add_edge(graph_t * g, int source, int destination){
    // The function adds an edge from source to destination but not the other way.
    // Make sure you are not adding the same edge multiple times.
    // Make sure you modify the in and out neighbors appropriately. destination will be an out neighbor of source.
    // Source will be an in neighbor of destination.
    if (g == NULL) {
        return -1;
    }
    // check if the src and des do exist
    graph_node_t * src = find_node(g, source);
    graph_node_t * des = find_node(g, destination);
    if (src == NULL || des == NULL) {
        return 0;
    }
    // check if the edge exists
    if (contains_edge(g, source, destination) == 1) {
        return 0;
    }
    // get out neighbors of src
    dll_t * src_out = getOutNeighbors(g, source);
    // get in neighbors of des
    dll_t * des_in = getInNeighbors(g, destination);
    // update in and out neighbors
    if (dll_push_back(src_out, des) != 1) {
        return 0;
    }
    if (dll_push_back(des_in, src) != 1) {
        return 0;
    }
    // update edges
    g->numEdges++;
    return 1;
}

// Returns the number of in neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumInNeighbors( graph_t * g, int value){
    if (g == NULL) {
        return -1;
    }
    // get in dll
    dll_t * in = getInNeighbors(g, value);
    if (in == NULL) {
        return -1;
    }
    return in->count;
}

// Returns the number of out neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumOutNeighbors( graph_t * g, int value){
    if (g == NULL) {
        return -1;
    }
    // get out dll
    dll_t * out = getOutNeighbors(g, value);
    if (out == NULL) {
        return -1;
    }
    return out->count;
}

// Returns the number of nodes in the graph
// Returns -1 if the graph is NULL.
int graph_num_nodes(graph_t* g){
    if (g == NULL) {
        return -1;
    }
    return g->numNodes;
}

// Returns the number of edges in the graph,
// Returns -1 on if the graph is NULL
int graph_num_edges(graph_t* g){
    if (g == NULL) {
        return -1;
    }
    return g->numEdges;
}

// Print the graph with in and out neighbors
void printGraph(graph_t* g) {
    dll_t * nodes = g->nodes;
    node_t * i = nodes->head;
    while (i != NULL) {
        graph_node_t * g_node = i->data;
        printf("vertex: %d\n", g_node->data);
        dll_t * in = g_node->inNeighbors;
        dll_t * out = g_node->outNeighbors;
        node_t * g_in = in->head;
        node_t * g_out = out->head;
        printf("links in: ");
        while (g_in != NULL) {
            graph_node_t * gin = g_in->data;
            printf("%d ", gin->data);
            g_in = g_in->next;
        }
        printf("\nlinks out: ");
        while (g_out != NULL) {
            graph_node_t * gout = g_out->data;
            printf("%d ", gout->data);
            g_out = g_out->next;
        }
        printf("\n");
        i = i->next;
    }
    printf("\n");
}

// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the program terminates.
// Make sure you free all the dll's too.
void free_graph(graph_t* g){
    if (g == NULL) {
        exit(1);
    }
    // get dll of all nodes
    dll_t * allNodes = g->nodes;
    // traversal to free all in and out neighbors of each node
    node_t * iterator = allNodes->head;
    while (iterator != NULL) {
        // mark current node
        node_t * current_node = iterator;
        graph_node_t * current_g_node = (graph_node_t*) current_node->data;
        // move pointer to the next node
        iterator = iterator->next;
        // remove the node
        graph_remove_node(g, current_g_node->data);
    }
    // free the graph dll
    free_dll(g->nodes);
    // free graph
    free(g);
}

// returns 1 if we can reach the destination from source
// returns 0 if it is not reachable
// returns -1 if the graph is NULL (using BFS)
int graph_is_reachable(graph_t * g, int source, int dest){
    if (g == NULL) {
        return -1;
    }
    // if source or dest node don't exist
    if (find_node(g, source) == NULL || find_node(g, dest) == NULL) {
        return -1;
    }
    // create a dll and use it as a queue to save a node if its adjacent list haven't been visited
    dll_t * queue = create_dll();
    // create a dll to store visited nodes
    dll_t * visited = create_dll();
    // get the source node out neighbors
    graph_node_t * g_node = find_node(g, source);
    dll_t * out = g_node->outNeighbors;

    // BFS
    graph_node_t * head = (graph_node_t*) out->head->data;
    // check if the source node have neighbors
    // if not return -1 because the source node doesn't have any neighbors
    if (head == NULL) {
        free_dll(queue);
        free_dll(visited);
        return 0;
    }

    // mark the node visited
    dll_push_back(visited, head->data);
    // add the node to the queue to visit its adjacent list
    dll_push_back(queue, head->data);

    while (!dll_empty(queue)) {
        // check if the destination appeared in the visited node list means from source -> dest is reachable
        if (isContain(visited, dest)) {
            // free memory
            free_dll(queue);
            free_dll(visited);
            return 1;
        }

        // retrieve head from the queue
        int current_node = dll_pop_front(queue);
        // add the neighbors of the current node to the queue
        dll_t * out = getOutNeighbors(g, current_node);
        node_t * iterator = out->head;
        while (iterator != NULL) {
            // get the graph node data
            graph_node_t * iterated_node = (graph_node_t*) iterator->data;
            // add it to the queue if it is unvisited
            if (!isContain(visited, iterated_node->data)) {
                // mark it visited
                dll_push_back(visited, iterated_node->data);
                // add the node to the queue to visit its adjacent list
                dll_push_back(queue, iterated_node->data);
            }
            iterator = iterator->next;
        }

    }
    // free memory
    free_dll(queue);
    free_dll(visited);
    return 0;
}

// a dfs helper function to detect if a cycle start from the given vertex
// returns 1 if there is a cycle in the graph from the vertex
// returns 0 if no cycles exist in the graph from the vertex
int isCycle(graph_t* g, int vertex, dll_t* visited, dll_t* recStack) {
    // if the node links to itself
    if (isContain(recStack, vertex)) {
        return 1;
    }
    // if the node has been visited
    if (isContain(visited, vertex)) {
        return 0;
    }

    // mark the node in the recursion stack
    dll_push_back(recStack, vertex);
    // mark the start node visited
    dll_push_back(visited, vertex);

    // get its adjacent list
    graph_node_t * g_node = find_node(g, vertex);
    dll_t * out = g_node->outNeighbors;
    node_t * iterator = out->head;
    while (iterator != NULL) {
        // get the graph node
        graph_node_t * current_node = (graph_node_t*) iterator->data;
        // if a cycle found
        if (isCycle(g, current_node->data, visited, recStack)) {
            return 1;
        }
        iterator = iterator->next;
    }
    // if not cycle found, remove the node from the recursion stack
    dll_pop_back(recStack);
    return 0;
}

// returns 1 if there is a cycle in the graph
// returns 0 if no cycles exist in the graph
// returns -1 if the graph is NULL
// You may use either BFS or DFS to complete this task.
int graph_has_cycle(graph_t * g){
    if (g == NULL) {
        return -1;
    }
    // no nodes in the graph
    if (g->numNodes == 0) {
        return 0;
    }
    // DFS for every node in the graph
    dll_t * nodes = g->nodes;
    node_t * iterator = nodes->head;
    while (iterator != NULL) {
        // create dlls to store nodes' information
        dll_t * visited = create_dll();
        dll_t * recStack= create_dll();
        // get the graph node
        graph_node_t * g_node = (graph_node_t*) iterator->data;
        // DFS starting from each node
        if (isCycle(g, g_node->data, visited, recStack)) {
            // clear dlls
            free_dll(visited);
            free_dll(recStack);
            return 1;
        }
        // clear dlls
        free_dll(visited);
        free_dll(recStack);
        iterator = iterator->next;
    }
    return 0;
}

void print_path_helper(graph_t* g, int src, int des, dll_t* visited, dll_t* path) {
    // if the path matched then print
    if (src == des) {
        node_t * iterator = path->head;
        while (iterator != NULL) {
            if (iterator->next == NULL) {
                printf("%d", iterator->data);
            } else {
                printf("%d -> ", iterator->data);
            }
            iterator = iterator->next;
        }
        printf("\n");
        return;
    }
    // mark current node
    dll_push_back(visited, src);
    // recursive for the node's adjacent list
    dll_t * out = getOutNeighbors(g, src);
    node_t * it = out->head;
    while (it != NULL) {
        graph_node_t * current_node = (graph_node_t*) it->data;
        if (!isContain(visited, current_node->data)) {
            // store current node in path
            dll_push_back(path, current_node->data);
            // go deeper from the current node
            print_path_helper(g, current_node->data, des, visited, path);
            // remove current node in path
            // if the path matched, it should already be printed out
            dll_pop_back(path);
        }
        it = it->next;
    }
    // unmark current node for next round
    dll_pop_back(visited);
}


// prints any path from source to destination if there
// exists a path from the source to the destination.
// Note: Consider using one of the other functions to help you
//       determine if a path exists first
// (Choose either BFS or DFS, typically DFS is much simpler)
//
// Returns 1 if there is a path from source to destination
// Returns 0 if there is not a path from a source to destination
// Returns -1 if the graph is NULL
int graph_print_path(graph_t * g, int source, int dest){
    if (g == NULL) {
        return -1;
    }
    if (!graph_is_reachable(g, source, dest)) {
        return 0;
    }
    // store path from source -> dest
    dll_t * path = create_dll();
    dll_t * visited = create_dll();

    dll_push_back(path, source);
    print_path_helper(g, source, dest, visited, path);

    // free memory
    free_dll(path);
    free_dll(visited);
    return 1;
}

#endif
