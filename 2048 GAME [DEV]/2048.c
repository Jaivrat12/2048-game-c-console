#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "lib/project.h"

//int ROWS = 4, COLS = 4;
char playerName[100];
int highScore = 0;
int score = 0;

int difficulty;

int board[ROWS][COLS] = {2}; //{2, 128, 64, 2, 16, 4, 8, 16, 2, 0, 4, 8}; //{2, 128, 32, 8, 8, 16, 64, 2, 2, 8, 8, 2, 0, 0, 0, 2}
int boardCopy[ROWS][COLS];
int boardDigits[ROWS][COLS];
int addedOnce = 0;

int rows, cols;

void calcResolution();

void loadingScreen();
void updateLoadBar();
void clearRow();
void loadGameData();
void initDataFile();
void saveGameData(int);

void mainMenu();

void play();
void settings();

void initializeBoard();
void printBoard(int);
void copyBoard();
int parseInput(char);

int boardIsChanged();
void transposeBoard();
void move(int);
void add(int);
void spawnNum();
int assignBoardDigits(int);

int gameOver();
int checkForPairs();


int main() {

	loadingScreen();
	getch();
	resetColor();

	while (1) {

		mainMenu();
	}

    return 0;
}


void calcResolution() {

	cols = getConsoleWidth();
	rows = getConsoleHeight();
}

void loadingScreen() {

	system("MODE CON: COLS=120 LINES=30");
	calcResolution();

	gotoxy(cols/2 - 8, rows/2 - rows/4 - 2);
	setColor(GREEN - 8);
	printf("%c", 254);
	setColor(YELLOW - 8);
	for(int i = 0; i < 9; i++) {

		printf("%c", 205);
	}
	setColor(GREEN);
	printf("%c", 254);
	setColor(YELLOW - 8);
	gotoxy(cols/2 - 8, rows/2 - rows/4 - 1);
	printf("%c", 186);
	setColor(CYAN);
	printf("2048 GAME");
	setColor(YELLOW);
	printf("%c", 186);
	gotoxy(cols/2 - 8, rows/2 - rows/4);
	setColor(GREEN - 8);
	printf("%c", 254);
	setColor(YELLOW);
	for(int i = 0; i < 9; i++) {

		printf("%c", 205);
	}
	setColor(GREEN);
	printf("%c", 254);

	setColor(PINK - 8);
	gotoxy(cols/2 - 10, rows/2 - rows/4 + 2);
	printf("LOADING... ");

	int i;
	gotoxy(cols/2 - 15, rows/2 - rows/4 + 3);
	setColor(10);
	printf("%c", 201);
	for(i = 0; i < 23; i++) {

		printf("%c", 205);
	}
	printf("%c", 187);
	gotoxy(cols/2 - 15, rows/2 - rows/4 + 4);
	printf("%c", 186);
	for(i = 0; i < 23; i++) {

		printf(" ");
	}
	printf("%c", 186);
	gotoxy(cols/2 - 15, rows/2 - rows/4 + 5);
	printf("%c", 200);
	for(i = 0; i < 23; i++) {

		printf("%c", 205);
	}
	printf("%c", 188);

	setColor(14);
	gotoxy(cols/2 - 14, rows/2 - rows/4 + 4);
	printf("%c", 222);

	updateLoadBar();
    printf("  Loading Game Data...");
    loadGameData();
    updateLoadBar();
	gotoxy(cols/2 + 8, rows/2 - rows/4 + 4);
	setColor(14);
	printf("%c", 221);

	setColor(GREEN);
	gotoxy(cols/2 + 1, rows/2 - rows/4 + 2);
	printf("100%%");

	setColor(CYAN);
	gotoxy(cols/2 - 16, rows/2 - rows/4 + 6);
    printf("Press any key to continue...");
}

void clearRow() {

	gotoxy(0, rows/2 - rows/4 + 6);
	for(int i = 0; i < cols; i++) {

		printf(" ");
	}
}

