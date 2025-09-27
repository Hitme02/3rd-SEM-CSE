#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 20

struct node{
    char data;
    struct node *left, *right;
};

typedef struct node *NODE;

struct stack{
    int top;
    NODE data[SIZE];
};

typedef struct stack STACK;

void push(STACK *s, NODE item){
    s->data[++(s->top)] = item;
}

NODE pop(STACK *s){
    return s->data[(s->top)--];
}

NODE createnode(char symbol){
    NODE temp;
    temp = (NODE)malloc(sizeof(struct node));
    temp->data = symbol; temp->left = NULL; temp->right = NULL;
    return temp;
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
        printf("%c", root->data);
    }
}

int preced(char symbol){
    switch(symbol){
        case '^': return 5;
        case '/':
        case '*': return 3;
        case '+':
        case '-': return 1;
    }
}

NODE create_expr_tree(NODE root, char infix[SIZE]){
    STACK OS, TS; TS.top=-1; OS.top=-1;
    char symbol; NODE temp, t; int i,j;
    for(i=0;infix[i]!='\0';i++){
        symbol = infix[i];
        temp = createnode(symbol);
        if(isalnum(symbol)) push(&TS, temp);
        else{
            if(OS.top==-1) push(&OS, temp);
            else{
                while(OS.top!=-1 && preced(symbol)<=preced(OS.data[OS.top]->data)){
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

int main(){
    NODE root=NULL;
    char infix[SIZE];
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    root = create_expr_tree(root, infix);
    printf("Preorder expression is: ");
    preorder(root);
    printf("\n");
    printf("Inorder expression is: ");
    inorder(root);
    printf("\n");
    printf("Postorder expression is: ");
    postorder(root);
    printf("\n");
    return 0;
}