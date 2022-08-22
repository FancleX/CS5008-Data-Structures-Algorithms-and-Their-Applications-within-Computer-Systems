// Your name: Zhicun Chen
// Date: 5/19/2022
//
// Add your program here!
// 

#include <stdio.h>

double power(double base, double n) {
	if (n == 0) {
		return 1;
	} 
	return base * power(base, n - 1);
}

int main() {
	double i = 1;
	while (i <= 10) {
		double result = power(2, i);
		printf("power(2, %.0f) = %.0f\n", i, result);
		i++;
	}
	return 0;
}