void updateLoadBar() {

	static int i, counter;

	setColor(PINK);
	gotoxy(cols/2 + 1, rows/2 - rows/4 + 2);
	printf("%d%%", counter);
	counter += 15;

	if(i >= 9 && i <= 12) {

		setColor(225);
		gotoxy(cols/2 - 13 + i++, rows/2 - rows/4 + 4);
		printf("2");
		wait(0.2);
		gotoxy(cols/2 - 13 + i++, rows/2 - rows/4 + 4);
		printf("0");
		wait(0.2);
		gotoxy(cols/2 - 13 + i++, rows/2 - rows/4 + 4);
		printf("4");
		wait(0.2);
		gotoxy(cols/2 - 13 + i++, rows/2 - rows/4 + 4);
		printf("8");
		wait(0.2);
	}
	else if(i < 21) {

		setColor(14);
		gotoxy(cols/2 - 13 + i++, rows/2 - rows/4 + 4);
		printf("%c", 219);
		wait(0.2);
		gotoxy(cols/2 - 13 + i++, rows/2 - rows/4 + 4);
		printf("%c", 219);
		wait(0.2);
		gotoxy(cols/2 - 13 + i++, rows/2 - rows/4 + 4);
		printf("%c", 219);
		wait(0.2);
	}

	setColor(15);
	clearRow();
	setColor(WHITE);
	gotoxy(cols/2 - 14, rows/2 - rows/4 + 6);
}

void loadGameData() {

	updateLoadBar();
    printf("\b\bChecking for 'data.txt' file");

    FILE *fptr;
    if ((fptr = fopen("data/data.txt", "r")) == NULL) {

        //wait(0.9);
        initDataFile();
        fclose(fptr);
        main();
    }

	updateLoadBar();
    printf("\b\b\b\bReading File and Acquiring the Data");

	fscanf(fptr, "%d", &difficulty);
	fscanf(fptr, "%d", &highScore);
	fscanf(fptr, "%d", &score);

	for(int i = 0; i < ROWS; i++) {

		for(int j = 0; j < COLS; j++) {

			fscanf(fptr, "%d", &board[i][j]);
		}
	}

	updateLoadBar();
    printf("     Closing File... ");
    fclose(fptr);

    updateLoadBar();
	/*
    printf("\bDecrypting Acquired Data...");
    int pow10 = 1;
    i = 0;
    while(data[1][i] != '\n') {

        //printf("%d> %c\n", i, data[1][i]);
        highScore += (data[1][i] - 65) * pow10;
        //printf("  -> High Score: %d\n", highScore);
        pow10 *= 10;
        i++;
    }
	*/

    updateLoadBar();
    printf("\b\bAcquired Data Successfully!!");
}

void initDataFile() {

    FILE *fp;
    fp = fopen("data/data.txt","w");
    fprintf(fp, "1\n");
    fprintf(fp, "0\n");
	fprintf(fp, "0\n");
	for(int i = 0; i < ROWS; i++) {

		for(int j = 0; j < COLS; j++) {

			fprintf(fp, "%d\n", board[i][j]);
		}
	}
    fclose(fp);
}

void saveGameData(int resetHighScore) {

	printf("\bSaving Game Data...");

	if(resetHighScore)
		highScore = 0;
	else
		highScore = (highScore < score) ? score : highScore;

	FILE *fptr;
	fptr = fopen("data/data.txt", "w");
	fprintf(fptr, "%d\n", difficulty);
	fprintf(fptr, "%d\n", highScore);
	fprintf(fptr, "%d\n", score);

	for(int i = 0; i < ROWS; i++) {

		for(int j = 0; j < COLS; j++) {

			fprintf(fptr, "%d\n", board[i][j]);
		}
	}
	fclose(fptr);

	wait(0.5);
	printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                   \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b ");
}

