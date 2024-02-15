#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int n;

// finds sccs in graph 
void find_scc(int currNode, int disc[], int low[], int stack[], bool stackItem[], int graph[n][n]) {
    
    // keep track of node discovery order 
    static int order= 0;

    // low is the earliest reachable node 

    //discovery and low initialized to same order 
    disc[currNode]= low[currNode]= ++order;

    //push current node onto stack and mark as discovered
    stack[++stack[0]]= currNode;
    stackItem[currNode]= true;

    // iterate through nodes adjacent to current Node 
    for (int v = 0; v<n; v++) {

        // if edge between current node, check if v has been visited 
        if (graph[currNode][v]) {

            // if not, find v's lowest linke 
            if (disc[v] == -1) {
                find_scc(v, disc, low, stack, stackItem, graph);
                low[currNode] = min(low[currNode], low[v]);

            //if v has been visited, update currentNode's low link 
            } else if (stackItem[v])
                low[currNode] = min(low[currNode], disc[v]);
        }
    }

    // current node is root of an scc 
    if (low[currNode] == disc[currNode]) {
        int popped= 0;

        //nodes belonging to scc 
        do {
            popped= stack[stack[0]--];
            printf("%d ", popped);
            stackItem[popped]= false;
        } while (popped != currNode);
        printf("\n");
    }
}

//tarjan's alg to find sccs
void tarjan(int graph[n][n]) {

    //initialize disk and low values for inp adj matrix 
    int disc[n], low[n];
    bool stackItem[n];
    int stack[n + 1];
    stack[0] = 0;

    for (int i = 0; i < n; i++) {
        disc[i] = low[i]= -1;
        stackItem[i]= false;
    }

    // iterate through matrix for each node
    for (int i= 0; i<n; i++) {
        if (disc[i] == -1)
            find_scc(i, disc, low, stack, stackItem, graph);
    }
}
