#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

struct node{
    int data;
    struct node *left, *right;
};
typedef struct node *NODE;

NODE createnode(int item){
    NODE temp;
    temp = (NODE)malloc(sizeof(struct node));
    temp->data=item; temp->left = NULL; temp->right = NULL;
    return temp;
}

NODE buildtree(int arr[], int size, int index){
    if(index >= size || arr[index]==-1) return NULL;
    NODE root = createnode(arr[index]);
    root->left = buildtree(arr, size, 2*index+1);
    root->right = buildtree(arr, size, 2*index+2);
    return root;
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
    else return count_nodes(root->left) + count_nodes(root->right) + 1;
}

int height(NODE root){
    int leftht, rightht;
    if(root==NULL)  return -1;
    else{
        leftht = height(root->left);
        rightht = height(root->right);
        if(leftht>rightht) return leftht+1;
        else return rightht+1;
    }
}

int leaf_nodes(NODE root){
    if(root==NULL) return 0;
    else if(root->left==NULL && root->right==NULL) return 1;
    else return leaf_nodes(root->left) + leaf_nodes(root->right);
}

int nonleaf_nodes(NODE root){
    return count_nodes(root) - leaf_nodes(root);
}

int main(){
    int arr[SIZE]; NODE root=NULL;
    int n, ch, i;
    for(;;){
        printf("\n1.Create BT\n2.Display\n3.Count nodes\n4.Height\n5.Leaf Nodes\n6.Non-leaf nodes\n7.Exit\n");
        printf("Enter your choice: "); scanf("%d", &ch); getchar();
        switch(ch){
            case 1: printf("Enter number of elements in the tree: ");
            scanf("%d", &n);
            printf("Enter the elements: ");
            for(i=0;i<n;i++){
                scanf("%d", &arr[i]);
            }
            root = buildtree(arr, n, 0);
            break;
            case 2: printf("Contents of the bt are: ");
            display(root); break;
            case 3: printf("No. of nodes are:- %d", count_nodes(root));
            break;
            case 4: printf("Height of the tree is :- %d", height(root));
            break;
            case 5: printf("No. of leaf nodes are :- %d", leaf_nodes(root));
            break;
            case 6: printf("No. of non leaf nodes are :- %d", nonleaf_nodes(root));
            break;
            default: exit(0);
        }
    }
    return 0;
}