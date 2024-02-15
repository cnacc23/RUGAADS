#include <stdio.h>
#include <stdlib.h>

int main(){

    int s, p; 
    scanf("%d %d", &s, &p); 

    int* penguins= (int*)malloc(p * sizeof(int)); 
    for(int i=0; i<p; i++){
        scanf("%d", &penguins[i]); 
    }

   // calculate total volume of penguins 
   int sum= 0; 
   for(int i=0; i<p; i++){
        sum += penguins[i];
    }

    int m= sum /s;

    // extra basket needed if division has a remainder 
    if(s*m < sum){
        m= m+1; 
    } 

    printf("%d\n", m);
    free(penguins);

    return 0; 
}