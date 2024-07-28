#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpace();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main() {
    char winner;
    char response;

    do {
        winner = ' ';
        resetBoard();
        
        while (winner == ' ' && checkFreeSpace() != 0) {
            printBoard();
            
            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpace() == 0) {
                break;
            }
            
            computerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpace() == 0) {
                break;
            }
        }
        
        printBoard();
        printWinner(winner);
        
        printf("Would you like to play again? (Y/N): ");
        while ((getchar()) != '\n'); // clear input buffer
        scanf("%c", &response);
        response = toupper(response);
        
    } while (response == 'Y');
    
    printf("Thanks for playing!\n");
    return 0;
}

void resetBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int checkFreeSpace() {
    int freeSpaces = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                freeSpaces++;
            }
        }
    }
    return freeSpaces;
}

void playerMove() {
    int x, y;
    
    do {
        printf("Enter row number (1-3): ");
        scanf("%d", &x);
        x--;
        
        printf("Enter column number (1-3): ");
        scanf("%d", &y);
        y--;
        
        if (x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != ' ') {
            printf("Invalid move! Please try again.\n");
        } else {
            board[x][y] = PLAYER;
            break;
        }
    } while (1);
}

void computerMove() {
    srand(time(0));
    int x, y;
    
    if (checkFreeSpace() > 0) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');
        
        board[x][y] = COMPUTER;
    }
}

char checkWinner() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return board[i][0];
        }
    }
    
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return board[0][i];
        }
    }
    
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return board[0][2];
    }
    
    return ' ';
}

void printWinner(char winner) {
    if (winner == PLAYER) {
        printf("You win!\n");
    } else if (winner == COMPUTER) {
        printf("Computer wins!\n");
    } else {
        printf("It's a tie!\n");
    }
}
