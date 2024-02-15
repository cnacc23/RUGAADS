#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_NODE 10000000

typedef struct Node {
    char name[MAX_NAME];
    struct Node* left;
    struct Node* right;
    struct Node* parent; 
    int depth;
} Node;

Node* create_node(const char* name) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strncpy(newNode->name, name, MAX_NAME);
    newNode->left= NULL;
    newNode->right= NULL;
    newNode->depth= 0;

    return newNode;
}

// function to search tree for a name 
Node *search_tree(Node *node, const char* name){

    // if node == NULL or node's name is the name we're looking for 
    if(node == NULL || (strcmp(node->name, name) == 0)){
        printf("Returning %s\n", node->name);
        return node;
    }
    
    //search left subtree if name's first character < node's first character 
    if(strcmp(node->name, name) < 0){
        return search_tree(node->left, name);
    }else{
        return search_tree(node->right, name);
    }
    return 0;
}


// function to add node to family tree
void add_node(Node** root, const char* parent, const char* child) {
   
    // initializing tree if root is null
    if (*root == NULL) {
        Node* new_parent = create_node(parent);
        Node* new_child = create_node(child);
        new_parent->left = new_child;
        *root = new_parent;
     
        return;
    }

    // search for parent in the tree
    Node* curr_parent = search_tree(*root, parent);

    if(curr_parent != NULL) {
        Node* new_child = create_node(child);

        // check if the parent already has a left child
        if (curr_parent->left == NULL) {
            curr_parent->left = new_child;

        } else {
            // compare the first character of the existing left child's name and the new child's name
            if (new_child->name[0] < curr_parent->left->name[0]) {
               
               //update pointers if new child has smaller ASCII than exisiting one 
                Node* tmp = curr_parent->left;
                curr_parent->left = new_child;
                curr_parent->right= tmp;
            } else {

                // add the new child to the right subtree of the parent if the ASCII condition fails 
                curr_parent->right = new_child;
            }
        }

    // parent not in tree, check if child is root     
    } else if (strcmp((*root)->name, child) == 0) {
            Node* new_root= create_node(parent);
            Node* tmp= *root;
            new_root->left= tmp;
            *root = new_root;
    }
}



// function to print tree in pre-order traversal
void print_tree(Node* node, int depth) {
    
    // base case 
    if (node != NULL) {

        //print 2*depth spaces for each name 
        for(int i=0; i<depth; i++){
            printf(" ");
        }        
        printf("%s\n", node->name);  

        // recursively print left and right subtrees
        print_tree(node->left, depth + 1); 
        print_tree(node->right, depth +1);
        }
    
}


int main() {

    Node* root = NULL;
    add_node(&root, "Aroha", "Manaia");
    add_node(&root, "Aroha", "Tane");
    add_node(&root, "Hemi", "Aroha");
    add_node(&root, "Manaia", "Rangi");
    add_node(&root, "Manaia", "Marama");
    add_node(&root, "Marama", "Tui");

    Node* node= search_tree(root, "Aroha");
    printf("%s\n", node->name);
    print_tree(root, 0);

    return 0;
}

