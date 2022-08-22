// Task: Implement the divide-and-conquer algorithm 
// for calculating mixed-up-ness score

// =================== Libraries ==================
#include <stdio.h> // Include file for standard input/output


// =============== Helper Functions ===============
// TODO: Implement your helper functions here
// merge process and count the score of current subarrays
int merge(int array[], int l, int mid, int r) {
  int count = 0;
  // first subarray start index
  int first = l;
  // second subarray start index
  int second = mid + 1;
  // comparison
  // thoughts: choose the first subarray as target, 
  // then compare the value of the first subarray with the second subarray,
  // if the element of the first subarray is greater than the second, then increase counter
  // during the comparison, every time, we fix one element of the first subarray,
  // and compare it with the all elements of the second subarray.
  // we do need to check the second subarray boundary, if it reach boundary, we have to reset it to the beginning
  // then iterate the next element of the first subarray.
  // note: we don't actually sort the array because we have to guarantee the integrity of the original array, 
  // therefore, we only make the comparison instead of changing the order of the elements.
  while (first <= mid) {
    if (array[first] > array[second]) {
      count++;
    }
    if (second == r) {
        second = mid + 1;
        first++;
    } else {
      second++;
    }
  }
  return count;
}


// mergesort helper
int mergesort(int array[], int l, int r) {
  // global counter
  int count = 0;
  if (r > l) {
    // find the mid
    // prevent integer overflow
    int mid = l + (r - l) / 2;
    // call stack left
    // collect the count value from the last left child
    count += mergesort(array, l, mid);
    // call stack right
    // collect the count value from the last right child
    count += mergesort(array, mid + 1, r);
    // merge and sort
    // count value of the this level
    count += merge(array, l, mid, r);
  }
  return count;
}


// Provided below is a mixed-up-ness score.
// Name: mixedupness
// Input(s):
//    (1) 'array' is a pointer to an integer address. 
//         This is the start of some 'contiguous block of memory' that we will sort.
//    (2) 'size' tells us how big the array of data is we are sorting.
// Output: The mixedupness score of the original array
int mixedupness(int* array, unsigned int size){
  // TODO: Implement me!!
  return mergesort(array, 0, size - 1);
}

// Input: A pointer to an array (i.e. the array itself points to the first index)
//        The size of the array (Because we do not know how big the array is automatically)
void printIntArray(int* array, unsigned int size){
  unsigned int i; // Note: 'unsigned int' is a datatype for storing positive integers.
  for(i = 0; i < size; i=i+1){
    printf("%d ",array[i]);
  }
  printf("\n");
}

int main(){
  // Some test data sets.
  int dataset1[] = {0,1,2,3,4,5,6,7,8,9,10};
  int dataset2[] = {100,87,65,10,54,42,27,37};
  int dataset3[] = {0,3,2,1,4,7,6,5,8,9,10};
  int dataset4[] = {10,9,8,7,6,5,4,3,2,1,0};
  int dataset5[] = {100,201,52,3223,24,55,623,75,8523,-9,150};
  int dataset6[] = {-1,1,2,-3,4,5,-6,7,8,-9,10};

  // Print out an array
  printf("dataset 1: ");
  printIntArray(dataset1, 11);
  printf("dataset 2: ");
  printIntArray(dataset2, 8);
  printf("dataset 3: ");
  printIntArray(dataset3, 11);
  printf("dataset 4: ");
  printIntArray(dataset4, 11);
  printf("dataset 5: ");
  printIntArray(dataset5, 11);
  printf("dataset 6: ");
  printIntArray(dataset6, 11);
  printf("\n");
  
  // TODO: Change these so that they print 
  // both the expected score and the calculated score
  printf("dataset 1: expected = %d, actual = %d\n", 0, mixedupness(dataset1, 11));
  printf("dataset 2: expected = %d, actual = %d\n", 23, mixedupness(dataset2, 8));
  printf("dataset 3: expected = %d, actual = %d\n", 6, mixedupness(dataset3, 11));
  printf("dataset 4: expected = %d, actual = %d\n", 55, mixedupness(dataset4, 11));
  printf("dataset 5: expected = %d, actual = %d\n", 27, mixedupness(dataset5, 11));
  printf("dataset 6: expected = %d, actual = %d\n", 18, mixedupness(dataset6, 11));
  
  return 0;
}
