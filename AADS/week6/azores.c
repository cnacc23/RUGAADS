#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

// returns the minimum of two numbers 
int min(int a, int b) {
    return (a < b) ? a : b;
}

// returns whether or not node is a leaf
bool is_leaf(int i, int size) {
    int left_index= 2 * i + 1;
    int right_index= 2 * i + 2;

    if (left_index >= size && right_index >= size) {
        return true;
    } else {
        return false;
    }
}

// recursively calculates the sum of nodes that contain cameras 
int camera_costs(int* tree_array, int size, int current_node) {
    
    //base case: current node is a non-existing intersection
    if (tree_array[current_node] == -1) {
        return 0;
    }

    // base case: current node is a leaf
    if (is_leaf(current_node, size)) {
        return tree_array[current_node];
    }

    // calculate indices of children 
    int left_index = 2 * current_node + 1;
    int right_index = 2 * current_node + 2;

    // cost of placing camera at current node 
    int total_cost = tree_array[current_node];

    // recursively calculate children's costs (including their children)
    int left_child_cost= camera_costs(tree_array, size, left_index);
    int right_child_cost= camera_costs(tree_array, size, right_index);

    // if child is not a leaf, sum the minimum costs of child + descendants 
    if (!is_leaf(left_index, size)) {
        total_cost += left_child_cost;
    }

    if (!is_leaf(right_index, size)) {
        total_cost += right_child_cost;
    }

    // sum the childrens cost 
    int children_cost = left_child_cost + right_child_cost;


    // return  minimum cost between current node and the sum of its children 
    return min(total_cost, children_cost);
}



int main() {
    int n;
    scanf("%d", &n);

    // total nodes in tree
    int total_nodes = (pow(2, n)) - 1;

    // implement tree as an array
    int *tree_array = (int *)malloc(total_nodes * sizeof(int));

    int level_cap;
    int treeIdx = 0;

    for (int i = 0; i < n; i++) {
        // set capacity of nodes at each level
        level_cap = pow(2, i) + treeIdx;

        // populate tree array
        for (int j = treeIdx; j < level_cap; j++) {
            int data;
            scanf("%d", &data);
            tree_array[j] = data;

            // increase index each time an element is added
            treeIdx++;
        }
    }

    int min_cost = camera_costs(tree_array, total_nodes, 0); // start from root 
    printf("%d\n", min_cost);

    free(tree_array);
    return 0;
}