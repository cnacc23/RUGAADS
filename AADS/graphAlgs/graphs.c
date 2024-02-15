#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Structure to represent the adjacency list
struct Graph {
    int numVertices;
    struct Node** adjLists;
};

// Function to create a new node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with 'n' vertices
struct Graph* createGraph(int n) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = n;

    graph->adjLists = (struct Node**)malloc(n * sizeof(struct Node*));

    int i;
    for (i = 0; i < n; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from source to destination
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add an edge from destination to source
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to connect two graphs
void connectGraphs(struct Graph* graph1, struct Graph* graph2) {
    int i;

    // Assuming the graphs have the same number of vertices
    for (i = 0; i < graph1->numVertices; i++) {
        // Find corresponding vertices in graph2 based on some matching criterion
        // Here, we assume that vertices in graph1 and graph2 are matched based on their indices
        int correspondingVertex = i;

        // Add an edge between the corresponding vertices in the two graphs
        addEdge(graph1, i, correspondingVertex);
    }
}

// Function to print the adjacency list representation of a graph
void printGraph(struct Graph* graph) {
    int i;
    for (i = 0; i < graph->numVertices; i++) {
        struct Node* temp = graph->adjLists[i];
        printf("Adjacency list of vertex %d\n", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int numVertices = 4;
    struct Graph* graph1 = createGraph(numVertices);
    struct Graph* graph2 = createGraph(numVertices);

    // Add edges to the first graph
    addEdge(graph1, 0, 1);
    addEdge(graph1, 1, 2);
    addEdge(graph1, 2, 3);
    addEdge(graph1, 3, 0);

    // Add edges to the second graph
    addEdge(graph2, 0, 3);
    addEdge(graph2, 3, 2);
    addEdge(graph2, 2, 1);
    addEdge(graph2, 1, 0);

    printf("Graph 1:\n");
    printGraph(graph1);

    printf("\nGraph 2:\n");
    printGraph(graph2);

    printf("\nConnecting Graphs...\n");
    connectGraphs(graph1, graph2);

    printf("\nMerged Graph:\n");
    printGraph(graph1);

    return 0;
}
