#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>


// struct for airport vertices
typedef struct __attribute__((packed)) {
	char name[4]; // name of the node
	int  nCons;   // number of outgoing edges
	int  conOff;  // outg. edges are indexed by range g.edges[conOff, conOff + nCons)
} Vert;

//struct for edges
typedef struct {
	int dest;
	int weight;
} Edge;

//struct for vertex 
typedef struct {
	size_t V; // how many verts
	size_t E; // how many edges
	Vert *verts; // vertex data
	Edge *edges; // edge data, ascending origin vertex, monotonically increasing destination vertex
} Graph;

typedef struct {
	int src; int dst; int wt;
} FullEdge;

int compareEdges(const void *a, const void *b) {
	FullEdge *edgeA = (FullEdge *)a;
	FullEdge *edgeB = (FullEdge *)b;
	if (edgeA->src != edgeB->src) {
		return edgeA->src - edgeB->src;
	} else {
		return edgeA->dst - edgeB->dst;
	}
}

static inline
void setEdges(Graph *g, size_t n, FullEdge edges[n]){
	// sort the edges array by src, then dst, ascending
	qsort(edges, n, sizeof(FullEdge), compareEdges);

	Edge *e = calloc(n, sizeof *e);

	size_t V = g->V;
	size_t v = 0;
	for (size_t i=0; i<n; ++i){
		assert(edges[i].src < V);
		assert(edges[i].dst < V);
		while(edges[i].src > v){
			g->verts[v+1].conOff = i;
			v++;
		}
		e[i].dest   = edges[i].dst;
		e[i].weight = edges[i].wt;
		g->verts[v].nCons++;
	}

	if (g->edges) free(g->edges);

	g->edges = e;
	g->E     = n;
}

static inline
void addEdge(Graph *g, int src, int dst, int weight){
	const size_t V      = g->V;
	assert(src < V);
	assert(dst < V);
	const size_t oldE   = g->E;
	const size_t newE   = oldE+1;
	Edge *const  old    = g->edges;
	Edge *const  new    = calloc(newE, sizeof *new);
	const size_t conOff = g->verts[src].conOff;
	const size_t oldCnt = g->verts[src].nCons;
	const size_t newCnt = oldCnt + 1;

	// write increased edge and connection count
	g->E = newE;
	g->verts[src].nCons = newCnt;

	// adjust the offsets following after this slot
	for(int i=src+1; i<V; i++){
		g->verts[i].conOff++;
	}

	// copy edges before this slot
	memcpy(new, old, conOff*sizeof *old);
	
	// in this slot, copy and insert sorted
	if (oldCnt){
		size_t left = 0;
		size_t right = oldCnt - 1;
		size_t mid = 0;

		while (left <= right) {
			mid = left + (right - left) / 2;
			assert(mid < V);
			if (dst == old[mid].dest)
				break;
			else if (dst < old[mid].dest)
				right = mid - 1;
			else
				left = mid + 1;
		}

		size_t insertionIndex = (dst < old[mid].dest) ? mid : mid + 1;

		memcpy(conOff+new, conOff+old, insertionIndex * sizeof*old);
		new[conOff+insertionIndex].dest = dst;
		new[conOff+insertionIndex].weight = weight;
		memcpy(&new[conOff+insertionIndex + 1], &old[conOff+insertionIndex], (oldCnt - insertionIndex) * sizeof*old);
	} else {
		new[conOff].dest = dst;
		new[conOff].weight = weight;
	}

	// copy edges after this slot
	const size_t nAfter = oldE-(conOff+oldCnt);
	memcpy(new+conOff+newCnt, old+conOff+oldCnt, nAfter*sizeof *old);

	free(old);
	g->edges = new;
}

static inline
int addVert(Graph *g, char name[4]){
	int oldV = g->V;
	g->verts = realloc(g->verts, (++g->V)*sizeof *g->verts);
	g->verts[oldV] = (Vert){
		.name[0] = name[0],
		.name[1] = name[1],
		.name[2] = name[2],
		.name[3] = name[3],
		.conOff = oldV
			? g->verts[oldV-1].conOff +
			  g->verts[oldV-1].nCons
			: 0,
		.nCons = 0
	};
	return oldV;
}

