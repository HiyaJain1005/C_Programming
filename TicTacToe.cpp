#include <iostream>
using namespace std;

char board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };

// Function to print the board
void printBoard() {
    cout << "-------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

// Function to check if the game is over
int checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') return (board[i][0] == 'X') ? 10 : -10;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') return (board[0][i] == 'X') ? 10 : -10;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') return (board[0][0] == 'X') ? 10 : -10;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') return (board[0][2] == 'X') ? 10 : -10;
    return 0;
}

// Function to check if any moves are left
bool isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return true;
    return false;
}

// Minimax function
int minimax(bool isMax) {
    int score = checkWin();
    if (score == 10) return 10;
    if (score == -10) return -10;
    if (!isMovesLeft()) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = max(best, minimax(false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = min(best, minimax(true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// Function to find the best move
void findBestMove() {
    int bestVal = -1000, row = -1, col = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'X';
                int moveVal = minimax(false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    row = i;
                    col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    board[row][col] = 'X';
}

// Main function
int main() {
    cout << "Tic-Tac-Toe AI using Minimax!\n";
    printBoard();

    while (true) {
        int row, col;
        cout << "Enter your move (row and column 0-2): ";
        cin >> row >> col;
        if (board[row][col] != ' ') {
            cout << "Invalid move! Try again.\n";
            continue;
        }
        board[row][col] = 'O';
        if (checkWin() == -10) {
            printBoard();
            cout << "You Win!\n";
            break;
        }
        if (!isMovesLeft()) {
            printBoard();
            cout << "It's a draw!\n";
            break;
        }

        findBestMove();
        printBoard();
        if (checkWin() == 10) {
            cout << "AI Wins!\n";
            break;
        }
        if (!isMovesLeft()) {
            cout << "It's a draw!\n";
            break;
        }
    }
    return 0;
}