void mainMenu() {

	static int choice = 1;

    CLS;
	gotoxy(cols/2 - 9, rows/2 - rows/4);
	setColor(160);
    printf(" M A I N-M E N U ");
	gotoxy(cols/2 - 3, rows/2 - rows/4 + 3);
	setColor(CYAN);
    printf("PLAY");
	gotoxy(cols/2 - 7, rows/2 - rows/4 + 5);
	setColor(YELLOW);
    printf("INSTRUCTIONS");
	gotoxy(cols/2 - 5, rows/2 - rows/4 + 7);
	setColor(PINK);
    printf("SETTINGS");
	gotoxy(cols/2 - 3, rows/2 - rows/4 + 9);
	setColor(RED);
    printf("EXIT");
	resetColor();

	int x = cols/2 - 12;
	int y = rows/2 - rows/4 + (2 * choice) + 1;
    char control;

    gotoxy(x, y);
    printf(" -> ");

    gotoxy(x, y);
    //Loop until "ENTER" key isn't pressed...
    while((control = getch()) != 13) {

        if(control == 'w' || control == 'W' || control == 72) {

            if(choice == 1) {

                choice = 4;
                y = rows/2 - rows/4 + 9;
            }
            else {

                choice--;
                y -= 2;
            }
        }
        else if(control == 's' || control == 'S' || control == 80) {

            if(choice == 4) {

                choice = 1;
                y = rows/2 - rows/4 + 3;
            }
            else {

                choice++;
                y += 2;
            }
        }

        printf("    ");
        gotoxy(x, y);
        printf(" -> \b\b\b\b");
    }

    switch(choice) {

        case 1: CLS;
                play();
                return;

        case 2: CLS;
				gotoxy(cols/2 - 14, rows/2 - rows/3);
				setColor(224);
                printf("I N S T R U C T I O N S\n\n\n");
				resetColor();
				printf("\t\tInstructions are Pretty Simple. Use the controls listed below to move the numbers,\n\t\t  mix the same ones and make them larger, and try to score as high as possible!\n");
				gotoxy(cols/2 - 7, rows/2 - rows/3 + 6);
				setColor(GREEN);
				printf("CONTROLS:");
				gotoxy(cols/2 - 7, rows/2 - rows/3 + 8);
				printf("W:    UP");
				gotoxy(cols/2 - 7, rows/2 - rows/3 + 9);
				printf("S:    DOWN");
				gotoxy(cols/2 - 7, rows/2 - rows/3 + 10);
				printf("A:    LEFT");
				gotoxy(cols/2 - 7, rows/2 - rows/3 + 11);
				printf("D:    RIGHT\n");
				resetColor();
				printf("\n\tNOTE: The Arrow Keys also work but are not recommended, however you can still use them if you wish.\n");
				printf("\t\t\t\t\bAlso note that the W, A, S, D controls are case-insensitive.\n\n");
				PAUSE;
                return;

        case 3: settings();
				return;

        case 4: CLS;
                exit(0);
    }
}

void play() {

    int boardChanged = 0;

    printBoard(assignBoardDigits(0));

	printf("\nz: Main Menu\tx: Save Game\tr: Reset Board\n");

    printf("\n> ");

    while(1) {

        copyBoard();

        //printf("\n> ");
        if(parseInput(getche())) {

			return;
		}
        /*
        if(gameOver()) {

            printf("GAME OVER!!!\nDO YOU WANT TO RETRY?(Press 'y' for yes)\n> ");
            if(getch() == 'y') {

                printf("Restarting Game...\n");
                PAUSE;
                main();
            }
            else {

                printf("Thank You for Playing...\nClosing this Game...\n");
                PAUSE;
                exit(0);
            }
        }
        else */
        if(boardIsChanged()) {

            spawnNum();
            int maxDigits = assignBoardDigits(0);
            printBoard(maxDigits);

            if(!boardChanged) {

                boardChanged = 1;
            }
        }
        else {

            boardChanged = 0;
        }

        if(boardChanged) {

			printf("\nz: Main Menu\tx: Save Game\tr: Reset Board\n");
            printf("\n> ");
        }
        else {

            //_sleep(100);
            printf("\b \b");
        }
    }
}

void settings() {

	static int y = 2, choice = 1;
    char control;

    while(1) {

		CLS;
		printf("> ");
		setColor(208);
	    printf(" S E T T I N G S \n\n");
		resetColor();
		if(difficulty == EASY)
			printf("    [EXPERIMENTAL] Change Difficulty to HARD ['2' will spawn Randomly at any free place in the board]\n");
		else
			printf("    Change Difficulty to EASY ['2' will spawn at first space (at first '0') available]\n");
	    printf("    Reset High-Score [High-Score: %d]\n", highScore);
		printf("    Reset Game Data\n");
	    printf("    Resize Console to Default\n");
		printf("    Recalculate Resolution for Current Console Size\n");
		printf("    Return to MAIN MENU\n");

	    gotoxy(0, y);
	    printf(" -> ");

	    gotoxy(0, y);
	    //Loop until "ENTER" key isn't pressed...
	    while((control = getch()) != 13) {

	        if(control == 'w' || control == 'W' || control == 72) {

	            if(choice == 1) {

	                choice = 6;
	                y = 7;
	            }
	            else {

	                choice--;
	                y--;
	            }
	        }
	        else if(control == 's' || control == 'S' || control == 80) {

	            if(choice == 6) {

	                choice = 1;
	                y = 2;
	            }
	            else {

	                choice++;
	                y++;
	            }
	        }

	        printf("\r    ");
	        gotoxy(0, y);
	        printf(" -> \r");
	    }

		switch (choice) {

			case 1: difficulty = (difficulty == EASY) ? HARD : EASY;
					printf("\n\n\n\n\n\n\n>  ");
					saveGameData(0);
					break;

			case 2: printf("\n\n\n\n\n\n> Do you really want to 'RESET' your High-Score? (Press Enter/Return key to Confirm)\n\n> ");
					if(getch() == 13) {

						highScore = 0;
						printf(" ");
						printf("\bHigh-Score was Reset to %d", highScore);
						wait(0.5);
						printf("\r                           \r>  ");
						saveGameData(1);
					}
					break;

			case 3: printf("\n\n\n\n\n\n> Do you really want to 'RESET' your GAME DATA? (Press Enter/Return key to Confirm)\n\n> ");
					if(getch() == 13) {

						initializeBoard();
						highScore = score = 0;
						difficulty = EASY;
						initDataFile();
						printf("Reinitialized Game Data...");
						wait(0.5);
					}
					break;

			case 4: printf("\n\n\n\n> DONE! cols = 120, rows = 30");
					wait(0.5);
					system("MODE CON: COLS=120 LINES=30");
					calcResolution();
					break;

			case 5: calcResolution();
					printf("\n\n\n> DONE! cols = %d, rows = %d", cols, rows);
					wait(0.5);
					break;

			case 6: choice = 1;
					y = 2;
					return;
		}
	}
}

