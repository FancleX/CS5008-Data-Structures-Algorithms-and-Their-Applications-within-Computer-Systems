// =================== Support Code =================
// Stack
//
//
//
// - Implement each of the functions to create a working stack.
// - Do not change any of the function declarations
//   - (i.e. stack_t* create_stack() should not have additional arguments)
// - You should not have any 'printf' statements in your stack functions. 
//   - (You may consider using these printf statements to debug, 
//      but they should be removed from your final version)
// ==================================================
#ifndef MYSTACK_H
#define MYSTACK_H

// Stores the maximum 'depth' of our stack.
// Our implementation enforces a maximum depth of our stack.
// (i.e. capacity cannot exceed MAX_DEPTH for any stack)
# define MAX_DEPTH 32

// Create a node data structure to store data within
// our stack. In our case, we will stores 'integers'
typedef struct node{
	int data;
	struct node* next;
}node_t;

// Create a stack data structure
// Our stack holds a single pointer to a node, which
// is a linked list of nodes.
typedef struct stack{
	int count;		// count keeps track of how many items
				// are in the stack.
	unsigned int capacity;	// Stores the maximum size of our stack
	node_t* head;		// head points to a node on the top of our stack.
}stack_t;

// Creates a stack
// Returns a pointer to a newly created stack.
// The stack should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The stacks fields should also be initialized to default values.
stack_t* create_stack(unsigned int capacity){
	// Modify the body of this function as needed.
	stack_t* myStack = NULL;	
	// TODO: Implement me!!
	// initialize stack
	myStack = (stack_t*)malloc(sizeof(stack_t));
	if (myStack == NULL) {
		return NULL;
	}
	myStack->count = 0;
	myStack->capacity = capacity;
	// empty stack without nodes
	myStack->head = NULL;
	return myStack;
}

// Stack Empty
// Check if the stack is empty
// Returns 1 if true (The stack is completely empty)
// Returns 0 if false (the stack has at least one element enqueued)
int stack_empty(stack_t* s){
	// TODO: Implement me!!
	// empty stack
	if (s->count == 0) {
		return 1;
	}
	return 0;
}

// Stack Full
// Check if the stack is full
// Returns 1 if true (The Stack is completely full, i.e. equal to capacity)
// Returns 0 if false (the Stack has more space available to enqueue items)
int stack_full(stack_t* s){
	// TODO: Implement me!
	// not full
	if (s->count < s->capacity) {
		return 0;
	}
	return 1;
}

// Enqueue a new item
// i.e. push a new item into our data structure
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. if the Stack is full that is an error, but does not crash the program).
int stack_enqueue(stack_t* s, int item){
	// TODO: Implement me!
	if (s != NULL) {
		if (s->count != s->capacity) {
			// create a node for storing this item
			node_t* new_node = (node_t*)malloc(sizeof(node_t));
			new_node->data = item;
			new_node->next = s->head;
			// this node shoud be at top of the stack, so change the head reference to this node
			s->head = new_node;
			// update the count of the stack
			s->count++;
			return 0;
		}
	}
	return -1; // Note: you should have two return statements in this function.
}

// Dequeue an item
// Returns the item at the front of the stack and
// removes an item from the stack.
// Removing from an empty stack should crash the program, call exit(1).
int stack_dequeue(stack_t* s){
	// TODO: Implement me!
	// check empty
	if (s == NULL || s->count == 0) {
		exit(1);
	}
	// pop up the head and return its data
	int result;
	node_t* head_node = s->head;
	result = head_node->data;
	// change pointer of the head
	s->head = head_node->next;
	// free the memory of the removed node
	free(head_node);
	// update the count
	s->count--;
	return result;
}

// Stack Size
// Queries the current size of a stack
// A stack that has not been previously created will crash the program.
// (i.e. A NULL stack cannot return the size)
unsigned int stack_size(stack_t* s){
	// TODO: Implement me!
	if (s == NULL) {
		exit(1);
	}
	return s->count;
}

// Free stack
// Removes a stack and ALL of its elements from memory.
// This should be called before the proram terminates.
void free_stack(stack_t* s){
	// TODO: Implement me!
	if (s == NULL) {
		return;
	}
	// free the linked list of the stack
	node_t* iterator = s->head;
	while (iterator != NULL) {
		// store the reference
		iterator = iterator->next;
		// free current head node
		free(s->head);
		// update the head node
		s->head = iterator;
	}
	// free the stack
	free(s);
}

#endif
