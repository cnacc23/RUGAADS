
#include <stdio.h>
 
// Function to swap two elements
void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
 
// Partition the array using the last element as the pivot
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int wall = (low - 1);
  
    for (int i = low; i <= high - 1; i++) {
        
        // if element is less than pivot, move to the "left" of the array 
        if (arr[i] < pivot) {
            
            //increment wall then swap element with element at wall index
            wall++;
            swap(&arr[wall], &arr[i]);
        }
    }
    swap(&arr[wall + 1], &arr[high]);

    //return pivot's index in array
    return (wall + 1);
}
 
// Function to implement Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {

        //obtain index of where pivot goes in concatenated list 
        int wall = partition(arr, low, high);
        
        // sort each partition recursively 
        quickSort(arr, low, wall - 1);
        quickSort(arr, wall + 1, high);
    }
}
 
// Function to print the array
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d\n ", arr[i]);
    
}
 
// Driver program
int main() {
    int arr[] = { 3, 10, 11, 6, 1, 7, 16, 2, 5, 4, 13, 8 };
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Unsorted array:\n");
    printArray(arr,n);

    quickSort(arr, 0, n - 1);
    
    printf("Sorted array: \n");
    printArray(arr, n);
    
    return 0;
}