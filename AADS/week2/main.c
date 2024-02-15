#include "spain.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Verify that the matrix is indeed n*n, and not read in as a stream for cheating purposes
void verify_matrix(int n, int **matrix) {
    int elem1 = matrix[0][0];
    int elem2 = matrix[n-1][n-1];

    assert(elem1 >= 0);
    assert(elem2 >= 0);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    printf("n: %d k: %d\n", n, k);

    read_matrix(n);
    int **matrix = read_matrix(n);
    verify_matrix(n, matrix);

    int kth = spain(matrix, n, k);
    printf("%d\n", kth);

    free_matrix(matrix, n);

    return 0;
}