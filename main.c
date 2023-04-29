#include <stdio.h>
#include <stdlib.h>

// Prototype
int isWinCondition(int *gameboard);


// Returns 1 if win condition, -1 if no win possible, and 0 if neither
int turn(int *player, int *gameboard, int *filledSpots) {
    int move = -1;

    while (1) {
        printf("Pick a number 1 thru 9:\n");
        scanf("%d", &move);
        if ((move < 1) || (move > 9)) continue;

        if (gameboard[move - 1] != 0) {
            printf("Spot already taken... pick again:\n");
            continue;
        }

        break;
    }

    gameboard[move - 1] = *player;
    *filledSpots += 1;

    if ((!isWinCondition(gameboard)) && (*filledSpots == 9)) {
        return -1; // Stalemate
    } else if (isWinCondition(gameboard)) {
        return 1; // Win condition met
    } else return 0; // Keep playing...
}

int isWinCondition(int *gameboard) {

    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (gameboard[i] && (gameboard[i] == gameboard [i + 1]) && (gameboard[i + 1] == gameboard[i + 2])) {
            return 1;
        }
    }

    // Check columns
    for (int i = 0; i < 9; i++) {
        if (gameboard[i] && (gameboard[i] == gameboard [i + 3]) && (gameboard[i + 3] == gameboard[i + 6])) {
                return 1;
        }
    }

    // Check diagonals
    if (gameboard[0] && (gameboard[0] == gameboard [4]) && (gameboard[4] == gameboard[8])) {
        return 1;
    }
    if (gameboard[2] && (gameboard[2] == gameboard [4]) && (gameboard[4] == gameboard[6])) {
        return 1;
    }

    return 0;
}

// Maps 0 to space, 1 to X, and 2 to O
char numToLetter(int num) {
    if (num == 0) {
        return ' ';
    } else if (num == 1) {
        return 'X';
    } else if (num == 2) {
        return 'O';
    }
}

void printBoard(int *gameboard) {
    int *p;
    p = gameboard;

    printf("======================================\n");

    printf("%c | %c | %c\t\t 1 2 3\n", numToLetter(*p), numToLetter(*(p + 1)), numToLetter(*(p + 2)));
    printf("----------\n");
    printf("%c | %c | %c\t\t 4 5 6\n", numToLetter(*(p+3)), numToLetter(*(p + 4)), numToLetter(*(p + 5)));
    printf("----------\n");
    printf("%c | %c | %c\t\t 7 8 9\n", numToLetter(*(p+6)), numToLetter(*(p + 7)), numToLetter(*(p + 8)));

    printf("======================================\n");
}

int main()
{
    int player1 = 1;
    int player2 = 2;

    int filledSpots = 0;

    int winCondition = 0;

    // Calloc ensures allocated memory is zeroed out...
    int *gameboard = calloc(9, sizeof(int));
    if (gameboard == NULL)
    {
        printf("Memory allocation failed. Exiting...");
        exit(-1);
    }

    while (1) {
        /*
            The following code makes the (hopefully correct) assumption
            that player 1 cannot win on player 2's turn and vice-versa.
        */

       // Player 1's Turn
        printBoard(gameboard);
        printf("Player 1's Turn (X): \n");
        int status = turn(&player1, gameboard, &filledSpots);
        if (status == 1)
        {
            winCondition = 1;
            break;
        } else if (status == -1) {
            printf("\n\n\n");
            printBoard(gameboard);
            printf("Stalemate...\n");
            break;
        }

        // Player 2's Turn
        printBoard(gameboard);
        printf("Player 2's Turn (O): \n");
        status = turn(&player2, gameboard, &filledSpots);
        if (status == 1)
        {
            winCondition = 2;
            break;
        } else if (status == -1) {
            printf("\n\n\n");
            printBoard(gameboard);
            printf("Stalemate...\n");
            break;
        }


    }

    if (winCondition > 0) {
        printf("\n\n\n");
        printBoard(gameboard);
        printf("Player %d wins!", winCondition);
    }

    return 0;
}