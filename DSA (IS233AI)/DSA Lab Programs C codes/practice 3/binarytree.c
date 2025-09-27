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

NODE buildtree(){
    int item; char ch;
    printf("Enter an item to insert (or -1 for NULL node): ");
    scanf("%d", &item); getchar();
    if(item==-1) return NULL;
    NODE new_node = createnode(item);
    printf("Do you want to add a left child to %d? (y/n): ", item);
    scanf("%c", &ch); getchar();
    if(ch=='y' || ch=='Y') new_node->left = buildtree();

    printf("Do you want to add a right child to %d? (y/n): ", item);
    scanf("%c", &ch); getchar();
    if(ch=='y' || ch=='Y') new_node->right = buildtree();

    return new_node;
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
    if(root==NULL) return -1;
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
    else return leaf_nodes(root->left)+leaf_nodes(root->right);
}

int nonleaf_nodes(NODE root){
    return count_nodes(root)-leaf_nodes(root);
}

int main(){
    NODE root=NULL; int ch, n, arr[SIZE];
    for(;;){
        printf("\n1.Create a BST\n2.Display\n3.No. of nodes\n4.Height\n5.Leaf nodes\n6.Non-leaf nodes\n7.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch); getchar();
        switch(ch){
            case 1: root = buildtree();
            break;
            case 2: display(root); break;
            case 3: printf("No. of nodes are %d", count_nodes(root)); break;
            case 4: printf("Height is %d", height(root)); break;
            case 5: printf("No. of leaf nodes are %d", leaf_nodes(root)); break;
            case 6: printf("No. of non-leaf nodes are %d", nonleaf_nodes(root)); break;
            default: exit(0);
        }
    }
    return 0;
}