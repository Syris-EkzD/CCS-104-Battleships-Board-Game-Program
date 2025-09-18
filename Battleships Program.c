#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int ROWS, COLS;
int NUM_SHIPS;

void clearScreen();
void instructions();
void pickingGridSize();
void exitGame();
void buffer();
void initGrid(char grid[ROWS][COLS]);
void displayGrid(char grid[ROWS][COLS]);
void placeShips(char grid[ROWS][COLS], int player);
int takeShot(char opponentGrid[ROWS][COLS], char playerTrackingGrid[ROWS][COLS], int player);
void startGame();


int main() {
	int choices;	
	do {
		clearScreen();
		printf("Welcome to battleships!\n");
		printf("1. Start Game\n");
		printf("2. View Instructions\n");
		printf("3. Exit\n");
		printf("Choose an option: ");
		
		if (scanf("%d", &choices) != 1) {
			buffer();
			printf("Invalid Input");
			getch();
			continue;
		}
		
		
		switch(choices) {
			
			case 1:
				pickingGridSize();
			    startGame();
				break;
				
			case 2: 
				instructions();
				break;	 
				
			case 3:
				exitGame();
				return 0;
				
			default: 
				printf("Invalid Input");
				getch();
				break;
		}
	} while(choices != 3);
	return 0;
}

void clearScreen() {
	system("cls");
}

void pickingGridSize() {
	int gridSizeChoice;
	
	do {
		clearScreen();
		printf("Please choose the grid size and number of ships for you match!\n");
		printf("1. 3x3 | 1 ship\n");
		printf("2. 5x5 | 2 ships\n");
		printf("3. 7x7 | 3 ships\n");
		printf("4. 10x10 | 5 ships\n");
		printf("Your choice: ");
		if (scanf("%d", &gridSizeChoice) != 1) {
			printf("Invalid Input!");
			buffer();
			getch();
			gridSizeChoice = 0;
			continue;
		}
		
		switch(gridSizeChoice) {
			
			case 1:
				ROWS = 3;
				COLS = 3;
				NUM_SHIPS = 1;
				break;
			
			case 2:
				ROWS = 5;
				COLS = 5;
				NUM_SHIPS = 2;
				break;
				
			case 3: 
				ROWS = 7;
				COLS = 7;
				NUM_SHIPS = 3;
				break;
				
			case 4:
				ROWS = 10;
				COLS = 10;
				NUM_SHIPS = 5;
				break;
				
			default: 
				printf("Invalid Choice");
				gridSizeChoice = 0;	
				buffer();
				getch();
				continue;
		}
	} while(gridSizeChoice == 0);
}

void instructions() {
    clearScreen();
    printf("Welcome to Battleships!\n\n");
    printf("1. Each player places their %d ships on their own grid.\n", NUM_SHIPS);
    printf("2. Grids use coordinates: [Row][Column]. For example, '23' = Row 2, Column 3.\n");
    printf("3. Players take turns guessing the locations of the opponent's ships.\n");
    printf("4. Hits are marked as 'X' and misses as 'O' on your tracking grid.\n");
    printf("5. The first player to sink all opponent ships wins.\n\n");
    printf("Press any key to continue...");
    getch();
}


void exitGame() {
	clearScreen();
	printf("exiting game...");
	getch();
}

void buffer() {
	while(getchar() != '\n');
}

void initGrid(char grid[ROWS][COLS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			grid[i][j] = ' ';
		}
	}
}

void displayGrid(char grid[ROWS][COLS]) {
	printf("%3s", "");
	for (int j = 0; j < COLS; j++) {
		printf("%3d", j + 1);
	}
	printf("\n");
	
	for (int i = 0; i < ROWS; i++) {
		printf("%3d", i + 1);
	 	for (int j = 0; j < COLS; j++) {
			printf("%3c", grid[i][j]);
		}
		printf("\n");
	}	
}

