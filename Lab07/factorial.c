// Zhicun Chen
// 7/17/2022
//
// gcc -Wall factorial.c -o factorial
// ./factorial

#include <stdio.h>

long factorial(long n){
  // TODO: Implement iterative solution here
  long result = 1;
  while (n > 0) {
    result *= n;
    n--;
  }
  return result;
};

long factorial_rec(long n){
  // TODO: Implement recursive solution here
  if (n == 0) {
    return 1;
  }
  return n * factorial_rec(n - 1);
}

int main(){

  // Both of these should print the same result!
  printf("factorial(10) = %ld\n",factorial(10l));
  printf("factorial_rec(10) = %ld\n",factorial_rec(10l));

  return 0;
}
