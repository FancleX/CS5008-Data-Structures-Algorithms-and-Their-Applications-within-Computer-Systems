// Zhicun Chen
// 7/17/2022 
//
// Include our header file for our my_bst.c
#include "my_bst.h"

// Include any other libraries needed
#include <stdio.h>
#include <stdlib.h>

// Creates a BST
// Returns a pointer to a newly created BST.
// The BST should be initialized with data on the heap.
// The BST fields should also be initialized to default values(i.e. size=0).
bst_t* bst_create(){
    // Modify the body of this function as needed.
    bst_t* myBST= NULL; 
    myBST = (bst_t*) malloc(sizeof(bst_t));
    // if successfully allocate memory
    // initialize fields
    if (myBST != NULL) {
        myBST->root = NULL;
        myBST->size = 0;
    }
    return myBST;
}

// BST Empty
// Check if the BST is empty
// Returns 1 if true (The BST is completely empty)
// Returns 0 if false (the BST has at least one element)
int bst_empty(bst_t* t){
    // if the input tree is null
    if (t == NULL) {
        exit(1);
    }
    return t->size == 0;
}


// help to recursively visist nodes in the tree and add nodes
void helperAdd(bstnode_t* root, bstnode_t* node) {
    if (node->data <= root->data) {
        if (root->leftChild == NULL) {
            // add the new node here
            root->leftChild = node;
            return;
        }
        // traversal left
        helperAdd(root->leftChild, node);
    } else {
        if (root->rightChild == NULL) {
            root->rightChild = node;
            return;
        }
        // traversal right
        helperAdd(root->rightChild, node);
    }
}

// Adds a new node containng item to the BST
// The item is added in the correct position in the BST.
//  - If the data is less than or equal to the current node we traverse left
//  - otherwise we traverse right.
// The bst_function returns '1' upon success
//  - bst_add should increment the 'size' of our BST.
// Returns a -1 if the operation fails.
//      (i.e. the memory allocation for a new node failed).
// Your implementation should should run in O(log(n)) time.
//  - A recursive imlementation is suggested.
int bst_add(bst_t* t, int item){
    // if the tree is null
    if (t == NULL) {
        exit(1);
    }
    // create a new node for the item
    bstnode_t* node = NULL;
    node = (bstnode_t*) malloc(sizeof(bstnode_t));
    if (node == NULL) {
        return -1;
    }
    // initialize
    node->data = item;
    node->leftChild = NULL;
    node->rightChild = NULL;
    
    // if the first node in the tree
    if (t->root == NULL) {
        t->root = node;
    } else {
        // add somewhere else
        helperAdd(t->root, node);
    }
    t->size++;
    return 1;
}

// help to print recursively
void helperPrint(bstnode_t* root, int order) {
    // perform inorder dfs
    // ascending print
    if (order == 0) {
        if (root != NULL) {
            helperPrint(root->leftChild, order);
            printf("%d ", root->data);
            helperPrint(root->rightChild, order);
        }
    } else {
        // descending order
        if (root != NULL) {
            helperPrint(root->rightChild, order);
            printf("%d ", root->data);
            helperPrint(root->leftChild, order);
        }
    }
}

// Prints the tree in ascending order if order = 0, otherwise prints in descending order.
// A BST that is NULL should print "(NULL)"
// It should run in O(n) time.
void bst_print(bst_t *t, int order){
    if(NULL == t){
        printf("(NULL)");
    }else{
        // call helper
        helperPrint(t->root, order);
    }
}

// help to calculate the sum of all nodes
int helperSum(bstnode_t* root) {
    // count the sum
    int count = 0;
    if (root != NULL) {
        // collect result of the left subtree
        count += helperSum(root->leftChild);
        // collect result of the right subtree
        count += helperSum(root->rightChild);
        // add the current node data
        count += root->data;
    } 
    return count;
}

// Returns the sum of all the nodes in the bst. 
// A BST that is NULL exits the program.
// It should run in O(n) time.
int bst_sum(bst_t *t){
  if (t == NULL) {
    exit(1);
  }
  return helperSum(t->root);
}

// help to find a value in the tree
int helperFind(bstnode_t* root, int value) {
    // intialize a result to determine how many nodes have the value
    int result = 0;
    if (root != NULL) {
        // if found
        if (root->data == value) {
            return 1;
        } else if (value < root->data) {
            // traversal left
            result += helperFind(root->leftChild, value);
        } else {
            // traversal right
            result += helperFind(root->rightChild, value);
        }
    }
    return result;
}

// Returns 1 if value is found in the tree, 0 otherwise. 
// For NULL tree -- exit the program. 
// It should run in O(log(n)) time.
int bst_find(bst_t * t, int value){
    if (t == NULL) {
        exit(1);
    }
    // if more than one value found in the tree return 1, otherwise 0
    return helperFind(t->root, value) != 0;
}

// Returns the size of the BST
// A BST that is NULL exits the program.
// (i.e. A NULL BST cannot return the size)
unsigned int bst_size(bst_t* t){
    if (t == NULL) {
        exit(1);
    }
    return t->size;
}

// help to free the nodes of the tree
void helperFree(bstnode_t* root) {
    // postorder free
    if (root != NULL) {
        helperFree(root->leftChild);
        helperFree(root->rightChild);
        free(root);
    }
}

// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the proram terminates.
void bst_free(bst_t* t){
    // free nodes
    helperFree(t->root);
    // free the tree
    free(t);
}


