#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 20

struct stack{
    int top;
    char data[SIZE];
};

typedef struct stack STACK;

void push(STACK *s, char item){
    s->data[++(s->top)] = item;
}

char pop(STACK *s){
    return s->data[(s->top)--];
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

void infixtopostfix(STACK *s, char infix[SIZE]){
    char postfix[SIZE], temp, symbol; int i,j=0;
    for(i=0;infix[i]!='\0';i++){
        symbol = infix[i];
        if(isalnum(symbol)) postfix[j++] = symbol;
        else if(symbol==' ') continue;
        else{
            switch(symbol){
                case '(': push(s, symbol); break;
                case ')': temp = pop(s);
                while(temp!='('){
                    postfix[j++] = temp;
                    temp = pop(s);
                }
                break;
                case '+':
                case '-':
                case '*':
                case '/':
                case '^': if(s->top==-1 || s->data[s->top]=='(') push(s, symbol);
                else{
                    while(preced(symbol)<=preced(s->data[s->top] && s->top!=-1 && s->data[s->top]!='(')) postfix[j++] = pop(s);
                    push(s, symbol);
                }
                break;
                default: printf("Invalid!"); exit(0);
            }
        }
    }
    while(s->top!=-1) postfix[j++] = pop(s);
    postfix[j] = '\0';
    printf("Postfix for the required expression is %s\n", postfix);
}

int main(){
    STACK s; s.top = -1;
    char infix[SIZE];
    printf("Enter the required expression: ");
    gets(infix);
    infixtopostfix(&s, infix);
    return 0;
}