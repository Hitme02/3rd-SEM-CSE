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

void push(STACK *s, NODE item){
    s->data[++(s->top)] = item;
}

NODE pop(STACK *s){
    return s->data[(s->top)--];
}

int preced(char symbol){
    switch(symbol){
        case '$': return 5;
        case '*':
        case '/': return 3;
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

NODE createnode(char item){
    NODE temp;
    temp = (NODE)malloc(sizeof(struct node));
    temp->left = NULL; temp->right = NULL;
    temp->data = item;
    return temp;
}

NODE create_exp_tree(NODE root, char infix[10]){
    NODE temp, t; char symbol; STACK TS, OS;
    TS.top = -1; OS.top = -1; int i;
    for(i=0;infix[i]!='\0';i++){
        symbol = infix[i];
        temp = createnode(symbol);
        if(isalnum(symbol)) push(&TS, temp);
        else{
            if(OS.top == -1) push(&OS, temp);
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
    char infix[10];
    printf("Enter the required infix expression: ");
    scanf("%s", infix);
    root = create_exp_tree(root, infix);
    printf("\nThe preorder expression is: ");
    preorder(root);
    printf("\nThe inorder expression is: ");
    inorder(root);
    printf("\nThe postorder expression is: ");
    postorder(root);
    return 0;
}