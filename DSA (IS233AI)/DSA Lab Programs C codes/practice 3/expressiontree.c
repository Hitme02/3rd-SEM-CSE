#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 10

struct node{
    char data;
    struct node *left, *right;
};
typedef struct node *NODE;

struct stack{
    NODE data[SIZE];
    int top;
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
    temp->data = symbol;
    temp->left = NULL; temp->right = NULL;
    return temp;
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

NODE create_expr_tree(NODE root, char infix[SIZE]){
    char symbol; int i, j; NODE temp, t;
    STACK TS, OS; TS.top = -1; OS.top = -1;
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

void main(){
    NODE root = NULL;
    char infix[SIZE];
    printf("Read infix expression: ");
    scanf("%s", infix);
    root = create_expr_tree(root, infix);
    printf("Preorder is : ");
    preorder(root);
    printf("\n");
    printf("Inorder is : ");
    inorder(root);
    printf("\n");
    printf("Postorder is : ");
    postorder(root);
    printf("\n");
}