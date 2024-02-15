
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 8

//structure to store coordinates 
struct Coordinates{
    int data[2]; 
};


// A structure to represent a queue
struct Queue {
    struct Coordinates coords[SIZE]; 
	int head, tail, size;
	unsigned capacity;
	int* array;
};

//function to create a queue 
struct Queue* createQueue(){
	struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
	q->head= 0;
    q->tail= 0;
    q->size= 0;

	return q;
}

//function to tell if queue is free 
int isFull(struct Queue* q){
	return (((q->tail+1) % SIZE) == q->head);
}

//function to enqueue 
void enqueue(struct Queue* q, int *coordinates)
{
	if (isFull(q))return;

	q->coords[q->tail].data[0]= coordinates[0]; 
    q->coords[q->tail].data[1]= coordinates[1]; 
	q->tail= (q->tail + 1) % SIZE; //8= SIZE 
    q->size= q->size + 2;
}


// function to dequeue
struct Coordinates dequeue(struct Queue* q){
    struct Coordinates first;

    first= q->coords[q->head]; 
    q->head = (q->head + 1) % SIZE;

    return first; 
}

void printQueue(struct Queue* q){
  int tmp = q->head;
  printf("Queue Contains: ");

  int flag = 0;
  
  while(tmp != q->tail){
    if (flag) printf(", ");
    flag = 1;
    
    printf("(%d,%d)", q->coords[tmp].data[0], q->coords[tmp].data[1]);

    tmp = (tmp + 1) % SIZE;
  }
  printf("\n");
}


int main(){

    int c[2] = {2,3};
    int d[2] = {4,5};
    struct Queue* q = createQueue();
    enqueue(q, c);
    enqueue(q, d);
 
    printQueue(q);

   
    struct Coordinates data;
    
    data = dequeue(q);
    printf("first pair: (%d,%d)\n", data.data[0], data.data[1]);
    

return 0; 

}
