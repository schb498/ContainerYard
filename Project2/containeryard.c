#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NUM_ROWS 8
#define NUM_COLS 8

#define VACANT 0
#define BOUNDARY -1
#define ENTRY -2
#define EXIT -3

/***********************************************************/
/***********************************************************/
/******* ADD THE REQUIRED FUNCTIONS BELOW THIS POINT *******/
/***********************************************************/
/***********************************************************/

// Your function definitions should go here...
/*
InitialiseFloor function creates an array for the floor which using numbers.
It uses a for loop to set the correct numbers in the right positions,
and if statements to check for the position of entry boundaries.
Author: Shiangbo Chang
*/
void InitialiseFloor(int floor[NUM_ROWS][NUM_COLS], char entryboundary, int index)
{
	//For loop goes through every element in the array
	for (int i = 0; i < NUM_COLS; i++) {
		for (int j = 0; j < NUM_ROWS; j++) {
			//Checks if the position is on the 'boundary' of the array (outer edge)
			if ((i == 0) || (i == NUM_COLS - 1) || (j == 0) || (j == NUM_ROWS - 1)) {
				floor[i][j] = BOUNDARY;
			}
			else {
				floor[i][j] = VACANT;
			}
		}
	}

	//Checks the value for entryboundary to determine entry and exit positions
	if (entryboundary == 'T') {
		floor[0][index] = ENTRY;
		floor[NUM_ROWS - 1][index] = EXIT;
	}
	else if (entryboundary == 'B') {
		floor[0][index] = EXIT;
		floor[NUM_ROWS - 1][index] = ENTRY;
	}
	else if (entryboundary == 'L') {
		floor[index][0] = ENTRY;
		floor[index][NUM_ROWS - 1] = EXIT;
	}
	else if (entryboundary == 'R') {
		floor[index][0] = EXIT;
		floor[index][NUM_ROWS - 1] = ENTRY;
	}
	return;
}

/*
PrintFloor function prints out the given floor array.
It uses a nested for loop and if statements.
Author: Shiangbo Chang
*/
void PrintFloor(int floor[NUM_ROWS][NUM_COLS])
{
	//Initialise variables
	int i = 0, j = 0;

	//Nested for loop goes through every position in array
	for (i = 0; i < NUM_COLS; i++) {
		for (j = 0; j < NUM_ROWS; j++) {
			//Initialise variable that shortens code
			int pos = floor[i][j];
			//Conditions checking current position to determine what to print
			if (pos == -1) {
				printf("@");
			}
			else if (pos == 0) {
				printf(" ");
			}
			else if (pos == -2) {
				printf("U");
			}
			else if (pos == -3) {
				printf("X");
			}
			else {
				printf("%c", pos);
			}
			//Condition to check if end of row is reached
			if (j == NUM_COLS - 1) {
				printf("\n");
			}
		}
	}
	return;
}

/*
FloorAreaAvailable calculates the total area available by using a loop to count.
Author: Shiangbo Chang
*/
double FloorAreaAvailable(int floor[NUM_ROWS][NUM_COLS], double length, double width)
{
	//Initialise variable that counts the number of free spaces
	int free = 0;

	//Calculate the area of each grid cell
	double cellArea;
	cellArea = length * width;

	//Nested loops to check every positon in the array
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			//Checks if value in current position is vacant
			if (floor[i][j] == VACANT) {
				free++;
			}
		}
	}
	return free * cellArea;
}

/*
AddContainer function adds one container into the array by changing the
positions of the container into numbers
Author: Shiangbo Chang
*/
void AddContainer(int floor[NUM_ROWS][NUM_COLS], int position, int size, int direction)
{
	//Initialise variables
	int row, col, max = 0;

	//Calculates the start position of container
	row = position / NUM_COLS;
	col = position % NUM_COLS;

	//Nested loop finds current maximum value in array
	for (int i = 1; i < NUM_COLS - 1; i++) {
		for (int j = 1; j < NUM_ROWS - 1; j++) {
			if (floor[i][j] > max) {
				max = floor[i][j];
			}
		}
	}
	//Checks if array has no containers
	if (max == 0) {
		max = 64;
	}

	//Loop checks if position of container is vacant, and places it depending on the outcome
	for (int count = 0; count < 2 * size; count++) {
		//Checks if current position is empty
		if (count < size) {
			if ((count < size) && ((!direction && floor[row][col + count] != 0) || (direction && floor[row + count][col] != 0))) {
				break; //Exits loop if position is not vacant
			}
		}
		//Adds container in specified position
		else {
			if (!direction) {
				floor[row][col + count - size] = max + 1; //Assigned to ascii value
			}
			else if (direction) {
				floor[row + count - size][col] = max + 1; //Assigned to ascii value
			}

		}
	}
	return;
}

