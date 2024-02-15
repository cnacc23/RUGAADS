#include <stdio.h>
#include <stdlib.h>


int cmpfunc(const void *a, const void *b){
    //pointers to inner arrays 
    int *x = *(int **)a;
    int *y = *(int **)b;

    //comparing difference in second element of inner array 
    return x[1] - y[1];
}

/*function to merge sorted arrays in ascending order of skill level while 
maintaining alternating 0/1 order */
void merge(int** arr0, int** arr1, int size0, int size1, int** merged) {
    int idx0 = 0, idx1 = 0;
    int currIdx = 0;
    int currMerge = 1;

    // figure out which array to start merging w based on smallest second element 

    //start with 0 array
    if (arr0[0][1] <= arr1[0][1]) {
        merged[currIdx]= arr0[idx0];
        idx0++;
        currMerge= 0;

    //start with 1 array     
    } else {
        merged[currIdx]= arr1[idx1];
        idx1++;
        currMerge= 1;  
    }
    currIdx++;
    currMerge = !currMerge; //update to maintain alternating order 

    //merge rest of elements 
    while (idx0 < size0 && idx1 < size1) {
        
        //merging from 0
        if(currMerge == 0) {
            merged[currIdx] = arr0[idx0];
            idx0++;

        //merging from 1    
        } else {
            merged[currIdx] = arr1[idx1];
            idx1++;
        }

        currIdx++;
        currMerge = !currMerge; //update 
    }

    // if index != size for either array, there are leftover elements 

   //merge leftover elements from 0 array
    while (idx0 < size0) {
        merged[currIdx] = arr0[idx0];
        idx0++;
        currIdx++;
    }

    //merge leftover elements from 1 array 
    while (idx1 < size1) {
        merged[currIdx] = arr1[idx1];
        idx1++;
        currIdx++;
    }
}


int main(){

    int n, c; 
    scanf("%d %d", &n, &c); 

    int **lines= malloc(n * sizeof(lines)); 
    for(int i=0; i<n; i++){

        //allocate memory for each line 
        lines[i]= malloc(3 * sizeof(int));

        for(int j=0; j<3; j++){
            scanf("%d", &lines[i][j]); 
        }
    }

    //separate arrays depending on their t value 
    int **zeros= malloc(n* sizeof(*zeros));
    int **ones= malloc(n* sizeof(*ones));
    int idx0= 0; 
    int idx1= 0;

    for(int i=0; i<n; i++){
        if(lines[i][0] == 0){
            // append to zeros if first element of inner array is 0
            zeros[idx0]= lines[i];
            idx0++; 
        } else if(lines[i][0] == 1){
            // append to ones if first element of inner array is 1
            ones[idx1]= lines[i];
            idx1++; 
        }
    }    

    //reallocate seperate array memories
    zeros= realloc(zeros, idx0 * sizeof(*zeros));
    ones= realloc(ones, idx1 * sizeof(*ones));


    //sort array based on ascending difficulty level (d); 
    qsort(zeros, idx0, sizeof(int*), cmpfunc);
    qsort(ones, idx1, sizeof(int*), cmpfunc);

    
    // merge arrays so that new array is sorted in order of ascending 
    // difficulty level but also alternating between 0s and 1s
    int** merged = malloc((idx0+idx1) * sizeof(*merged));
    merge(zeros, ones, idx0, idx1, merged);

    int stolen= 0; 
    int curr_skill= c;
    int t= -1; 

    // determine how many generators can be stolen based on difficulty level 
    for(int i=0; i<n; i++){
        if(merged[i][1] <= curr_skill && merged[i][0] != t){
            stolen++;
            curr_skill+= merged[i][2]; 
            t= merged[i][0];
        }
    }
  
    printf("%d\n", stolen);
    

    //free memory
    for(int i=0; i<n; i++){
        free(lines[i]);
    }

    free(lines);
    free(zeros);
    free(ones);
    free(merged);

    return 0; 
}