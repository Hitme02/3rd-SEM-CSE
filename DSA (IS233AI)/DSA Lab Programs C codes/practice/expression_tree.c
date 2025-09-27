#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node{
    char data;
    struct node *left, *right;    
};

typedef struct node *NODE;

struct stack{
    int top;
    NODE data[10];
};
typedef struct stack STACK;

int preced(char symbol){
    switch(symbol){
        case '$': return 5;
        case '*':
        case '/': return 3;
        case '+':
        case '-': return 1;
    }
}

NODE createnode(char item){
    NODE temp;
    temp = (NODE)malloc(sizeof(struct node));
    temp->right = NULL; temp->left = NULL;
    temp->data = item;
    return temp;
}

void push(STACK *s, NODE item){
    s->data[++(s->top)] = item;
}

NODE pop(STACK *s){
    return s->data[(s->top)--];
}

NODE create_exp_tree(NODE root, char infix[10]){
    STACK TS, OS; OS.top = -1; TS.top = -1;
    char symbol; int i; NODE temp, t;
    for(i=0;infix[i]!='\0';i++){
        symbol = infix[i];
        temp = createnode(symbol);
        if(isalnum(symbol)) push(&TS, temp);
        else{
            if(OS.top==-1) push(&OS, temp);
            else{
                while(preced(symbol)<=preced(OS.data[OS.top]->data) && OS.top!=-1){
                    t = pop(&OS);
                    t->right = pop(&TS);
                    t->left = pop(&TS);
                    push(&TS, t);
                }
                push(&OS, temp);
            }
        }
    }
    while(OS.top!=-1){
        t = pop(&OS);
        t->right = pop(&TS);
        t->left = pop(&TS);
        push(&TS, t);
    }
    return pop(&TS);
}

void preorder(NODE root){
    if(root!=NULL){
        printf("%c", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(NODE root){
    if(root!=NULL){
        inorder(root->left);
        printf("%c", root->data);
        inorder(root->right);
    }
}

void postorder(NODE root){
    if(root!=NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->data);
    }
}

int main(){
    NODE root=NULL;
    char infix[10];
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    root = create_exp_tree(root, infix);
    printf("\nThe preorder traversal is: ");
    preorder(root);
    printf("\nThe inorder traversal is: ");
    inorder(root);
    printf("\nThe postorder traversal is: ");
    postorder(root);
    return 0;
}