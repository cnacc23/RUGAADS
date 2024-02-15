#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "spain.h"

int **read_matrix(int n){
   int rows[n];
   int **matrix= (int**)malloc(sizeof (int*) *n); 

    //allocating memory for matrix 
    for(int i=0; i < n; i++){
        matrix[i]= (int *)malloc(sizeof (int*) * n);
    }

    for(int i=0; i < n; i++){
        
        // scan in and store input row in matrix
        for (int j = 0; j < n; j++) {
            scanf("%d", &rows[j]);
            matrix[i][j]= rows[j];
        }
    }
    return matrix;
}


void free_matrix(int **matrix, int n){
    //free matrix

    for(int i = 0; i < n; i++){
        int *currPtr= matrix[i]; 
        free(currPtr);
    }
}

int *flatten(int **matrix, int low, int high){

    //define new arrays //divide these values in 2 for two diff arrays 
    int total_rows= high - low +1;
    int total_cols= high - low +1;
    int *newArr= (int *)malloc(sizeof(int)*total_rows*total_cols);
 
    int n= 0;

    //2d matrix to 1d array 
    for(int i= low; i <= high; i++){
        for(int j= low; j <= high; j ++){
            newArr[n]= matrix[i][j];
            n++;
        }
    }
    return newArr; 
}


int spain(int **matrix, int n, int k) {
    k++; // correct for 1 based indexing
    int min = matrix[0][0];
    int max = matrix[n-1][n-1];
    int mid= floor((min + max)/2);
    int half= (n*n)/2;
    int kth;

   // printf("min %d max %d\n", min, max);

    //base cases 
    if(k == 1){
        kth= min;

    } else if(k == n){
        kth= max;
    }

    int *newMatrix= flatten(matrix, 1, n); 

// make a new 1d array and then index the kth element from there


    if(mid < half){
        // go through first min-half elements 
        for(int i = 0; i < half; i++){
    
            int index= k - half;
            if(i == index){
                kth= newMatrix[index];

            }
        }
        
    } else if (mid > half){
        //go through second half-max elements
        for(int i= half; i < n; i++){
            int index= k-half; 
            
            if(i == index){               
            kth= newMatrix[index]; 

            }
        }

    }
    return kth; // kth smallest element
}