static inline
int *weightOf(Graph g, int src, int dst){
	size_t nCons = g.verts[src].nCons;
	size_t conOff = g.verts[src].conOff;
	static int zero = 0;
	if (nCons){
#ifdef WEIGHTOF_FLATWALK
		// Iterate the array left to right
		for (Edge *e = g.edges+conOff; e < g.edges+conOff+nCons; e++){
			int d = e->dest;
			if (d == dst){
				return &e->weight;
			} else if (d > dst){
				return &zero;
			}
		}
#else
		// Binary search while loop g.edges from [conOff] to [conOff + nCons] to find dst
		Edge *lo = g.edges+conOff;
		Edge *hi = g.edges+conOff+nCons-1;
		while (lo <= hi) {
			//fprintf(stderr,"seeking in [%lu, %lu)\n",lo-g.edges,hi-g.edges);
			Edge *mid = lo + (hi - lo) / 2;
			if (mid->dest == dst) {
				return &mid->weight; // Found the destination vertex
			} else if (mid->dest < dst) {
				lo = mid + 1; // Search in the right half
			} else {
				hi = mid - 1; // Search in the left half
			}
		}
#endif
	}
	return &zero;
}

static inline
void printGraph(Graph g){
	for (size_t src=0; src<g.V; src++){
		size_t nCons  = g.verts[src].nCons;
		size_t conOff = g.verts[src].conOff;
		for (size_t con=conOff; con<conOff+nCons; con++){
			int dst = g.edges[con].dest;
			int wgt = g.edges[con].weight;
			printf("%s -> %s (%d)\n", g.verts[src].name, g.verts[dst].name, wgt);
		}
	}
}

static inline
void debugGraph(Graph g){
	size_t V = g.V;
	size_t E = g.E;
	for (size_t v=0; v<V; v++){
		Vert vt = g.verts[v];
		printf("%lu (%s) has %d cons starting at %d\n", v, vt.name, vt.nCons, vt.conOff);
	}
	for (size_t e=0; e<E; e++){
		Edge ed = g.edges[e];
		printf("[%d, %d]%s", ed.dest, ed.weight, e+1==E?"\n":", ");
	}
}

static inline
void freeGraph(Graph g){
	free(g.verts);
	free(g.edges);
}

static inline
Graph copyGraph(Graph g){
	Graph h = g;
	h.verts = calloc(h.V, sizeof *h.verts);
	memcpy(h.verts, g.verts, h.V*sizeof *h.verts);
	h.edges = calloc(h.E, sizeof *h.edges);
	memcpy(h.edges, g.edges, h.E*sizeof *h.edges);
	return h;
}

static inline
void tarjan(Graph g, int lut[g.V]) {
	int  *index   = calloc(g.V, sizeof *index);
	int  *lowlink = calloc(g.V, sizeof *lowlink);
	int  *stack   = calloc(g.V, sizeof *stack);
	char *stacked = calloc(g.V, sizeof *stacked);
	int stacktop  = 0;
	int counter   = 0;
	int sccId     = 0;

	void cleanup(void){
		free(index);
		free(lowlink);
		free(stack);
		free(stacked);
	}

	int stronglyConnect(int node){
		index[node]   = counter;
		lowlink[node] = counter;
		counter      += 1;

		stack[stacktop] = node;
		stacktop       += 1;
		stacked[node]   = 1;
		
		int nCons = g.verts[node].nCons;
		int conOff = g.verts[node].conOff;
		for(size_t i=0; i<nCons; i++){
			int neighbour = g.edges[conOff+i].dest;

			if (index[neighbour] == 0) {
				if (!stronglyConnect(neighbour)) {
					return 0;
				}
				if (lowlink[neighbour] < lowlink[node]) {
					lowlink[node] = lowlink[neighbour];
				}
			} else if (stacked[neighbour]) {
				if (index[neighbour] < lowlink[node]) {
					lowlink[node] = index[neighbour];
				}
			}
		}
		if (lowlink[node] == index[node]) {
			// Finished mapping a strongly connected component
			//printf("SCC %d: ", sccId);
			int tmp;
			do {
				tmp = stack[--stacktop];
				stacked[tmp] = 0;
				lut[tmp] = sccId;
			//	printf("%s ", g.verts[tmp].name);
			} while (tmp != node);
			sccId++;
			//puts("");
		}
		return 1;
	}
	
	for(size_t node=0; node<g.V; node++){
		if (index[node] == 0 && !stronglyConnect(node)) {
			cleanup();
			return;
		}
	}
	cleanup();
}

