#include <stdio.h>
#include <stdlib.h>

int **read_matrix(int n){
    int rows[n];
    int **matrix= (int**)malloc(sizeof (int*) *n); 

    //allocating memory for matrix 
    for(int i=0; i < n; i++){
        matrix[i]= (int *)malloc(sizeof (int*) * n);

        // scan in and store input row in matrix
        for (int j = 0; j < n; j++) {
            scanf("%d", &rows[j]);
            matrix[i][j]= rows[j];
        }
    }
    return matrix;
}

//function to print matrices
void printMatrix(int **matrix, int n){
   
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void maxmin(int **m,int n){
    int max=m[0][0], min=m[0][0],i,j;

    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {   
            if(m[i][j]>max)
                max= m[i][j];

            if(m[i][j]<min)
                min= m[i][j];
        }
    }
    printf("\n\tGreatest no. is :  %d\n",max);
    printf("\n\tSmallest no. is :  %d\n",min);
}

int main(){
    int n, r, a; 
   
   // scan in n and restaurant information 
    scanf("%d %d", &n, &r); 
    int **restaurants= read_matrix(n);

    maxmin(restaurants, n);

    return 0;
}