void placeShips(char grid[ROWS][COLS], int player) {
	int rows, cols;
	
	for (int i = 0; i < NUM_SHIPS; i++) {
		do {	 
			clearScreen();
			printf("Current Board for: Player %d\n", player);
			displayGrid(grid);
			printf("Enter the coordinates for ship %d [e.g 1 2]: ", i + 1);
			if (scanf("%d %d", &rows, &cols) != 2) {
				printf("Invalid Input!");
				buffer();
				rows = cols = -1;
				getch();
				continue;
			}
			buffer();
			
			rows -= 1;
			cols -= 1;
						
			if (rows < 0 || rows >= ROWS || cols < 0 || cols >= COLS) {
				printf("Coordinates out of range! Try again.\n");
				getch();
			} else if (grid[rows][cols] == 'S') {
				printf("There is already a ship there! Try again.\n");
				getch();
			}
		} while (rows < 0 || rows >= ROWS || cols < 0 || cols >= COLS || grid[rows][cols] == 'S');
		
		grid[rows][cols] = 'S';
	}
	
	clearScreen();
	printf("Grid for Player %d\n", player);
	displayGrid(grid);
	printf("Press any key to continue: ");
	getch();
}

int linearSearch(char opponentGrid[ROWS][COLS], char playerTrackingGrid[ROWS][COLS], int rows, int cols) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (i == rows && j == cols) {
				if (opponentGrid[i][j] == 'S') {
					opponentGrid[i][j] = 'X';
					playerTrackingGrid[i][j] = 'X';
					return 1;
				} else if (playerTrackingGrid[i][j] == 'O' || playerTrackingGrid[i][j] == 'X') {
					return -1;
				} else {
					playerTrackingGrid[i][j] = 'O';
					return 0;
				}
			}
		}
	}
	return 0;
}
	
int takeShot(char opponentGrid[ROWS][COLS], char playerTrackingGrid[ROWS][COLS], int player) {
	int rows, cols;
	int result;
	int hit = 0;
	int validShot = 0;
	
	do {
		clearScreen();
		printf("X = Hit  O = Miss");
		printf("\n--- Player %d's Turn ---\n", player);
		printf("Your tracking grid: \n");	
		displayGrid(playerTrackingGrid);
		
		printf("Enter coordinates to fire [e.g 2 1]: ");
		 if (scanf("%d %d", &rows, &cols) != 2) {
		 	printf("Invalid Input!");
		 	buffer();
		 	validShot = 0;
		 	getch();
		 	continue;
		 }
		 buffer();

		rows -= 1;
		cols -= 1;

		
		if (rows < 0 || rows >= ROWS || cols < 0 || cols >= COLS) {
			printf("Coordinates are out of range.\n");
			buffer();
			getch();
			continue;
		}
		
		result = linearSearch(opponentGrid, playerTrackingGrid, rows, cols);
		
		if (result == 1) {
			printf("Hit!!");
			hit = 1;
			validShot = 1;
			getch();
		} else if (result == -1) {
			printf("You have already targeted this area!");
			validShot = 0;
			getch();
		} else {
			printf("Miss!!!");
			validShot = 1;
			hit = 0;
			getch();
		}
	} while (!validShot);
	return hit;
}

void startGame() {
	char response;
	do {
		clearScreen();
		char player1Grid[ROWS][COLS], player2Grid[ROWS][COLS];
	    char player1TrackingGrid[ROWS][COLS], player2TrackingGrid[ROWS][COLS]; 
		int player1Ships = NUM_SHIPS;
		int player2Ships = NUM_SHIPS;
	    int currentPlayer = 1;
	
	    initGrid(player1Grid);
	    initGrid(player2Grid);
	    initGrid(player1TrackingGrid);
	    initGrid(player2TrackingGrid);
	    
	    placeShips(player1Grid, 1);
	    clearScreen();
	    printf("Player 1 has finished setting up their ships.\n");
	    printf("Press any key to proceed to Player 2....\n");
		getch();
		placeShips(player2Grid, 2);
		
		while(player1Ships > 0 && player2Ships > 0) {
			if (currentPlayer == 1) {
				player2Ships -= takeShot(player2Grid, player1TrackingGrid, 1);
				currentPlayer = 2;
			} else {
				player1Ships -= takeShot(player1Grid, player2TrackingGrid, 2);
				currentPlayer = 1;
			}
		}    
		
		clearScreen();
		if (player1Ships == 0) {
			printf("All of Player 1's ships have been destroyed!");
			printf("\nPlayer 2 wins!!!");
		} else {
			printf("All of Player 2's ships have been destroyed!");
			printf("\nPlayer 1 wins!!!");
		}
		printf("\nDo you wish to play again? [Y/N]: ");
		
		response = getch();
	} while (response == 'Y' || response == 'y');
}


 
