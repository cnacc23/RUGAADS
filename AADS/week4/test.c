#include <stdio.h>
#include <stdlib.h>

// struct for bag 
typedef struct {
    int capacity;
    int currentVolume;
    int* penguins;
    int numPenguins;
} Bag;


void initializeBag(Bag* bag, int capacity) {
    bag->capacity = capacity;
    bag->currentVolume = 0;
    bag->penguins = NULL;
    bag->numPenguins = 0;
}


void addPenguinToBag(Bag* bag, int penguinVolume) {
    bag->currentVolume += penguinVolume;
    bag->numPenguins++;
    bag->penguins = realloc(bag->penguins, bag->numPenguins * sizeof(int));
    bag->penguins[bag->numPenguins - 1] = penguinVolume;
}

// for qsort 
int cmpfunc(const void* a, const void* b) {
    int valueA = *(int*)a;
    int valueB = *(int*)b;

    if (valueA < valueB) {
        return 1;
    } else if (valueA > valueB) {
        return -1;
    }

    return 0;
}


int minimizeBags(int bagVolume, int* penguinVolumes, int numPenguins) {

    
    Bag* bags = malloc(numPenguins * sizeof(Bag));
    for (int i = 0; i < numPenguins; i++) {
        initializeBag(&bags[i], bagVolume);
    }

    for (int i = 0; i < numPenguins; i++) {
        int penguinVolume = penguinVolumes[i];
        int bagIndex = -1;

        // check if the penguin can fit in any existing bag
        for (int j = 0; j < numPenguins; j++) {
            if (bags[j].currentVolume + penguinVolume <= bags[j].capacity) {
                bagIndex = j;
                break;
            }
        }

        // if the penguin cannot fit in any existing bag, create a new bag
        if (bagIndex == -1) {
            bagIndex = i;
        }

        // add the penguin to the selected bag
        addPenguinToBag(&bags[bagIndex], penguinVolume);
    }

   // sum number of bags 
    int numBags = 0;
    for (int i = 0; i < numPenguins; i++) {
        if (bags[i].numPenguins > 0) {
            numBags++;
        }
    }

    
    for (int i = 0; i < numPenguins; i++) {
        free(bags[i].penguins);
    }
    free(bags);

    return numBags;
}

int main() {
    int s, p; 
    scanf("%d %d", &s, &p); 

    int* penguins= (int*)malloc(p * sizeof(int)); 
    for(int i=0; i<p; i++){
        scanf("%d", &penguins[i]); 
    }

    qsort(penguins, p, sizeof(int*), cmpfunc);
    int numBags = minimizeBags(s, penguins, p);

    printf("Number of bags required: %d\n", numBags);

    return 0;
}