void initializeBoard() {

    for(int i = 0; i < ROWS; i++)
		for(int j = 0; j < COLS; j++)
			board[i][j] = 0;

	spawnNum();
}

void printBoard(int maxDigits) {

    CLS;

	int colorSet[10] = {GRAY, WHITE, YELLOW, CYAN, GREEN, RED};

	setColor(WHITE);
	printf("DIFFICULTY: ");
	if(difficulty == EASY) {

		setColor(GREEN);
		printf("EASY\n");
	}
	else {

		setColor(RED);
		printf("HARD\n");
	}
	setColor(WHITE);
    printf("High Score: %d\nScore: %d", highScore, score);
    printf("\n\n");

    for(int i = 0; i < ROWS; i++) {

        for(int j = 0; j < COLS; j++) {

			if(!j)
				printf("\t\t  ");

            for(int k = 0; k < maxDigits - boardDigits[i][j] + 1; k++) {

                printf(" ");
            }

			if(!board[i][j]) {

				setColor(colorSet[0]);
			}
			else {

				setColor(colorSet[boardDigits[i][j]]);
			}
            printf("%d", board[i][j]);
        }
        printf("\n");
    }
	resetColor();
}

void copyBoard() {

    static int maxDigits = 1;

    for(int i = 0; i < ROWS; i++) {

        for(int j = 0; j < COLS; j++) {

            boardCopy[i][j] = board[i][j];
        }
    }
}

int parseInput(char input) {

    //Move Up with Up Arrow or 'W'
    if(input == 72 || input == 'w' || input == 'W') {

        transposeBoard();
        move(0);            //Passing 0 to move Up (-ve direction)
        transposeBoard();
    }
    //Move Down with Down Arrow or 'S'
    else if(input == 80 || input == 's' || input == 'S') {

        transposeBoard();
        move(1);            //Passing 1 to move Down (+ve direction)
        transposeBoard();
    }
    //Move Left with Left Arrow or 'A'
    else if(input == 75 || input == 'a' || input == 'A') {

        move(0);            //Passing 0 to move Left (-ve direction)
    }
    //Move Right with Right Arrow or 'D'
    else if(input == 77 || input == 'd' || input == 'D') {

        move(1);            //Passing 1 to move Right (+ve direction)
    }

    else if(input == 'z' || input == 'Z') {

		saveGameData(0);
        return 1;
    }

	else if(input == 'x' || input == 'X') {

        saveGameData(0);
    }

	else if(input == 'r' || input == 'R') {

		printf("\bCONFIRM RESET OF BOARD? [Press Enter/Return key for 'yes' (Avoid Using Arrow Keys)]\n\n> ");
		if (getch() == 13) {

			for(int i = 0; i < ROWS; i++) {

				for(int j = 0; j < COLS; j++) {

					board[i][j] = 0;
				}
			}
			assignBoardDigits(1);
			highScore = (highScore < score) ? score : highScore;
			score = 0;
			board[0][0] = 2;
			saveGameData(0);
			board[0][0] = 0;
		}
		else {

			printf("Confirmation Canceled\n\n>  ");
		}
	}

	return 0;
}

