// Your name: Zhicun Chen
// Date: 5/18/2022
//
// Add your program here!
// 

#include <stdio.h>
#include <stdlib.h>

// count total rounds
int count = 0;
// store results
int result[5];
// program picked number
int pickedNum; 

// assign the random number
void init() {
	pickedNum = getRand();
}

// get a random number
int getRand() {
	srand(time(NULL));
	int randNum = rand() % 10 + 1;
	return randNum;
} 

// get user input
int getInput() {
	int num;	
	scanf("%d", &num);
	return num;
}

// display game process
void gameDisplay() {
	printf("============================\n");
	printf("CPU Says: Pick a number 1-10\n");
	printf("============================\n");
}

// indicate guess result
int indicator(int guessedNum, int pickedNum) {
		switch (compareTo(guessedNum, pickedNum)) {
		case -1:
			printf("No guess higher!\n");
			return 1;
		case 0:
			printf("You got it!\n");
			return 0;
		case 1: 
			printf("No guess lower!\n");
			return 1;
	}
}

// -1 if guessedNum is less than pickedNum
// 0 if equal
// 1 if greater
int compareTo(int guessedNum, int pickedNum) {
	if (guessedNum == pickedNum) { 
		return 0;
	}
	if (guessedNum < pickedNum) {
		return -1;
	}
	return 1;
}


// display game result
void resultDisplay(int result[]) {
	printf("=================================================\n");
	printf("|Here are the results of your guessing abilities|\n");
	printf("=================================================\n");
	int i = 0;
	for (; i < 5; i=i+1) {
		printf("Game %d took you %d guesses\n", i, result[i]);
	}
}

int main() {
	while (count < 5) {
		int countNumOfGuess = 0;
		//1. get program picked number
		init();
		//2. render game title
		gameDisplay();	
		while (1) {
			//3. get input
			printf("Make a guess: ");
			int guessedNum = getInput();
			// increase the number of guess
			countNumOfGuess++;	
			//4. determine guess result
			int res = indicator(guessedNum, pickedNum);
			// if guess correct, store the number of guess and start the next round
			if (res == 0) {
				result[count] = countNumOfGuess;
				count++;	
				break;
			}
		}					
	}
	//5. finally print the results 
	resultDisplay(result);	
	return 0;
}


