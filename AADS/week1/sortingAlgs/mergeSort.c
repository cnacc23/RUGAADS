/* C program for Merge Sort */
#include <stdio.h>
#include <stdlib.h>

// Merges two subarrays of arr[].
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int leftSize = m - l + 1;
	int rightSize = r - m;

	// create temp arrays 
	int left[leftSize], right[rightSize];

	// Copy data to temp arrays 
	for (i = 0; i < leftSize; i++)
		left[i] = arr[l + i];
	for (j = 0; j < rightSize; j++)
		right[j] = arr[m + 1 + j];

	// merge the temp arrays back into original array 
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	
    //compare elements of left array to right
    //add smaller element to merged array 
    while (i < leftSize && j < rightSize) {
		if (left[i] <= right[j]) {
			arr[k] = left[i];
			i++;
		}
		else {
			arr[k] = right[j];
			j++;
		}
		k++;
	}

	//to copy over remaining elements in left array
	while (i < leftSize) {
		arr[k] = left[i];
		i++;
		k++;
	}

	//to copy over remaining elements in right array
	while (j < rightSize) {
		arr[k] = right[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
	if (l < r) {
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l + (r - l) / 2;

		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

void printArray(int A[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

int main()
{
	int arr[] = { 12, 11, 13, 5, 6, 7 };
	int arr_size = sizeof(arr) / sizeof(arr[0]);

	printf("Given array is \n");
	printArray(arr, arr_size);

	mergeSort(arr, 0, arr_size - 1);

	printf("\nSorted array is \n");
	printArray(arr, arr_size);
	return 0;
}

  