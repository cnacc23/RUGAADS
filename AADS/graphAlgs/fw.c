// Floyd-Warshall Algorithm in C

#include <stdio.h>

// defining the number of vertices
#define nV 6

#define INF 999

void printMatrix(int matrix[][nV]);

// Implementing floyd warshall algorithm
void floydWarshall(int graph[][nV]) {
  int matrix[nV][nV], i, j, k;

  for (i = 0; i < nV; i++)
    for (j = 0; j < nV; j++)
      matrix[i][j] = graph[i][j];
     
  // Adding vertices individually
  for (k = 0; k < nV; k++) {
    printf("D(%d):\n", k);
    printMatrix(matrix);
    printf("\n");
    for (i = 0; i < nV; i++) {
      for (j = 0; j < nV; j++) {
        if (matrix[i][k] + matrix[k][j] < matrix[i][j])
          matrix[i][j] = matrix[i][k] + matrix[k][j];
      }
    }
  }
  printMatrix(matrix);
}

void printMatrix(int matrix[][nV]) {
  for (int i = 0; i < nV; i++) {
    for (int j = 0; j < nV; j++) {
      if (matrix[i][j] == INF)
        printf("%4s", "INF");
      else
        printf("%4d", matrix[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int graph[nV][nV] = 
  {{0, 8, INF, INF, 7, 3},
    {8, 0, 2, 6,INF, INF},
    {INF, 2, 0, 3, INF, 1},
    {INF, 6, 3, 0, 8, 5},
		{7, INF, INF, 8, 0, 2},
		{3, INF, 1, 5, 2, 0}};

  floydWarshall(graph);
}
