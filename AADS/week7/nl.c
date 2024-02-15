#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include "maxFlow.c"
#include "tarjan.c"

//#include "api/AirFranceApi.h"
//#include "api/AirFranceExampleApi.cpp"

#define MAX_V 17576
int n, s;

// finds the index of a code in matrix 
int findIndex(char matrix[n][4], int n, char *code){
    int index= 0; 
    for(int i=0; i<n; i++){
        if(strcmp(matrix[i], code) == 0){
            index= i;
        }
    }
    return index;
}

// returns if a row is all 0s
bool rowZeros(int graph[n][n], int n, int nodeIdx){
    for(int i=0; i<n; i++){
        if(graph[nodeIdx][i] != 0){
            return false;
        }
    }
    return true;
}

//returns if a column is all 0s
bool colZeros(int graph[n][n], int n, int nodeIdx){
    for(int i=0; i<n; i++){
        if(graph[i][nodeIdx] != 0){
            return false;
        }
    }
    return true;

}

// returns how many edges must be added
int edgesToAdd(int graph[n][n], char airports[n][4], char edges[s][4], int n, int s, int srcIdx){

    int toAdd= 0; 
    int ind= 0;
    bool cycleNode= false;
    
    for(int i=0; i<n; i++){
        // if a node has no incoming or outgoing edges 
        if(rowZeros(graph, n, i) && colZeros(graph, n, i)){
            toAdd++; 
            strcpy(edges[ind], airports[i]);
            ind++;

        } 
        //if a node has no incoming edges only (and is not source )
        else if((!rowZeros(graph, n, i) && colZeros(graph, n, i)) &&  i != srcIdx){
            toAdd++;
            strcpy(edges[ind], airports[i]);
            ind++;
        }

        /*//if a node in a cycle 
        else if((!rowZeros(graph, n, i) && !colZeros(graph, n, i)) && !cycleNode){
            toAdd++; 
            cycleNode= true;
        }*/
    }
    

    return toAdd;
}

void updateGraph(int matrix[n][n], char airports[n][4], char newEdges[s*2][4], char edges[s][4], int n, int srcIdx){


    //  update adj matrix with API flow for each airport code in edges 
    // this connects the graphs 

    //find index for each start and end point 

    int start= 0;
    int end= 1; 

    //update adj matrix with API flow (this connects edges )

    for(int i=0; i<n; i++){

        int sinkIdx= findIndex(airports[i], n, edges[i]);

        //updating adj matrix
        matrix[srcIdx][i] = af_addConnection(airports[srcIdx], airports[sinkIdx]);

        //copy start and end airports to new array 
        strcpy(newEdges[start], srcIdx);
        strcpy(newEdges[end], edges[i]);
        start++, 
        end++;
    }

}


int main(){

    // n is number of total vertices 
    scanf("%d", &n);

    // scan in first batch of airports 
    char airports1[n][4];
    for(int i=0; i<n; i++){
        scanf("%s", airports1[i]);
    }

    // number of airports to calculate max flow 
    scanf("%d", &s);

    // scan in second batch of airports
    // calculate max flow to these airports 
    char airports2[s][4];
    for(int i=0; i<s; i++){
        scanf("%s", airports2[i]);
    }

    int t;
    scanf("%d", &t);


    // create adjacency matrix for graph and initialize all elements to 0
    int adj[n][n];
     for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            adj[i][j]= 0; 
        }
    }

    // scan in pre-determined flights 
    for(int i=0; i<t; i++){
        char f[4], to[4];
        int w;

        scanf("%s %s %d", f, to, &w);


        // find to and from airport indices 
        int fInd, toInd;
        for(int j=0; j<n; j++){
            if(strcmp(f, airports1[j]) == 0){
                fInd= j;
            }

            if(strcmp(to, airports1[j]) == 0){
                toInd= j;
            }
        }
        // add connections to adjacency matrix
        adj[fInd][toInd]+= w;
    }
    

    // scan in starting airport 
    char src[4];
    scanf("%s", src);

    // save source index 
    int srcIdx; 
    for(int i=0; i<n; i++){
        if(strcmp(airports1[i], src) == 0)
            srcIdx= i; 
    }

    // array to contain vertices we want to add an edge to
    char sinks[s][4];
    int numAdditions= edgesToAdd(adj, airports1, sinks, n, s, srcIdx);
    
    //array contains start and end vertices of new edges 
    char newEdges[s*2][4];
    updateGraph(adj, airports1, newEdges, sinks, n, srcIdx);


    // initialize queue for max flow
    Queue *q= createQueue(n);

    // calculate and sum max flow for each of the s airports in sinks 
    int maxFlow=0;
    for(int i=0; i<s; i++){
        maxFlow+= max_flow(adj, srcIdx, sinks[i], *q);
    }

    // print number of edges being added and airports they're being added between
    printf("%d\n", numAdditions);
    for(int i=0; i<s; i++){
        printf("%s %s\n", newEdges[i], newEdges[i+1]);
    }

    //print max flow
    printf("%d\n", maxFlow);
    return 0; 

}