static inline
int min(int a, int b){
	return a<b?a:b;
}

static inline
bool find_augmenting_path(Graph g, Graph residual, int source, int sink, int parent[g.V]){
	bool visited[g.V];
	memset(visited, 0, g.V*sizeof*visited);

	int stack[g.V];
	int top = -1;

	stack[++top] = source;
	visited[source] = true;

	while (top >= 0){
		int current_vertex = stack[top--];

		for (int neighbor = 0; neighbor < g.V; neighbor++){
			if (!visited[neighbor] && *weightOf(residual,current_vertex,neighbor) > 0){
				stack[++top] = neighbor;
				visited[neighbor] = true;
				parent[neighbor] = current_vertex;

				if (neighbor == sink){
					// Found an augmenting path
					return true;
				}
			}
		}
	}

	// No augmenting path found
	return false;
}

static inline
int ford_fulkerson(Graph g, int source, int sink){
	Graph residual = copyGraph(g);

	int max_flow = 0;

	int parent[g.V];
	while (find_augmenting_path(g, residual, source, sink, parent)){
		// Find the minimum residual capacity along the augmenting path
		int min_capacity = INT_MAX;
		for (int v = sink; v != source; v = parent[v]){
			int u = parent[v];
			min_capacity = min(*weightOf(residual, u, v), min_capacity);
		}

		// Update the residual capacities and reverse edges
		for (int v = sink; v != source; v = parent[v]){
			int u = parent[v];
			*weightOf(residual, u, v) -= min_capacity;
			*weightOf(residual, v, u) += min_capacity;
		}

		// Add the flow of the augmenting path to the maximum flow
		max_flow += min_capacity;
	}

	freeGraph(residual);

	return max_flow;
}

int main(void){
	char  names[][4] = {"EWR","HND","ICN","JFK","LGA","BGI","ORD","DSM","SFO","SAN","EYW","LHR","CDG","DEL","DOH","SIN","BUD","TLV"};
	int   source     = 4;
	char *sourcename = names[source];

	Graph g = {0};
	g.V     = sizeof(names)/sizeof(names[0]);
	g.verts = calloc(g.V, sizeof *g.verts);
	for (int i=0; i<g.V; i++)
		memcpy(g.verts[i].name, names[i], 3);
	
	FullEdge e[] = {
		{0,1,3184},
		{1,2,5710},
		{2,3,8858},
		{3,4,7422},
		{5,4,552},
		{6,5,7529},
		{7,6,5144},
		{8,7,1699},
		{8,9,3289},
		{9,10,5303},
		{10,11,3268},
		{11,8,1711},
		{12,13,2719},
		{13,14,9158},
		{14,15,5657},
		{15,12,2665}};
	size_t nE     = (sizeof e)/(sizeof e[0]);
	setEdges(&g, nE, e);
	// printGraph(g);

	int scc[g.V];
	tarjan(g, scc);

	// find which nodes have a predescessor from another SCC
	// O(E)
	char *hasPred = calloc(g.V, sizeof *hasPred);
	for (int i = 0; i < g.V; i++) {
		int off = g.verts[i].conOff;
		int ncons = g.verts[i].nCons;
		for (int j = 0; j < ncons; j++) {
			int to = g.edges[j+off].dest;
			if (scc[i] != scc[to]){
				hasPred[to] = 1;
			}
		}
	}

	// O(V)
	char *visitedSCC = calloc(g.V, sizeof *visitedSCC);
	visitedSCC[scc[source]] = 1; // ignore source
	for (int i = 0; i < g.V; i++) {
		if (visitedSCC[scc[i]]){
			continue;
		}
		visitedSCC[scc[i]] = 1;
		// fmt.Printf("%d:%s scc:%d pred:%t\n", node, codes[node], sccLUT[node], hasPred[node]);
		if (!hasPred[i]){
			// add edge
			printf("add %s->%s\n", sourcename, g.verts[i].name);
			addEdge(&g, source, i, 66666);
		}
	}

	// now add all sinks to one supersink
	int sinks[] = {0,1,2,3,5,6,7,9,14,16,17};
	int sink = addVert(&g, "###");
	for (int i = 0; i < sizeof(sinks)/sizeof(sinks[0]); ++i){
		printf("add %s->%s\n", g.verts[sinks[i]].name, g.verts[sink].name);
		addEdge(&g, sinks[i], sink, 99999);
	}

	free(visitedSCC);
	free(hasPred);

	// printGraph(g);
	int maxf = ford_fulkerson(g, source, sink);

	freeGraph(g);
}

