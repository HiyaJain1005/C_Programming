#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 6  // Number of nodes in the graph

// Graph adjacency matrix (distances between nodes)
int graph[MAX_NODES][MAX_NODES] = {
    {0, 4, 2, 0, 0, 0},
    {4, 0, 0, 5, 10, 0},
    {2, 0, 0, 3, 0, 0},
    {0, 5, 3, 0, 4, 2},
    {0, 10, 0, 4, 0, 6},
    {0, 0, 0, 2, 6, 0}
};

// Heuristic values (estimated distance to goal "F")
int heuristic[MAX_NODES] = {10, 8, 6, 4, 2, 0};

// Node names for easy reference
char nodes[MAX_NODES] = {'A', 'B', 'C', 'D', 'E', 'F'};

// Find the index of a node from its name
int getNodeIndex(char node) {
    for (int i = 0; i < MAX_NODES; i++) {
        if (nodes[i] == node) return i;
    }
    return -1;  // Return -1 if node not found
}

// A* Search Algorithm
void astar(char start, char goal) {
    int startIdx = getNodeIndex(start);
    int goalIdx = getNodeIndex(goal);

    if (startIdx == -1 || goalIdx == -1) {
        printf("❌ Invalid start or goal node.\n");
        return;
    }

    int g[MAX_NODES], f[MAX_NODES], parent[MAX_NODES];
    int visited[MAX_NODES] = {0};

    // Initialize cost arrays
    for (int i = 0; i < MAX_NODES; i++) {
        g[i] = INT_MAX;
        f[i] = INT_MAX;
        parent[i] = -1;
    }

    g[startIdx] = 0;
    f[startIdx] = heuristic[startIdx];

    while (1) {
        int minF = INT_MAX, current = -1;

        // Find the node with the smallest f-score
        for (int i = 0; i < MAX_NODES; i++) {
            if (!visited[i] && f[i] < minF) {
                minF = f[i];
                current = i;
            }
        }

        if (current == -1) {
            printf("❌ No path found.\n");
            return;
        }

        if (current == goalIdx) {
            // Path found, reconstruct path
            printf("\n✅ Shortest Route Found:\n");
            int path[MAX_NODES], pathLen = 0, node = goalIdx;
            while (node != -1) {
                path[pathLen++] = node;
                node = parent[node];
            }

            // Print path
            for (int i = pathLen - 1; i >= 0; i--) {
                printf("%c", nodes[path[i]]);
                if (i > 0) printf(" → ");
            }

            printf("\nTotal Distance: %d km\n", g[goalIdx]);
            return;
        }

        visited[current] = 1;

        // Explore neighbors
        for (int neighbor = 0; neighbor < MAX_NODES; neighbor++) {
            if (graph[current][neighbor] > 0 && !visited[neighbor]) {
                int tempG = g[current] + graph[current][neighbor];

                if (tempG < g[neighbor]) {
                    g[neighbor] = tempG;
                    f[neighbor] = g[neighbor] + heuristic[neighbor];
                    parent[neighbor] = current;
                }
            }
        }
    }
}

int main() {
    char start = 'A', goal = 'F';
    astar(start, goal);
    return 0;
}
