#include <stdio.h>
#include <stdlib.h>

struct wq{

    int station; 
    float quality; 
};

int main(){
    int n; 
    scanf("%d", &n);

    struct wq *water_stations= malloc(n * sizeof(struct wq*));

    for (int i=0; i<n; i++) {
        char s;
    
        // store station number and water quality only 
        scanf(" %c%d%f", &s, &water_stations[i].station, &water_stations[i].quality);
    }


    free(water_stations);
    
    return 0; 
}