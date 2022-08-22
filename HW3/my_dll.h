// =================== Support Code =================
// Doubly Linked List ( DLL ).
//
//
//
// - Implement each of the functions to create a working DLL.
// - Do not change any of the function declarations
//   - (i.e. dll_t* create_dll() should not have additional arguments)
// - You should not have any 'printf' statements in your DLL functions. 
//   - (You may consider using these printf statements to debug,
//     but they should be removed from your final version)
//   - (You may write helper functions to help you debug your code such as print_list etc)
// ==================================================
#ifndef MYDLL_H
#define MYDLL_H

// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node {
	int data;
	struct node* next;
  	struct node* previous;
} node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL {
	int count;		// count keeps track of how many items are in the DLL.
	node_t* head;		// head points to the first node in our DLL.
    node_t * tail;          //tail points to the last node in our DLL.
} dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t* create_dll(){
	// Modify the body of this function as needed.
	dll_t* myDLL= NULL;	

	// TODO: Implement me!!
	// allocate memory for the dll
	myDLL = (dll_t*) malloc(sizeof(dll_t));
	if (myDLL == NULL) {
		return NULL;
	}
	// initialize value
	myDLL->count = 0;
	myDLL->head = NULL;
	myDLL->tail = NULL;
	return myDLL;
}

// DLL Empty
// Check if the DLL is empty
// Returns -1 if the dll is NULL.
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t* l){
	// TODO: Implement me!!
	// if null
	if (l == NULL) {
		return -1;
	}
	// if completely empty
	if (l->count == 0) {
		return 1;
	}
	return 0;
}

// push a new item to the front of the DLL ( before the first node in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t* l, int item){
	// TODO: Implement me!!
	// check if dll is null
	if (l == NULL) {
		return -1;
	}
	// allocate memory to store the item in a node
	node_t* newNode = (node_t*) malloc(sizeof(node_t));
	// check failure
	if (newNode == NULL) {
		return 0;
	}
	// assign value
	newNode->data = item;
	// check if the current head is null, if yes, the dll is empty and this will be the first node in the list
	if (l->head == NULL) {
		// change the previous pointer of the node to null
		newNode->previous = NULL;
		// change the next pointer of the node to the null
		newNode->next = NULL;
		// change the head pointer to this node
		l->head = newNode;
		// change the tail pointer to this node
		l->tail = newNode;
		// increase the size
		l->count++;
		return 1;
	}
	// otherwise
	// get current head node
	node_t* currentHead = l->head;
	// change new node next pointer to point at the head node
	newNode->next = currentHead;
	// change the current head node previous pointer to point at the new node
	currentHead->previous = newNode;
	// change the new node previous pointer to point at the null
	newNode->previous = NULL;
	// change the head pointer of the dll to point at the new node
	l->head = newNode;
	// increase the count of the dll
	l->count++;
	return 1;
}

// push a new item to the end of the DLL (after the last node in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* l, int item){
	// TODO: Implement me!!
	// check if the dll is null
	if (l == NULL) {
		return -1;
	}
	// allocate memory to store the item in a new node
	node_t* newNode = (node_t*) malloc(sizeof(node_t));
	// check failure
	if (newNode == NULL) {
		return 0;
	}
	// assign the value
	newNode->data = item;
	// check if the current tail is null, if yes, the dll is empty and this will be the first node in the list
	if (l->tail == NULL) {
		// change the previous pointer of the node to null
		newNode->previous = NULL;
		// change the next pointer of the node to the null
		newNode->next = NULL;
		// change the head pointer to this node
		l->head = newNode;
		// change the tail pointer to this node
		l->tail = newNode;
		// increase the size
		l->count++;
		return 1;
	}
	// otherwise
	// get current tail node
	node_t* currentTail = l->tail;
	// change the current tail next pointer to point at the new node
	currentTail->next = newNode;
	// change the new node previous pointer to point at the current tail node
	newNode->previous = currentTail;
	// change the new node next pointer to point at null
	newNode->next = NULL;
	// change the tail pointer of the dll to point at the new node
	l->tail = newNode;
	// increase the count of the dll
	l->count++;
	return 1;
}

// Returns the first item in the DLL and also removes it from the list.
// Returns -1 if the DLL is NULL. 
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
int dll_pop_front(dll_t* t){
	// TODO: Implement me!!
	//check if the dll is null
	if (t == NULL) {
		return -1;
	}
	// if count == 0, there is nothing to pop
	if (t->count == 0) {
		return 0;
	}
	// get current head node
	node_t* currentHead = t->head;
	// store the item value
	int data = currentHead->data;
	// check if this is only one node in the dll
	if (t->count == 1) {
		// change the head and tail pointer to null
		t->head = NULL;
		t->tail = NULL;
		// free the node
		free(currentHead);
		// decrease count
		t->count--;
		// return value
		return data;
	}
	// otherwise
	// change the head pointer of the dll to point the next node
	t->head = currentHead->next;
	// change the updated head node previous pointer to point at null
	t->head->previous = NULL;
	// free the popped node
	free(currentHead);
	// decrease the count of the dll
	t->count--;
	// return the value
	return data;
}

