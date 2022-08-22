// Zhicun Chen
// 8/13/2022
//
// Compile this assignment with: gcc -Wall test.c -o tests
//
// This is a great assignment to practice debugging.
// First compile with debugging symbols
// Compile with: gcc -Wall -g test.c -o tests
// Run with: gdb ./tests --tui
// Then type 'start'
// Then type 'next' or 'n' and enter
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

// You may add as many unit tests as you like here
// A few have been provided for your convenience.
// We will use our own test suite (i.e. replacing this file)
// in order to test your implementation from my_bst.

// Testing allocation
int unitTest1(){
    int result;
    graph_t * testGraph = create_graph();
    if (testGraph!=NULL){
        result = 1;
    }else{
        result = 0;
    }
    free_graph(testGraph);
    return result;
}

// Add and find a node
int unitTest2(){
    int result;
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 1);
    graph_node_t * node = find_node(testGraph, 1);
    if (node->data == 1) {
        result = 1;
    } else {
        result = 0;
    }
    free_graph(testGraph);
    return result;
}

// Add duplicate nodes
int unitTest3(){
    int result;
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    if (testGraph->numNodes == 2) {
        result = 1;
    } else {
        result = 0;
    }
    free_graph(testGraph);
    return result;
}

// add edges to node
int unitTest4(){
    int result;
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    graph_add_edge(testGraph, 1, 2);
    graph_add_edge(testGraph, 1, 3);
    if (testGraph->numEdges == 2) {
        result = 1;
    } else {
        result = 0;
    }
    free_graph(testGraph);
    return result;
}

// add edges and test in and out neighbors of the node
int unitTest5(){
    int result;
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    graph_add_edge(testGraph, 1, 2);
    graph_add_edge(testGraph, 1, 3);
    graph_add_edge(testGraph, 2, 3);
    graph_add_edge(testGraph, 2, 1);

    if (getNumOutNeighbors(testGraph, 1) == 2 && getNumInNeighbors(testGraph, 2) == 1 &&
            getNumOutNeighbors(testGraph, 2) == 2 && getNumInNeighbors(testGraph, 3) == 2) {
        result = 1;
    } else {
        result = 0;
    }
    free_graph(testGraph);
    return result;
}

// remove edges
int unitTest6(){
    int result;
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    graph_add_edge(testGraph, 1, 2);
    graph_add_edge(testGraph, 1, 3);

    graph_remove_edge(testGraph, 1, 2);

    if (getNumOutNeighbors(testGraph, 1) == 1 && getNumInNeighbors(testGraph, 2) == 0 && getNumInNeighbors(testGraph, 3) == 1 && testGraph->numEdges == 1) {
        result = 1;
    } else {
        result = 0;
    }
    free_graph(testGraph);
    return result;
}

// remove bi-directed edges
int unitTest7(){
    int result;
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_edge(testGraph, 1, 2);
    graph_add_edge(testGraph, 2, 1);
    graph_remove_edge(testGraph, 1, 2);
    graph_remove_edge(testGraph, 2, 1);

    if (getNumOutNeighbors(testGraph, 1) == 0 && getNumInNeighbors(testGraph, 2) == 0 && testGraph->numEdges == 0) {
        result = 1;
    } else {
        result = 0;
    }
    free_graph(testGraph);
    return result;
}

// remove nodes
int unitTest8(){
    int result;
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    graph_add_edge(testGraph, 1, 2);
    graph_add_edge(testGraph, 2, 1);
    graph_add_edge(testGraph, 2, 3);

    graph_remove_node(testGraph, 2);

    if (testGraph->numNodes == 2 && find_node(testGraph, 2) == NULL && getNumInNeighbors(testGraph, 1) == 0 && getNumOutNeighbors(testGraph, 1) == 0
        && getNumInNeighbors(testGraph, 3) == 0) {
        result = 1;
    } else {
        result = 0;
    }
    free_graph(testGraph);
    return result;
}