/*
LocateContainer function uses for loops to find the start and end positions of the input container.
Then checks if the container is blocked on both ends (lengthways) and returns correct output.
Author: Shiangbo Chang
*/
int LocateContainer(int floor[NUM_ROWS][NUM_COLS], char move, int* rowStart, int* colStart, int* rowEnd, int* colEnd)
{
	//Initialise variables
	int i, j, k, l, result = 0;

	//For loops to find end position of given container
	for (i = 0; i < NUM_ROWS; i++) {
		for (j = 0; j < NUM_COLS; j++) {
			if (floor[i][j] == move) {
				*rowEnd = i;
				*colEnd = j;
			}
		}
	}
	//For loops to find start position of given container
	for (k = NUM_ROWS; k >= 0; k--) {
		for (l = NUM_COLS; l >= 0; l--) {
			if (floor[k][l] == move) {
				*rowStart = k;
				*colStart = l;
			}

		}
	}

	//Conditions to check if container has vacant spot on any end (lengthways)
	if (*colStart == *colEnd) {
		if ((floor[*rowStart - 1][*colStart] == VACANT) || (floor[*rowEnd + 1][*colStart] == VACANT)) {
			result = 1;
		}
	}
	else if (*rowStart == *rowEnd) {
		if ((floor[*rowStart][*colStart - 1] == VACANT) || (floor[*rowStart][*colEnd + 1] == VACANT)) {
			result = 1;
		}
	}
	return result;
}

/*
MoveContainer attempts to move container using the given input positions.
If container is not blocked, container will move until it is unable to.
It returns an integer depending if container is next to the entry or exit.
Author: Shiangbo Chang
*/
int MoveContainer(int floor[NUM_ROWS][NUM_COLS], int r0, int c0, int r1, int c1, int isBlocked)
{
	//Initialise variables
	int i = 1, container, result = 0;

	//Sets variable to the value of the container with positions given in the input
	container = floor[r0][c0];

	//Condition to check if container is blocked and if it is next to entry, exit, or otherwise
	if (isBlocked == 0) {
		//Checks if container is horizontal
		if (r0 == r1) {
			if ((floor[r0][c0 - 1] == ENTRY) || (floor[r0][c1 + 1] == ENTRY)) {
				result = 1;
			}
			else if ((floor[r0][c0 - 1] == EXIT) || (floor[r0][c1 + 1] == EXIT)) {
				result = 2;
			}
			else {
				result = -1;
			}
		}
		//Checks if container is vertical
		else if (c0 == c1) {
			if ((floor[r0 - 1][c0] == ENTRY) || (floor[r1 + 1][c0] == ENTRY)) {
				result = 1;
			}
			else if ((floor[r0 - 1][c0] == EXIT) || (floor[r1 + 1][c0] == EXIT)) {
				result = 2;
			}
			else {
				result = -1;
			}
		}
	}

	//If container isn't blocked:

	//Checks if container is horizontal and has vacant spot on its left
	if ((r0 == r1) && (floor[r0][c0 - 1] == VACANT) && (isBlocked == 1)) {
		//Loop checks if container has space on its left
		while (floor[r0][c0 - i] == VACANT) {
			//Replaces checked position with container and removes one value at the end of it
			floor[r0][c0 - i] = container;
			floor[r0][c1 - i + 1] = VACANT;
			//Checks if position on its left is entry or exit
			if (floor[r0][c0 - i - 1] == ENTRY) {
				result = 1;
			}
			else if (floor[r0][c0 - i - 1] == EXIT) {
				result = 2;
			}
			i++;
		}
	}
	//Checks if container is horizontal and has vacant spot on its right
	else if ((r0 == r1) && (floor[r0][c1 + 1] == VACANT) && (isBlocked == 1)) {
		//Loop checks if container has space on its right
		while (floor[r0][c1 + i] == VACANT) {
			//Replaces checked position with container and removes one value at the end of it
			floor[r0][c1 + i] = container;
			floor[r0][c0 + i - 1] = VACANT;
			//Checks if position on its right is entry or exit
			if (floor[r0][c1 + i + 1] == ENTRY) {
				result = 1;
			}
			else if (floor[r0][c1 + i + 1] == EXIT) {
				result = 2;
			}
			i++;
		}
	}
	//Checks if container is horizontal and has vacant spot above
	else if ((c0 == c1) && (floor[r0 - 1][c0] == VACANT) && (isBlocked == 1)) {
		//Loop checks if container has space above
		while (floor[r0 - i][c0] == VACANT) {
			//Replaces checked position with container and removes one value at the end of it
			floor[r0 - i][c0] = container;
			floor[r1 - i + 1][c0] = VACANT;
			//Checks if position above is entry or exit
			if (floor[r0 - i - 1][c0] == ENTRY) {
				result = 1;
			}
			else if (floor[r0 - i - 1][c0] == EXIT) {
				result = 2;
			}
			i++;
		}
	}
	//Checks if container is horizontal and has vacant spot below
	else if ((c0 == c1) && (floor[r1 + 1][c0] == VACANT) && (isBlocked == 1)) {
		//Loop checks if container has space below
		while (floor[r1 + i][c0] == VACANT) {
			//Replaces checked position with container and removes one value at the end of it
			floor[r1 + i][c0] = container;
			floor[r0 + i - 1][c0] = VACANT;
			//Checks if position below is entry or exit
			if (floor[r1 + i + 1][c0] == ENTRY) {
				result = 1;
			}
			else if (floor[r1 + i + 1][c0] == EXIT) {
				result = 2;
			}
			i++;
		}
	}
	//Returns the result
	return result;
}

