#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define MAX_V 17576

int num_vertices;

// queue struct 
typedef struct{
    int head, tail, size;
    unsigned cap;
    int *arr;
}Queue; 


// function to initialize a queue 
Queue* createQueue(unsigned cap){
    Queue* queue= (Queue*)malloc(sizeof(Queue));
    queue->cap= cap;
 
    queue->tail= cap - 1;
    queue->arr = (int*)malloc(
        queue->cap * sizeof(int));
    return queue;
}
 
 
// function to tell if queue is empty
int isEmpty(Queue* queue){
    return (queue->size == 0);
}
 
// function to add an item to queue 
void enqueue(Queue* queue, int node){

    // check if queue is full 
    if (queue->size == queue->cap)
        return;

    // inc queue tail 
    queue->tail= (queue->tail + 1) % queue->cap;

    // add item to array
    queue->arr[queue->tail]= node;

    // inc queue size 
    queue->size= queue->size + 1;
}
 
// function to dequeue an item from queue
int dequeue(Queue* queue){

    // check if queue empty first 
    if (isEmpty(queue))
        return INT_MIN;
    int node= queue->arr[queue->head];

    // inc head to node after current head 
    queue->head= (queue->head + 1) % queue->cap;

    // dec queue size 
    queue->size= queue->size - 1;
    return node;
}
 
// function that returns head of queue
int queue_head(Queue* queue){

    if (isEmpty(queue))
        return INT_MIN;
    return queue->arr[queue->head];
}
 
// function to return minimum of two numbers 
int min(int a, int b){
    return (a < b) ? a : b;
}
 
// breadth first search to find all existing augmentation paths 
bool bfs(int rGraph[num_vertices][num_vertices], int s, int t, int parent[], Queue q){
    
    // array to keep track of vertices visited
    bool visited[num_vertices];

    //initialize to 0
    memset(visited, 0, sizeof(visited));
 
    // enqueue source vertex to queue 
    // queue ensures order of vertexes visited is breadth first 
    enqueue(&q, s);
    visited[s] = true;
    parent[s] = -1;
 

    while (!isEmpty(&q)) {

        // dequeue current vertex of interest 
        int u= queue_head(&q);
        dequeue(&q);
 
        for (int v = 0; v < num_vertices; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
        
                // if direct connection to sink then no need to bfs
                if (v == t) {

                    // update parent array 
                    parent[v]= u;
                    return true;
                }
                enqueue(&q, v);
                parent[v]= u;
                visited[v]= true;
            }
        }
    }
 
    // no more augmentation paths exist 
    return false;
}
 
// uses ford-fulkerson method to return max flow of graph
int max_flow(int** graph, int s, int t, Queue q){
    int u, v;
 
    // residual graph
    int res_graph[num_vertices][num_vertices]; 
                 
    // copy over graph (capacities are the same right now)             
    for (u= 0; u<num_vertices; u++)
        for (v= 0; v<num_vertices; v++)
            res_graph[u][v] = graph[u][v];
 

    // for augmentation path
    int parent[num_vertices];
 
    // initialize all flow to 0
    int max_flow = 0; 
 
    // while augmentation paths exist 
    while(bfs(res_graph, s, t, parent, q)) {

        int path_flow= INT_MAX;
        // find minimum residual capacity of the edges included in augmentation path
        for (v= t; v != s; v= parent[v]) {
            u= parent[v];

            // take minimum of existing path and residual graph 
            path_flow = min(path_flow, res_graph[u][v]);
        }
 
        // update residual capacities of the edges and
        // reverse edges along the path in residual graph 
        for (v= t; v != s; v= parent[v]) {
            u = parent[v];

            //add the new capacities 
            res_graph[v][u]+= path_flow;

            //subtract the reverse edge
            res_graph[u][v]-= path_flow;
            
        }

        // update overall max flow with recent augmentation path 
        max_flow+= path_flow;
    }
 
    // Return the overall flow
    return max_flow;
}


int main() {
    int num_edges;
    printf("Enter the number of vertices: ");
    scanf("%d", &num_vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &num_edges);

    printf("number of vertices: %d\nnumber of edges: %d\n", num_vertices, num_edges);

    // initialize queue
    Queue *q= createQueue(num_vertices);

    // initialize the graph's adjacency matrix 
    int** adj= (int**)calloc(num_vertices, sizeof(int*));

    // set rows to 0
    for(int i=0; i<num_vertices+1; i++){
        adj[i]= (int*)calloc(num_vertices, sizeof(int*));

    }
    adj[0][0]= 0; 
    adj[0][1]= 0;

    printf("Initialized adj matrix:\n");
    for (int i=0; i < num_vertices; i++){
        for(int j=0; j < num_vertices; j++){
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Read in edges of the graph
    printf("Enter the source, sink and edge weight:\n");
    for (int i= 0; i <num_edges; i++) {
        int source, destination, capacity;
        scanf("%d %d %d", &source, &destination, &capacity);
        adj[source][destination]= capacity;
        
    }
    printf("\n");


    printf("Updated adj matrix:\n");
    for (int i=0; i <num_vertices; i++){
        for(int j=0; j <num_vertices; j++){
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int source, sink;
    printf("Enter the source vertex: ");
    scanf("%d", &source);
    printf("Enter the sink vertex: ");
    scanf("%d", &sink);

    int maxFlow = max_flow(adj, source, sink, *q);
    printf("Maximum flow: %d\n", maxFlow);

    return 0;
}