// remove nodes and test the number of edges and nodes
int unitTest9(){
    int result;
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    graph_add_node(testGraph, 4);
    graph_add_edge(testGraph, 1, 2);
    graph_add_edge(testGraph, 2, 1);
    graph_add_edge(testGraph, 1, 3);
    graph_add_edge(testGraph, 3, 2);
    graph_add_edge(testGraph, 3, 4);

    graph_remove_node(testGraph, 1);
    graph_remove_node(testGraph, 2);

    if (graph_num_nodes(testGraph) == 2 && graph_num_edges(testGraph) == 1 && getNumOutNeighbors(testGraph, 3) == 1) {
        result = 1;
    } else {
        result = 0;
    }
    free_graph(testGraph);
    return result;
}


// test print
int unitTest10(){
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    graph_add_node(testGraph, 4);
    graph_add_edge(testGraph, 1, 1);
    graph_add_edge(testGraph, 1, 2);
    graph_add_edge(testGraph, 2, 4);
    graph_add_edge(testGraph, 3, 1);

    printGraph(testGraph);
    graph_remove_edge(testGraph, 1, 1);
    printGraph(testGraph);
    free_graph(testGraph);
    return 1;
}

// test graph_is_reachable
int unitTest11(){
    /*
     * 1->1, 2
     * 2->4
     * test 1->4 reachable
     * 1->3 unreachable
     */
    int result;
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    graph_add_node(testGraph, 4);
    graph_add_edge(testGraph, 1, 1);
    graph_add_edge(testGraph, 1, 2);
    graph_add_edge(testGraph, 2, 4);


    if (graph_is_reachable(testGraph, 1, 4) && !graph_is_reachable(testGraph, 1, 3)) {
        result = 1;
    } else {
        result = 0;
    }
    free_graph(testGraph);
    return result;
}

// test graph_has_cycle
int unitTest12(){
    /*
     * cycle
     * case1: 1->1, 2
     * case2: 2->1, 3
     *
     * no cycle
     * case3: 3->4
     */
    int result = 0;
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    graph_add_node(testGraph, 4);
    graph_add_edge(testGraph, 1, 1);
    graph_add_edge(testGraph, 1, 2);
    if (graph_has_cycle(testGraph)) {
        result++;
    } else {
        result--;
    }
    // remove the cycle
    graph_remove_edge(testGraph, 1, 1);

    graph_add_edge(testGraph, 2, 1);
    graph_add_edge(testGraph, 2, 3);
    if (graph_has_cycle(testGraph)) {
        result++;
    } else {
        result--;
    }
    // remove the cycle
    graph_remove_edge(testGraph, 2, 1);

    graph_add_edge(testGraph, 3, 4);
    if (!graph_has_cycle(testGraph)) {
        result++;
    } else {
        result--;
    }

    free_graph(testGraph);
    return result == 3;
}

// test graph_print_path
int unitTest13(){
    /*
     * no path
     * 1->4
     *
     * path
     * 1->3
     * 1->2->3
     * 1->2->4->3
     *
     */
    int result = 0;
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    graph_add_node(testGraph, 4);
    graph_add_edge(testGraph, 1, 2);
    if (!graph_print_path(testGraph, 1, 4)) {
        result++;
    } else {
        result--;
    }

    // add path
    graph_add_edge(testGraph, 1, 3);
    graph_add_edge(testGraph, 1, 2);
    graph_add_edge(testGraph, 2, 3);
    graph_add_edge(testGraph, 2, 4);
    graph_add_edge(testGraph, 4, 3);

    if (graph_print_path(testGraph, 1, 3)) {
        result++;
    } else {
        result--;
    }
    free_graph(testGraph);
    return result == 2;
}

// TODO: Add more tests here at your discretion
int (*unitTests[])(int) = {
        unitTest1,
        unitTest2,
        unitTest3,
        unitTest4,
        unitTest5,
        unitTest6,
        unitTest7,
        unitTest8,
        unitTest9,
        unitTest10,
        unitTest11,
        unitTest12,
        unitTest13,
        NULL
};

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){

    unsigned int testsPassed = 0;
    // List of Unit Tests to test your data structure
    int counter =0;
    while(unitTests[counter] != NULL){
        printf("========unitTest %d========\n",counter);
        if(1==unitTests[counter](1)){
            printf("passed test\n");
            testsPassed++;
        }else{
            printf("failed test, missing functionality, or incorrect test\n");
        }
        counter++;
    }

    printf("%d of %d tests passed\n",testsPassed,counter);

    return 0;
}