// Returns the last item in the DLL, and also removes it from the list.
// Returns a -1 if the DLL is NULL. 
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
int dll_pop_back(dll_t* t){
	// TODO: Implement me!!
	//check if the dll is null
	if (t == NULL) {
		return -1;
	}
	// if count == 0, there is nothing to pop
	if (t->count == 0) {
		return 0;
	}
	// get current tail node
	node_t* currentTail = t->tail;
	// store the item value
	int data = currentTail->data;
	// check if this is only one node in the dll
	if (t->count == 1) {
		// change the head and tail pointer to null
		t->head = NULL;
		t->tail = NULL;
		// free the node
		free(currentTail);
		// decrease count
		t->count--;
		// return value
		return data;
	}
	// otherwise
	// change the tail pointer of the dll to point the previous node
	t->tail = currentTail->previous;
	// change the updated tail node next pointer to point at null
	t->tail->next = NULL;
	// free the popped node
	free(currentTail);
	// decrease the count of the dll
	t->count--;
	// return the value
	return data;
}

// A helper function is to get the pointer at target position.
node_t* ptAtTarget(dll_t* l, int pos) {
	// create a pointer and a counter to find the position from head
	node_t* index = l->head;
	int counter = 0;
	// traversal to find the position
	while (counter < pos) {
		index = index->next;
		counter++;
	}
	// return the pointer
	return index;
}

// Inserts a new node before the node at the specified position.
// Returns -1 if the list is NULL
// Returns 1 on success
// Retruns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
int dll_insert(dll_t* l, int pos, int item){
	// TODO: Implement me!!
	// check if the ddl is null
	if (l == NULL) {
		return -1;
	}
	// check failures
	// check negative position and the postion is greater than current size
	if (pos < 0 || pos > l->count) {
		return 0;
	}
	// check if insert at head
	if (pos == 0) {
		// call push_front
		int result = dll_push_front(l, item);
		return result;
	}
	// check if insert at the size
	if (l->count == pos) {
		// call push_back
		int result = dll_push_back(l, item);
		return result;
	}
	// insert at the pos is neither head nor tail
	// allocate memory for the new node
	node_t* newNode = (node_t*) malloc(sizeof(node_t));
	// check if null
	if (newNode == NULL) {
		return 0;
	}
	// assign value to the node
	newNode->data = item;
	// get the node pointer at the position
	node_t* index = ptAtTarget(l, pos);
	// change the node and the previous node reference
	node_t* pre = index->previous;
	// join the new node between the previous node and the index node
	// change the reference of the pre node
	pre->next = newNode;
	// change reference of the index node
	index->previous = newNode;
	// change the reference of the new node
	newNode->previous = pre;
	newNode->next = index;
	// increase the size of the dll
	l->count++;
	// return
	return 1;
}

// Returns the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the list is NULL
//  (does not remove the item)
// Returns 0 on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Assume no negative numbers in the list or the number zero.
int dll_get(dll_t* l, int pos){
	// TODO: Implement me!!
	// check null
	if (l == NULL) {
		return -1;
	}
	// check failures
	// position is negative or greater than the last index of the dll
	if (pos < 0 || pos > l->count - 1) {
		return 0;
	}
	// get the pointer at the position
	node_t* index = ptAtTarget(l, pos);
	// get the data of the node
	int data = index->data;
	// return data
	return data;
}

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the list is NULL
// Returns 0 on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Assume no negative numbers in the list or the number zero.
int dll_remove(dll_t* l, int pos){
	// TODO: Implement me!!
	// check null
	if (l == NULL) {
		return -1;
	}
	// check failures
	// position is negative or greater than the last index of the dll
	if (pos < 0 || pos > l->count - 1) {
		return 0;
	}
	// if remove head
	if (pos == 0) {
		// call pop_front
		int result = dll_pop_front(l);
		return result;
	}
	// if remove tail
	if (pos == l->count - 1) {
		// call pop_back
		int result = dll_pop_back(l);
		return result;
	}
	// remove anywhere else
	// get the pointer at the position
	node_t* index = ptAtTarget(l, pos);
	// get data of the node
	int data = index->data;
	// get the previous node and the next node of the node
	node_t* pre = index->previous;
	node_t* next = index->next;
	// change the previous node reference
	pre->next = next;
	// change the next node reference
	next->previous = pre;
	// free the node
	free(index);
	// decrease the size
	l->count--;
	// return the value
	return data;
}

// DLL Size
// Returns -1 if the DLL is NULL.
// Queries the current size of a DLL
int dll_size(dll_t* t){
	// TODO: Implement me!!
	// check null
	if (t == NULL) {
		return -1;
	}
	return t->count;
}

// Free DLL
// Removes a DLL and all of its elements from memory.
// This should be called before the proram terminates.
void free_dll(dll_t* t){
	// TODO: Implement me!!
	// create an iterator
	node_t* iterator = t->head;
	// traversal the dll
	while(iterator != NULL) {
		iterator = iterator->next;
		// free current head
		free(t->head);
		// change head reference
		t->head = iterator;
	}
	// free dll
	free(t);
}



#endif
