// Modify this file
// compile with: gcc linkedlist.c -o linkedlist
// Zhicun Chen
// 5/27/2022

#include <stdio.h>
#include <stdlib.h> // contains the functions free/malloc

// TODO: Create your node_t type here
typedef struct node{
	int year;
	int wins;
	struct node* next;
} node_t;


// TODO: Write your functions here
// There should be 1.) create_list 2.) print_list 3.) free_list
// You may create as many helper functions as you like.

node_t* create_list() {
	// create nodes
	node_t* year18 = (node_t*) malloc(sizeof(node_t));
	node_t* year17 = (node_t*) malloc(sizeof(node_t));
	node_t* year16 = (node_t*) malloc(sizeof(node_t));
	node_t* year15 = (node_t*) malloc(sizeof(node_t));
	node_t* year14 = (node_t*) malloc(sizeof(node_t));
	// assign data and references
	node_t* nodes[5] = {year18, year17, year16, year15, year14};
	int wins[5] = {108, 93, 93, 78, 71};
	int i;
	for (i = 0; i < 5; i++) {
		nodes[i]->year = 2018 - i;
		nodes[i]->wins = wins[i];
		if (i < 4) {
			nodes[i]->next = nodes[i+1];
		} else {
			nodes[i]->next = NULL;
		}	
	}
	// return the head
	return year18;
}

void print_list(node_t* head) {
	// create a pointer points at head
	node_t* pointer = head;
	// traversal and print
	while (pointer != NULL) {
		printf("%d, %d wins\n", pointer->year, pointer->wins);
		pointer = pointer->next;
	}
}

void free_list(node_t* head) {
	// create apointer points at head
	node_t* pointer = head;
	// loop
	while (pointer != NULL) {
		// pointer skips this node and point at next no NULL one
		pointer = pointer->next;
		// free the current head
		free(head);
		// change the head to be the next node since this one is removed
		head = pointer;
	}
}
		 

int main(){
	// TODO: Implement me!
	// create a list
	node_t* myList = create_list(); 
	//print the list
	print_list(myList);
	//free the list
	free_list(myList);			
	return 0;
}
