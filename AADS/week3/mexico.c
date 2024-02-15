#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100000

int n, k; 

typedef struct node {
    int dish;
    int freq;
    struct node *next;
} Node;

Node *hash_table[MAX_SIZE] = {NULL};


int hash_function(int dish) {
   
    return dish % MAX_SIZE;
}


//function to insert a new dish-freq pair 
void insert(int dish) {
    int h = hash_function(dish);

    Node *add = hash_table[h];

    // check to see whether or not dish of node being inserted
    // already has a place in hash table 
    while (add != NULL) {

        // if it does, update its frequency
        if (add->dish == dish) {
            add->freq++;
            return;
        }
        add = add->next;
    }

    // if there is no prev occurenc, add new node to hashtable 
    Node *new = (Node*)malloc(sizeof(Node));

    new->dish = dish;
    //frequency initialized to 1
    new->freq = 1; 
    new->next = hash_table[h];
    hash_table[h] = new;

}


  // function to get dish-value pairs from hashtable 
void get_pairs(Node **dish_value_pairs, int *pairs) {
  
    // pointer to array (keeps track of number of pairs extracted)
    *pairs = 0;

    for (int i = 0; i < MAX_SIZE; i++) {

        //get dish-value pair at index i
        Node *tmp = hash_table[i];

        while (tmp != NULL) {

            //add to array at pointer index 
            dish_value_pairs[*pairs] = tmp;
            (*pairs)++;
            tmp = tmp->next;
        }
    }
}

 // comparison function for qsort
int compare(const void *a, const void *b) {
    Node **pa = (Node**)a;
    Node **pb = (Node**)b;
    return (*pb)->freq - (*pa)->freq;
}

// function to sort dishes by their frequency 
int* sort_by_frequency() {
    Node *pairs[MAX_SIZE];
    int num_pairs = 0;

    get_pairs(pairs, &num_pairs);

    // sort pairs by frequency 
    qsort(pairs, num_pairs, sizeof(Node*), compare);

    // copy the first k elements of the sorted array to kth
    int *kth = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        kth[i] = pairs[i]->dish;
    }

    return kth; 
}


int main() {
    
    scanf("%d %d", &n, &k); 
    

    int *dishes= (int*)malloc(n * sizeof(int));

    //scan in dishes and store each dish in a hashtable with its frequency 
    for (int i = 0; i < n; i++) {
        scanf("%d", &dishes[i]);
        insert(dishes[i]);
    }

    int *most_frequent= sort_by_frequency();
    
    // sort most frequent pairs in ascending order 
    for(int i=0; i<k; i++){
        for(int j=i+1; j<k; j++){
            if(most_frequent[i] > most_frequent[j]){

                //swap elements if first element (at index i) > second element
                int tmp= most_frequent[i];
                most_frequent[i]= most_frequent[j];
                most_frequent[j]= tmp;
            }
        }
    }

    // print kth most frequent pairs 
    for(int i=0; i<k; i++){
        if(i == k-1){
            printf("%d", most_frequent[i]);
        }else{
            printf("%d ", most_frequent[i]);
        }
    }
    printf("\n");

    free(dishes);
    free(most_frequent);

    return 0;
}