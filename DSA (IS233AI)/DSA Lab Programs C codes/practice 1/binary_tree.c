#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *left, *right;
};

typedef struct node *NODE;

NODE createnode(int item){
    NODE temp;
    temp = (NODE)malloc(sizeof(struct node));
    temp->data = item; temp->left=NULL; temp->right=NULL;
    return temp;
}

NODE insertleft(NODE root, int item){
    root->left = createnode(item);
    return root->left;
}

NODE insertright(NODE root, int item){
    root->right = createnode(item);
    return root->right;
}

void display(NODE root){
    if(root!=NULL){
        display(root->left);
        printf("%d ", root->data);
        display(root->right);
    }
}

int count_nodes(NODE root){
    if(root==NULL) return 0;
    else return (count_nodes(root->left) + count_nodes(root->right) + 1);
}

int height(NODE root){
    int leftht, rightht;
    if(root==NULL) return -1;
    leftht = height(root->left);
    rightht = height(root->right);
    if(leftht>rightht) return leftht+1;
    else return rightht+1;
}

int leaf_nodes(NODE root){
    if(root==NULL) return 0;
    else if(root->left==NULL && root->right==NULL) return 1;
    else return (leaf_nodes(root->left)+leaf_nodes(root->right));
}

int nonleaf_nodes(NODE root){
    if(root==NULL || (root->left==NULL && root->right==NULL)) return 0;
    else return (nonleaf_nodes(root->left) + nonleaf_nodes(root->right)+1);
}

int main(){
    NODE root = NULL;
    root = createnode(45);
    insertleft(root,39); 
    insertright(root,78); 
    insertleft(root->right,54); 
    insertright(root->right,79); 
    insertright(root->right->left,55); 
    insertright(root->right->right,80);
    printf("\nThe inorder traversal of the tree is ");
    display(root);
    printf("\nThe total number of nodes in the tree is %d", count_nodes(root));
    printf("\nThe height of the tree is %d", height(root));
    printf("\nThe total number of leaf nodes in the tree is %d", leaf_nodes(root));
    printf("\nThe total number of non leaf nodes in the tree is %d", nonleaf_nodes(root));
    return 0;
}