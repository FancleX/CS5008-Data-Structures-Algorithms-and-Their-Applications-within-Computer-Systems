// Zhicun Chen
// 6/6/2022
// Homework Assignment 3
//
// Compile this assignment with: gcc -g -Wall main.c -o main
// Use this file to implement testing for your
// doubly linked list implementation
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_dll.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

// test insert
int unitTest1(int status){
    int passed = 0;
    dll_t* test = create_dll();
    dll_push_front(test,123);
    dll_push_back(test,456);
    dll_insert(test, 1, 678);
    if(3==dll_size(test)){
       passed = 1;
    }else{
    	passed = 0;
    }
    free_dll(test);

    return passed;
}

// test get
int unitTest2(int status){
    int passed = 0;
    dll_t* test = create_dll();
    dll_push_front(test,123);
    dll_push_back(test,456);
    dll_insert(test, 1, 678);
    if(3==dll_size(test) && dll_get(test, 1) == 678){
       passed = 1;
    }else{
    	passed = 0;
    }
    free_dll(test);

    return passed;
}


// test remove
int unitTest3(int status){
    int passed = 0;
    dll_t* test = create_dll();
    dll_push_front(test,123);
    dll_push_back(test,456);
    dll_insert(test, 1, 678);
    dll_remove(test, 1);
    if(2==dll_size(test) && dll_get(test, 1) == 456){
       passed = 1;
    }else{
    	passed = 0;
    }
    free_dll(test);

    return passed;
}

// test empty
int unitTest4(int status){
    int passed = 0;
    dll_t* test = create_dll();
    dll_push_front(test,123);
    dll_push_back(test,456);
    dll_remove(test, 0);
    dll_remove(test, 0);
    // expect empty
    if(dll_empty(test) == 1){
       passed = 1;
    }else{
    	passed = 0;
    }
    free_dll(test);

    return passed;
}

// test push front twice and push back once, then pop and remove
int unitTest5(int status){
    int passed = 0;
    dll_t* test = create_dll();
    dll_push_front(test,123);
    dll_push_front(test,456);
    dll_push_back(test,789);
    dll_remove(test, 0);
    dll_pop_back(test);
    dll_pop_front(test);
    // expect empty
    if(dll_empty(test) == 1){
       passed = 1;
    }else{
    	passed = 0;
    }
    free_dll(test);

    return passed;
}

// An array of function pointers to all of the tests
// that main() can use iterate over them.
int (*unitTests[])(int)={
    unitTest1,
    unitTest2,
    unitTest3,
    unitTest4,
    unitTest5,
    NULL
};

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){   
 	// TODO: Implement unit tests for testing 
 	// your doubly linked list implementation

    unsigned int testsPassed = 0;
    // List of Unit Tests to test your data structure
    int counter =0;
    while(unitTests[counter]!=NULL){
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
