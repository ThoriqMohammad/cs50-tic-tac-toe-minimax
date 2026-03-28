/*
 * CS50 Final Project: Tic-Tac-Toe with Minimax AI
 *
 * This project is inspired by and based on the Tic-Tac-Toe game
 * from GeeksforGeeks (URL: https://www.geeksforgeeks.org/c/tic-tac-toe-game-in-c/).
 * It has been significantly modified to include:
 * - Random first player selection
 * - Replay functionality with persistent scoring
 * - Corrected minimax implementation for computer as 'O'
 * 
 * Original GeeksforGeeks article published: [October 4, 2023]
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COMPUTER 1
#define HUMAN    2
#define SIDE     3

#define COMPUTER_MOVE 'O'
#define HUMAN_MOVE    'X'

// Structure to hold a board position
struct Move {
    int row, col;
};

// Symbols used inside the minimax function (lowercase)
char player = 'x';      // human = maximizer
char opponent = 'o';    // computer = minimizer

// ---------- Minimax implementation ----------

bool isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}

int evaluate(char b[3][3]) {
    // rows
    for (int row = 0; row < 3; row++) {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
            if (b[row][0] == player) return +10;
            if (b[row][0] == opponent) return -10;
        }
    }
    // columns
    for (int col = 0; col < 3; col++) {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == player) return +10;
            if (b[0][col] == opponent) return -10;
        }
    }
    // diagonals
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == player) return +10;
        if (b[0][0] == opponent) return -10;
    }
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == player) return +10;
        if (b[0][2] == opponent) return -10;
    }
    return 0;
}

int minimax(char board[3][3], int depth, bool isMax) {
    int score = evaluate(board);
    if (score == 10) return score;
    if (score == -10) return score;
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = player;
                    int val = minimax(board, depth + 1, !isMax);
                    if (val > best) best = val;
                    board[i][j] = '_';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = opponent;
                    int val = minimax(board, depth + 1, !isMax);
                    if (val < best) best = val;
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

struct Move bestMoveForMaximizer(char board[3][3]) {
    int bestVal = -1000;
    struct Move bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = player;
                int moveVal = minimax(board, 0, false);
                board[i][j] = '_';
                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

struct Move bestMoveForMinimizer(char board[3][3]) {
    int bestVal = 1000;
    struct Move bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = opponent;
                int moveVal = minimax(board, 0, true);
                board[i][j] = '_';
                if (moveVal < bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

// ---------- Game display and helpers ----------

void showBoard(char board[][SIDE]) {
    printf("\n\n");
    printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t--------------\n");
    printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t--------------\n");
    printf("\t\t\t %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}

void showInstructions() {
    printf("\t\t\t Tic-Tac-Toe\n\n");
    printf("Choose a cell numbered from 1 to 9 as below and play\n\n");
    printf("\t\t\t 1 | 2 | 3 \n");
    printf("\t\t\t--------------\n");
    printf("\t\t\t 4 | 5 | 6 \n");
    printf("\t\t\t--------------\n");
    printf("\t\t\t 7 | 8 | 9 \n\n");
    printf("--------------------------------------------\n\n");
}

void initialise(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++)
        for (int j = 0; j < SIDE; j++)
            board[i][j] = ' ';
}

int rowCrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++)
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            board[i][0] != ' ')
            return 1;
    return 0;
}

int columnCrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++)
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i] &&
            board[0][i] != ' ')
            return 1;
    return 0;
}

int diagonalCrossed(char board[][SIDE]) {
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '))
        return 1;
    return 0;
}

int gameOver(char board[][SIDE]) {
    return rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board);
}

// ---------- One round of play, returns winner ----------
// Returns: HUMAN if human wins, COMPUTER if computer wins, 0 for draw
int playTicTacToe(int whoseTurn) {
    char board[SIDE][SIDE];
    initialise(board);
    showInstructions();

    int moveIndex = 0, x, y;

    while (moveIndex < SIDE * SIDE) {
        if (whoseTurn == COMPUTER) {
            // Convert board to minimax format
            char temp[3][3];
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == HUMAN_MOVE)    temp[i][j] = 'x';
                    else if (board[i][j] == COMPUTER_MOVE) temp[i][j] = 'o';
                    else                               temp[i][j] = '_';
                }

            struct Move thisMove = bestMoveForMinimizer(temp);
            x = thisMove.row;
            y = thisMove.col;

            board[x][y] = COMPUTER_MOVE;
            printf("Computer places %c at row %d, column %d\n", COMPUTER_MOVE, x, y);
            showBoard(board);
            moveIndex++;

            // Check if computer won
            if (gameOver(board)) {
                return COMPUTER;
            }
            whoseTurn = HUMAN;
        }
        else { // HUMAN's turn
            int move;
            printf("Your move (1-9): ");
            scanf("%d", &move);
            if (move < 1 || move > 9) {
                printf("Invalid cell number. Try again.\n");
                continue;
            }
            x = (move - 1) / SIDE;
            y = (move - 1) % SIDE;
            if (board[x][y] != ' ') {
                printf("Cell %d is already occupied. Try again.\n", move);
                continue;
            }
            board[x][y] = HUMAN_MOVE;
            showBoard(board);
            moveIndex++;

            // Check if human won
            if (gameOver(board)) {
                return HUMAN;
            }
            whoseTurn = COMPUTER;
        }
    }

    // If we exit loop, board is full with no winner → draw
    return 0;
}

//---------- Main program with replay and scoring ----------

int main() {
    srand(time(NULL));   // seed random number generator

    int humanWins = 0, computerWins = 0, draws = 0;
    char playAgain;

    do {
        // Randomly choose who starts
        int starter = (rand() % 2 == 0) ? COMPUTER : HUMAN;
        printf("\n=== New Game ===\n");
        printf("Starting player: %s\n\n",
               (starter == HUMAN) ? "You (HUMAN)" : "Computer");

        int result = playTicTacToe(starter);

        // Update scores and display result
        if (result == HUMAN) {
            printf("*** You win! ***\n");
            humanWins++;
        } else if (result == COMPUTER) {
            printf("*** Computer wins! ***\n");
            computerWins++;
        } else {
            printf("*** It's a draw! ***\n");
            draws++;
        }

        // Show current scores
        printf("\nCurrent Scores:\n");
        printf("  You: %d\n", humanWins);
        printf("  Computer: %d\n", computerWins);
        printf("  Draws: %d\n", draws);

        // Ask to play again
        printf("\nDo you want to play again? (y/n): ");
        // Clear input buffer
        while (getchar() != '\n');
        scanf("%c", &playAgain);
        // Convert to lowercase
        if (playAgain >= 'A' && playAgain <= 'Z')
            playAgain += 'a' - 'A';
    } while (playAgain == 'y');

    // Final scores
    printf("\n=== Final Scores ===\n");
    printf("  You: %d\n", humanWins);
    printf("  Computer: %d\n", computerWins);
    printf("  Draws: %d\n", draws);
    printf("\nThanks for playing! Goodbye.\n");

    return 0;
}
