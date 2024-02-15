#include <math.h>
#include <stdio.h>

void sort(int arr[], int n){
    int i, j, key;

    for(i=1; i < n; i++){
        key= arr[i];
        j= i-1;     //tmp 
    
        //compare tmp w prev element 
        while(j >= 0 && arr[j] > key){
            arr[j+1]= arr[j]; // shift elements forward by one if needed 
            j= j-1;
        }
        arr[j+1]= key;  //insert element 
    }

}

void printArray(int arr[], int n){
    
    for(int i= 0; i < n; i++)
        printf("%d\n", arr[i]);
    printf("\n");
}

int main(){
    int arr[]= {12, 11, 13, 5, 6};
    int n= sizeof(arr)/sizeof(arr[0]);

    sort(arr, n); 
    printArray(arr, n);

    return 0;
}