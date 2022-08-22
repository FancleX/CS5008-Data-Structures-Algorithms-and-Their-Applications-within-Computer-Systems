// Zhicun Chen
// 6/4/2022
// CS5008 Lab03
//
// Implement your cycle count tool here.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


// filter command string
char* filter(char* arr) {
        int i;
        for (i = 0; i < strlen(arr); i++) {
                // contents after # sign are comments
                // and fliter the unnecessary content after .
                if (arr[i] == '#') {
                        arr[i] = '\0';
                        return arr;
                }
        }
        return arr;
}

// analyze the instructions in the char array and storage it in storage
void stringAnalyzer(char* arr, int* storage, char** instructions) {
	// check if it is a command
        char* filteredArr = filter(arr);
        // skip comments and \n
        if (strlen(filteredArr) != 0 || filteredArr[0] != '\n') {
                // loop for seaching those instructions in the line
                int i;
                for(i = 0; i < 9; i++) {
                        if (strstr(filteredArr, instructions[i]) != NULL) {
                                // if find one, add it to storage
                                storage[i]++;
                                break;
                        }
                }
        }			
}

// convert a string to uppercase
char* strupr(char* str) {
	char* pt = NULL;
	pt = str;
	if (pt != NULL) {
		while(*pt) {
			*pt = toupper((int)*pt);
			++pt;
		}
	}
	return str;
}

// read file name that will be estimated
int main(int argc, char** argv) {
	// create buffer and file pointer
	FILE* fp;
	char* buffer = (char*) malloc(sizeof(char) * 200);
	// count for instructions
	int count_i = 0;
	// count for cycles
	int count_c = 0;	
	// define an array of instructions that need to be counted
	char* instructions[9] = {"add", "sub", "mul", "div", "mov", "lea", "push", "pop", "ret" };
	// create an array with initials 0 to store counts
	int result[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	// check args
	if (argc < 2) {
		printf("Please use: ./estimator <filename>\n");
		return 0;
	}
	// determine if the file is exit
	if ((fp = fopen(argv[1], "r")) == NULL) {
		printf("The file doesn't exit or cannot open\n");	
		return 0;
	}
	
	// if it can be opened
	// read file
	while (!feof(fp)) {
		// read a line as chars, then store them in the buffer
		fgets(buffer, 200, fp);
		// process the string and count it
		stringAnalyzer(buffer, result, instructions);
		// count cycles
		count_c++;
	}
	// close the file
	fclose(fp);
	// print the result
	int i;
	for(i = 0; i < 9; i++) {
		if (result[i] != 0) {
			// create a temp char array
			char temp[4] = "";
			// copy the char* of instructions to the temp array
			// this will convert read ony char* to char[] that can be modified to uppercase
			strncpy(temp, instructions[i], sizeof(temp));
			// print result
			if (result[i] > 1) {
				printf("%s counts as %d cycles\n", strupr(temp), result[i]);
			} else {
				printf("%s counts as %d cycle\n", strupr(temp), result[i]);
			}
			// count number of instructions
			count_i++;
		}
	}
	// print counts
	printf("\nTotal Instructions = %d\n", count_i);	
	printf("Total Cycles = %d\n", count_c);
	// free storage
	free(buffer);
	return 0;
}