int boardIsChanged() {

    for(int i = 0; i < ROWS; i++) {

        for(int j = 0; j < COLS; j++) {

            if(board[i][j] != boardCopy[i][j]) {

                return 1;
            }
        }
    }

    return 0;
}

void transposeBoard() {

    for(int i = 0; i < ROWS; i++) {

        for(int j = i + 1; j < COLS; j++) {

            int temp = board[i][j];
            board[i][j] = board[j][i];
            board[j][i] = temp;
        }
    }
}

void move(int dir) {

    int temp, i, j, k;

    //Move all numbers towards Right Side of the board...
    if(dir) {

        for(i = 0; i < ROWS; i++) {

            for(j = COLS - 2; j >= 0; j--) {

                if(board[i][j]) {

                    temp = board[i][j];
                    for(k = j + 1; !board[i][k] && k < COLS; k++);
                    board[i][j] = 0;
                    board[i][k - 1] = temp;
                }
            }
        }
    }
    //Move all numbers towards Left Side of the board...
    else {

        for(i = 0; i < ROWS; i++) {

            for(j = 1; j < COLS; j++) {

                if(board[i][j]) {

                    temp = board[i][j];
                    for(k = j - 1; !board[i][k] && k >= 0; k--);
                    board[i][j] = 0;
                    board[i][k + 1] = temp;
                }
            }
        }
    }

    if(!addedOnce) {

        addedOnce = 1;
        add(dir);
    }

    addedOnce = 0;
}

void add(int dir) {

    int i, j;

    if(dir) {

        for(i = 0; i < ROWS; i++) {

            for(j = COLS - 1; j > 0; j--) {

                if(board[i][j] == board[i][j - 1]) {

                    score += board[i][j] *= 2;
                    board[i][j - 1] = 0;
                    j--;
                }
            }
        }
    }
    else {

        for(i = 0; i < ROWS; i++) {

            for(j = 0; j < COLS - 1; j++) {

                if(board[i][j] == board[i][j + 1]) {

                    score += board[i][j] *= 2;
                    board[i][j + 1] = 0;
                    j++;
                }
            }
        }
    }

    move(dir);
}

void spawnNum() {

    if(difficulty == EASY) {

		for(int i = 0; i < ROWS; i++) {

	        for(int j = 0; j < COLS; j++) {

	            if(!board[i][j]) {

	                board[i][j] = 2;
	                return;
	            }
	        }
	    }
	}
	else {

		int freeSpaces = 0;

		for(int i = 0; i < ROWS; i++) {

	        for(int j = 0; j < COLS; j++) {

	            if(!board[i][j]) {

	                freeSpaces++;
	            }
	        }
	    }

		srand(time(0));
		int randomPos = getRandomPos(freeSpaces);
		for(int i = 0; i < ROWS; i++) {

	        for(int j = 0; j < COLS; j++) {

	            if(!board[i][j]) {

	                randomPos--;
					if(!randomPos) {

						board[i][j] = 2;
						return;
					}
	            }
	        }
	    }
	}
}

int assignBoardDigits(int reset) {

    static int maxDigits = 1;

	if(reset) {

		maxDigits = 1;
	}

    for(int i = 0; i < ROWS; i++) {

        for(int j = 0; j < COLS; j++) {

            boardDigits[i][j] = 1;
            int num = board[i][j];
            while(num/10) {

                num /= 10;
                boardDigits[i][j]++;
            }

            maxDigits = boardDigits[i][j] > maxDigits ? boardDigits[i][j] : maxDigits;
        }
    }

    return maxDigits;
}

int gameOver() {

    int rowPairsFound = checkForPairs();

    transposeBoard();
    int colPairsFound = checkForPairs();
    transposeBoard();

    return rowPairsFound || colPairsFound;
}

int checkForPairs() {

    for(int i = 0; i < ROWS; i++) {

        for(int j = 0; j < COLS - 1; j++) {

            if(!board[i][j] || board[i][j] == board[i][j - 1]) {

                return 0;
            }
        }
    }

    return 1;
}


/*
    TEST CASES

    2 128 64 2
    16 4 8 16
    2 0 4 8
    0 0 0 0

    //Turning Right is a Problem... And Causes gameOver() to return true...

    2 128 32 8
    8 16 64 2
    2 8 8 2
    0 0 0 2
*/

/*
        W               72
    A   S   D       75  80  77
*/
