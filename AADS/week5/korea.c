#pragma GCC optimize("09")

// north korea
#include <stdatomic.h>

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

static inline
int max(int a, int b){
	return a>b?a:b;
}

static inline
int move(int from, int to){
	// return how many soldiers we would have
	// if we move from cell a to cell b
	if (to == 0) {
		// can't into water
		return 0;
	}
	return from+to-1;
}

int main(void) {
	int rows, cols;
	scanf("%d %d", &rows, &cols);

	int (*mat)[cols] = calloc(rows*cols, sizeof(0));
	// assert(mat != NULL);

	int (*row)[2] = calloc(2*cols, sizeof *row);
	assert(row != NULL);

	// assume position i,j
	// legal moves: j++ or i++
	// moving to a cell containing 0 is illegal
	// on move, add cell value-1 to n
	// maximize n
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++){
			scanf("%d", &row[1][j]);
			printf("% 3d ", row[1][j]);
		}
		if (i == 0){

		}
		for (int j=0; j<cols; j++){

			acc[j+1] = max(move(acc[j], acc[j+1]), move(row[j], acc[j+1]));
			printf("\t%3d ", acc[j+1]);
		}
		puts("");
	}

	free(row);
}
