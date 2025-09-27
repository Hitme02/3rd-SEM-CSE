#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *left, *right;
};
typedef struct node *NODE;

NODE createnode(int item){
    NODE temp;
    temp=(NODE)malloc(sizeof(struct node));
    temp->data = item; temp->right = NULL; temp->left = NULL;
    return temp;
}

NODE insertbst(NODE root, int item){
    NODE temp;
    temp = createnode(item);
    if(root==NULL) return temp;
    else if(item<root->data) root->left = insertbst(root->left, item);
    else root->right = insertbst(root->right, item);
    return root;
}

NODE inordersuccessor(NODE root){
    NODE cur = root;
    while(cur->left!=NULL) cur = cur->left;
    return cur;
}

NODE deletebst(NODE root, int key){
    NODE temp;
    if(root==NULL) return NULL;
    else if(key<root->data) root->left = deletebst(root->left, key);
    else if(key>root->data) root->right = deletebst(root->right, key);
    else{
        if(root->left==NULL && root->right==NULL){
            free(root); return NULL;
        }
        if(root->left==NULL){
            temp = root->right;
            free(root);
            return temp;
        }
        if(root->right==NULL){
            temp = root->left;
            free(root);
            return temp;
        }
        temp = inordersuccessor(root->right);
        root->data = temp->data;
        root->right = deletebst(root->right, temp->data);
    }
    return root;
}

void preorder(NODE root){
    if(root!=NULL){
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(NODE root){
    if(root!=NULL){
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void postorder(NODE root){
    if(root!=NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main(){
    NODE root = NULL; int i, ch, item;
    for(;;){
        printf("\n1.Insert\n2.Delete\n3.Preorder\n4.Inorder\n5.Postorder\n6.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch); getchar();
        switch(ch){
            case 1: printf("Enter the item to insert: ");
            scanf("%d", &item); root = insertbst(root, item);
            break;
            case 2: printf("Enter the item to delete: ");
            scanf("%d", &item); root = deletebst(root, item);
            case 3: preorder(root); break;
            case 4: inorder(root); break;
            case 5: postorder(root); break;
            default: exit(0);
        }
    }
    return 0;
}