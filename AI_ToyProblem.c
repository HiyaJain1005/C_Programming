#include <stdio.h>
#include <stdlib.h>

#define N 3
#define MAX_QUEUE 100000

// Goal state
int GOAL_STATE[N][N] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 0} };

// Moves: Up, Down, Left, Right
int moves[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

// Structure for a puzzle state
typedef struct {
    int board[N][N];
} Puzzle;

// Queue for BFS
Puzzle queue[MAX_QUEUE];
int front = 0, rear = 0;

// Enqueue function
void enqueue(Puzzle p) {
    if (rear < MAX_QUEUE) {
        queue[rear++] = p;
    }
}

// Dequeue function
Puzzle dequeue() {
    return queue[front++];
}

// Find empty tile position (0)
void findEmptyTile(int board[N][N], int *x, int *y) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] == 0) {
                *x = i;
                *y = j;
                return;
            }
}

// Check if the current board matches the goal
int isGoal(int board[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] != GOAL_STATE[i][j])
                return 0;
    return 1;
}

// Copy one board state to another
void copyBoard(int dest[N][N], int src[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dest[i][j] = src[i][j];
}

// Print board
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Solve the puzzle using BFS
void solve(int initial[N][N]) {
    Puzzle start;
    copyBoard(start.board, initial);
    enqueue(start);

    while (front < rear) {  // While queue is not empty
        Puzzle current = dequeue();
        printBoard(current.board);  // Print current step

        if (isGoal(current.board)) {
            printf("✅ Puzzle solved!\n");
            return;
        }

        int x, y;
        findEmptyTile(current.board, &x, &y);

        // Try moving the empty tile
        for (int i = 0; i < 4; i++) {
            int newX = x + moves[i][0], newY = y + moves[i][1];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                Puzzle next;
                copyBoard(next.board, current.board);
                next.board[x][y] = next.board[newX][newY];
                next.board[newX][newY] = 0;
                enqueue(next);
            }
        }
    }

    printf("❌ No solution found.\n");
}

int main() {
    int initial[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {0, 7, 8}
    };

    solve(initial);
    return 0;
}
