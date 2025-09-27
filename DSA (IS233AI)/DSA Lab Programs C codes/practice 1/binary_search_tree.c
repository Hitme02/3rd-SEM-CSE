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

NODE insertbst(NODE root, int item){
    NODE temp;
    temp = createnode(item);
    if(root==NULL) return temp;
    else{
        if(item<root->data) root->left = insertbst(root->left, item);
        else root->right = insertbst(root->right, item);
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

NODE inordersuccessor(NODE root){
    NODE cur=root;
    while(cur->left!=NULL){
        cur=cur->left;
    }
    return cur;
}

NODE deletenode(NODE root, int key){
    NODE temp;
    if(root==NULL) return NULL;
    if(key<root->data) root->left = deletenode(root->left, key);
    else if(key>root->data) root->right = deletenode(root->right, key);
    else{
        if(root->left==NULL){
            temp = root->right; free(root); return temp;
        }
        if(root->right==NULL){
            temp = root->left; free(root); return temp;
        }
        temp = inordersuccessor(root->right);
        root->data = temp->data;
        root->right = deletenode(root->right, temp->data);
    }
    return root;
}

int main(){
    NODE root=NULL;
    int ch, item, key;
    for(;;){
        printf("Enter\n1.Insert\n2.Preorder\n3.Inorder\n4.Postorder\n5.Delete\n6.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch(ch){
            case 1:
                printf("Enter item to be inserted: ");
                scanf("%d", &item);
                root = insertbst(root, item); break;
            case 2:
                printf("The preorder traversal is ");
                preorder(root); break;
            case 3:
                printf("The inorder traversal is ");
                inorder(root); break;
            case 4:
                printf("The postorder traversal is ");
                postorder(root); break;
            case 5:
                printf("Enter the key to be deleted: ");
                scanf("%d", &key);
                root = deletenode(root, key); break;
            default:exit(0);
        }
    }
    return 0;
}