/***********************************************************/
/***********************************************************/
/********* DO NOT MODIFY ANY CODE BELOW THIS POINT *********/
/***********************************************************/
/***********************************************************/

/* Function to obtain capital letter as input */
char GetMove(void)
{
	char move;
	printf("\nMove container: ");
	scanf("%c", &move);
	// Ignore non-capital letter inputs
	while ((move < 'A') || (move > 'Z')) {
		scanf("%c", &move);
	}
	return move;
}

/* The main Container Yard simulation */
int main(void)
{
	int gameOver = 0;
	int isBlocked = 0;
	int floor[NUM_ROWS][NUM_COLS];
	int rowStart, colStart, rowEnd, colEnd;
	char input;

	/* Print banner */
	printf("............**********************************............\n");
	printf("............* CONTAINER YARD GAME SIMULATION *............\n");
	printf("............**********************************............\n");
	
	/* Initialise the yard floor grid and add containers */
	InitialiseFloor(floor, 'L', 3);
	AddContainer(floor, 28, 2, 0);
	AddContainer(floor, 11, 3, 1);
	AddContainer(floor, 41, 2, 1);
	AddContainer(floor, 42, 2, 1);
	AddContainer(floor, 42, 2, 1);
	AddContainer(floor, 34, 2, 0);
	AddContainer(floor, 36, 3, 1);
	AddContainer(floor, 37, 2, 1);
	AddContainer(floor, 53, 2, 0);
	AddContainer(floor, 30, 3, 1);

	/* Print status */
	printf("ENGGEN131 2021 - C Project\nContainer Yard!  The containers are rushing in!\n");
	printf("In fact, %.2f sq ft of the yard floor is available for containers!\n\n", FloorAreaAvailable(floor, 20.5, 10.3));

	/* Main simulation loop */
	while (gameOver != 2) {
		PrintFloor(floor);
		input = GetMove();
		isBlocked = LocateContainer(floor, input, &rowStart, &colStart, &rowEnd, &colEnd);
		gameOver = MoveContainer(floor, rowStart, colStart, rowEnd, colEnd, isBlocked);
	}

	/* A container is ready to exit - the simulation is over */
	PrintFloor(floor);
	printf("\nCongratulations, you've succeeded!");

	return 0;
}
