#include <stdbool.h>
#include <stdio.h>

#define MAX_NODES 100

void dfs(int adjacencyMatrix[][MAX_NODES], int node, bool visited[], int parent[], int n, int* cycleNode) {
    visited[node] = true;

    for (int i = 0; i < n; i++) {
        if (adjacencyMatrix[node][i] != 0) {
            if (!visited[i]) {
                parent[i] = node;
                dfs(adjacencyMatrix, i, visited, parent, n, cycleNode);
            } else if (parent[node] != i) {
                // Cycle detected
                *cycleNode = i;
                return;
            }
        }
    }
}

int findNodeInCycle(int adjacencyMatrix[][MAX_NODES], int n, int* cycleNode) {
    bool visited[n];
    int parent[n];

    for (int i = 0; i < n; i++) {
        visited[i] = false;
        parent[i] = -1;
    }

    *cycleNode = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(adjacencyMatrix, i, visited, parent, n, cycleNode);
            if (*cycleNode != -1) {
                return i;
            }
        }
    }

    return -1; // No cycle found
}

int main() {
    int adjacencyMatrix[MAX_NODES][MAX_NODES] = {
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 0, 1},
        {1, 0, 0, 0, 0}
    };

    int n = 5; // Number of nodes

    int cycleNode;
    int startNode = findNodeInCycle(adjacencyMatrix, n, &cycleNode);

    if (startNode != -1) {
        printf("Node in cycle with both incoming and outgoing edges: %d\n", cycleNode);
    } else {
        printf("No cycle found\n");
    }

    return 0;
}

