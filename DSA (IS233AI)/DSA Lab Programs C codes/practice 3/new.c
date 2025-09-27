#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};
typedef struct node *NODE;

// Function to create a new node
NODE create_node(int item) {
    NODE temp = (NODE)malloc(sizeof(struct node));
    temp->data = item;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

// Function to insert nodes interactively
NODE insert_nodes() {
    int item;
    char choice;
    printf("Enter the value of the node (or -1 for NULL): ");
    scanf("%d", &item);

    if (item == -1)  // -1 indicates no node
        return NULL;

    NODE new_node = create_node(item);

    printf("Do you want to add a left child to %d? (y/n): ", item);
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        new_node->left = insert_nodes();  // Recursively insert left child
    }

    printf("Do you want to add a right child to %d? (y/n): ", item);
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        new_node->right = insert_nodes();  // Recursively insert right child
    }

    return new_node;
}

// Function to display the tree in inorder traversal
void display_inorder(NODE root) {
    if (root != NULL) {
        display_inorder(root->left);
        printf("%d\t", root->data);
        display_inorder(root->right);
    }
}

// Function to count total nodes in the tree
int count_nodes(NODE root) {
    if (root == NULL)
        return 0;
    return count_nodes(root->left) + count_nodes(root->right) + 1;
}

// Function to calculate the height of the tree
int height(NODE root) {
    int leftht,rightht;
if(root == NULL)
return -1;
else
{
leftht = height(root->left);
rightht = height(root->right);
if(leftht > rightht)
return leftht + 1;
else
return rightht + 1;
}
}

// Function to count leaf nodes in the tree
int leaf_nodes(NODE root) {
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return leaf_nodes(root->left) + leaf_nodes(root->right);
}

// Function to count non-leaf nodes in the tree
int nonleaf_nodes(NODE root) {
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return 0;
    return nonleaf_nodes(root->left) + nonleaf_nodes(root->right) + 1;
}

// Main function
int main() {
    NODE root = NULL;

    printf("Build your binary tree dynamically:\n");
    root = insert_nodes();  // Call to build the tree interactively

    printf("\nInorder Traversal of the tree:\n");
    display_inorder(root);

    printf("\n\nTotal number of nodes: %d", count_nodes(root));
    printf("\nHeight of the tree: %d", height(root));
    printf("\nTotal number of leaf nodes: %d", leaf_nodes(root));
    printf("\nTotal number of non-leaf nodes: %d\n", nonleaf_nodes(root));
    return 0;
}