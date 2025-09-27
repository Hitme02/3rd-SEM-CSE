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
    temp->left = NULL; temp->right = NULL;
    temp->data = item;
    return temp;
}

int count_nodes(NODE root){
    if(root==NULL) return 0;
    return 1+count_nodes(root->left)+count_nodes(root->right);
}

int count_leaves(NODE root){
    if(root==NULL) return 0;
    if(root->left==NULL && root->right==NULL) return 1;
    return count_leaves(root->left)+count_leaves(root->right);
} 

int nonleaf_nodes(NODE root){
    if(root==NULL) return 0;
    if(root->left==NULL && root->right==NULL) return 0;
    return 1+nonleaf_nodes(root->left)+nonleaf_nodes(root->right);
}

int height(NODE root){
    int lheight, rheight;
    if(root==NULL) return -1;
    lheight = height(root->left);
    rheight = height(root->right);
    if(lheight>rheight) return lheight+1;
    else return rheight+1;
} 

int main(){
    NODE root = NULL;
    root = createnode(10);
    root->left = createnode(20);
    root->right = createnode(30);
    root->left->left = createnode(40);
    root->left->right = createnode(50);
    root->right->left = createnode(60);
    root->right->right = createnode(70);
    printf("Number of nodes in the tree is %d\n", count_nodes(root));
    printf("Number of leaves in the tree is %d\n", count_leaves(root));
    printf("Number of non-leaf nodes in the tree is %d\n", nonleaf_nodes(root));
    printf("Height of the tree is %d\n", height(root));
    return 0;
}
