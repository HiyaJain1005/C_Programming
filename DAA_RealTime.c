#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define ROWS 3
#define COLS 4

// Function to find the optimal parking cost dynamically
int findMinParkingCost(int cost[ROWS][COLS], int occupied[ROWS][COLS]) {
    int dp[ROWS][COLS];

    // Initialize DP table
    for (int i = 0; i < ROWS; i++) {
        if (occupied[i][0])  // If the slot is occupied, set cost to high value
            dp[i][0] = INT_MAX;
        else
            dp[i][0] = cost[i][0];
    }

    // Fill DP table dynamically
    for (int j = 1; j < COLS; j++) {
        for (int i = 0; i < ROWS; i++) {
            if (occupied[i][j]) {  // Skip occupied slots
                dp[i][j] = INT_MAX;
                continue;
            }

            int minCost = INT_MAX;

            if (dp[i][j - 1] != INT_MAX)
                minCost = dp[i][j - 1]; // Left slot

            if (i > 0 && dp[i - 1][j - 1] != INT_MAX)
                minCost = (dp[i - 1][j - 1] < minCost) ? dp[i - 1][j - 1] : minCost; // Upper diagonal slot

            if (i < ROWS - 1 && dp[i + 1][j - 1] != INT_MAX)
                minCost = (dp[i + 1][j - 1] < minCost) ? dp[i + 1][j - 1] : minCost; // Lower diagonal slot

            dp[i][j] = (minCost == INT_MAX) ? INT_MAX : cost[i][j] + minCost;
        }
    }

    // Find the minimum cost from the last column
    int minParkingCost = INT_MAX;
    for (int i = 0; i < ROWS; i++) {
        if (dp[i][COLS - 1] < minParkingCost) {
            minParkingCost = dp[i][COLS - 1];
        }
    }

    return (minParkingCost == INT_MAX) ? -1 : minParkingCost; // -1 means no available path
}

// Function to display the parking lot
void displayParking(int occupied[ROWS][COLS]) {
    printf("Parking Slot Availability (0 = Free, 1 = Occupied):\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", occupied[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int parkingCost[ROWS][COLS] = {
        {4, 7, 8, 6},
        {6, 3, 9, 2},
        {5, 8, 7, 4}
    };

    int occupied[ROWS][COLS];

    // Initialize all slots as available (0)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            occupied[i][j] = 0;
        }
    }

    // Ask the user to input the availability of slots
    int row, col, status;
    while (1) {
        printf("\nEnter the row (0-%d), column (0-%d) and status (0 = Free, 1 = Occupied) for a slot (or -1 to quit):\n", ROWS-1, COLS-1);
        printf("Row: ");
        scanf("%d", &row);
        if (row == -1) break;
        printf("Column: ");
        scanf("%d", &col);
        printf("Status (0 = Free, 1 = Occupied): ");
        scanf("%d", &status);
        
        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && (status == 0 || status == 1)) {
            occupied[row][col] = status;
        } else {
            printf("Invalid input. Try again.\n");
        }
    }

    // Display the updated parking availability
    displayParking(occupied);

    // Compute the optimal parking cost dynamically
    int minCost = findMinParkingCost(parkingCost, occupied);

    if (minCost == -1)
        printf("No available parking slot found.\n");
    else
        printf("Minimum Parking Cost (Considering Occupied Slots): %d\n", minCost);

    return 0;
}