// Implements our dijkstras algo
static inline
int dijkstras(Graph g, int from, int dist[g.V], int prev[g.V]) {
	int n = g.V;
	// int dist[n];  // Stores shortest distance from from to each node
	// int prev[n];  // Stores previous node in shortest path

	// Initialize all distances to a very high value and all previous nodes to -1
	for (int i = 0; i < n; i++) {
		dist[i] = INT_MAX;
		prev[i] = -1;
	}
	dist[from] = 0;  // Set distance of from to 0

	bool visited[n];               // Keep track of visited nodes
	for (int i = 0; i < g.V; i++) {  // initializes array
		visited[i] = 0;
	}

	for (int i = 0; i < n - 1; i++) {
		int curr_node = -1;
		int curr_dist = INT_MAX;
		// Find the unvisited node with the shortest distance from from
		for (int j = 0; j < n; j++) {
			if (!visited[j] && dist[j] < curr_dist) {
				curr_node = j;
				curr_dist = dist[j];
			}
		}
		if (curr_node == -1) {
			break;  // All remaining nodes are unreachable
		}
		visited[curr_node] = true;
		printf("visited %s\n", g.verts[curr_node].name);

		// Update distances to adjacent nodes
		for (int j = 0; j < n; j++) {
			int w = *weightOf(g,curr_node,j);
			if (w) {
				// If there is an edge from curr_node to j
				// Calculate alternate distance
				int alt_dist = dist[curr_node] + w;
				if (alt_dist < dist[j]) {
					// If alternate distance is shorter than current distance
					dist[j] = alt_dist;  // Update distance
					prev[j] = curr_node; // Update previous node
				}
			}
		}
	}

	// int to;
	// // Print shortest path and distance
	// int path_length = 0;
	// int path[n];
	// int curr_node = to;
	// while (curr_node != -1) {
	//   path[path_length] = curr_node;
	//   path_length++;
	//   curr_node = prev[curr_node];
	// }
	// if (dist[to] != INT_MAX) {
	//   for (int i = 0; i < path_length; i++) {
	//     printf("%s\n", g.verts[path[i]].name);
	//   }
	//   printf("%d\n", dist[to]);
	// } else {
	//   printf("UNREACHABLE\n");
	// }
	// return dist[to];
}

static inline
void insertSorted(int x, int n, int old[n], int new[n+1]) {
	int left = 0;
	int right = n - 1;
	int mid = 0;

	while (left <= right) {
		mid = left + (right - left) / 2;

		if (x == old[mid])
			break;
		else if (x < old[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}

	int insertionIndex = (x < old[mid]) ? mid : mid + 1;

	memcpy(new, old, insertionIndex * sizeof(int));
	new[insertionIndex] = x;
	memcpy(&new[insertionIndex + 1], &old[insertionIndex], (n - insertionIndex) * sizeof(int));
}
