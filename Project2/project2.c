/* ENGGEN131 Project - C Project - 2021 */
/* Container Yard */

/*Shiangbo Chang, schb498, 412341057*/

#include <stdio.h>
#define NUM_ROWS 8
#define NUM_COLS 8

#define VACANT 0
#define BOUNDARY -1
#define ENTRY -2
#define EXIT -3

void InitialiseFloor(int floor[NUM_ROWS][NUM_COLS], char entryboundary, int index);
void PrintFloor(int floor[NUM_ROWS][NUM_COLS]);
double FloorAreaAvailable(int floor[NUM_ROWS][NUM_COLS], double length, double width);
void AddContainer(int floor[NUM_ROWS][NUM_COLS], int position, int size, int direction);
int LocateContainer(int floor[NUM_ROWS][NUM_COLS], char move, int* rowStart, int* colStart, int* rowEnd, int* colEnd);
int MoveContainer(int floor[NUM_ROWS][NUM_COLS], int r0, int c0, int r1, int c1, int isBlocked);

/*
Your comment should go here – it should describe the purpose of the function and a
brief summary of the algorithm you have used to solve the task (this comment must
be written in your own words
*/
int main()
{
	int floor[NUM_ROWS][NUM_COLS];

	int rowA, colA, rowB, colB;
	int isBlocked;
	int result;


	/*Task 1*/
	InitialiseFloor(floor, 'R', 3);
	*/

	/*Task 2
	PrintFloor(floor);
	*/

	/*Task 3
	printf("Available Area: %f sq ft\n", FloorAreaAvailable(floor, 10.5, 25.6));
	*/

	/*Task 4
	AddContainer(floor, 25, 2, 0);
	AddContainer(floor, 28, 3, 1);
	PrintFloor(floor);
	*/

	/*Task 5
	isBlocked = LocateContainer(floor, 'A', &rowA, &colA, &rowB,
		&colB);
	printf("Container A is at: (%d, %d) - (%d, %d) Blocked? %d\n",
		rowA, colA, rowB, colB, isBlocked);

	isBlocked = LocateContainer(floor, 'B', &rowA, &colA, &rowB,
		&colB);
	printf("Container B is at: (%d, %d) - (%d, %d) Blocked? %d\n",
		rowA, colA, rowB, colB, isBlocked);

	isBlocked = LocateContainer(floor, 'C', &rowA, &colA, &rowB,
		&colB);
	printf("Container C is at: (%d, %d) - (%d, %d) Blocked? %d\n",
		rowA, colA, rowB, colB, isBlocked);
	*/

	// Move container B:

	isBlocked = LocateContainer(floor, 'B', &rowA, &colA,
		&rowB, &colB);
	result = MoveContainer(floor, rowA, colA, rowB, colB,
		isBlocked);
	printf("Result = %d\n", result);
	PrintFloor(floor);
	*/

	InitialiseFloor(floor, 'R', 3);
	AddContainer(floor, 25, 2, 0);
	PrintFloor(floor);
	// Move container A:
	isBlocked = LocateContainer(floor, 'A', &rowA, &colA,
		&rowB, &colB);
	result = MoveContainer(floor, rowA, colA, rowB, colB,
		isBlocked);
	printf("Result = %d\n", result);
	PrintFloor(floor);



	return 0;
}
//------------------------------------------------------------------------------------------------------

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

