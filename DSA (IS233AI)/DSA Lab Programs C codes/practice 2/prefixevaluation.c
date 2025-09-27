#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define SIZE 20

struct stack{
    int top;
    float data[SIZE];
};

typedef struct stack STACK;

void push(STACK *s, float item){
    s->data[++(s->top)] = item;
}

float pop(STACK *s){
    return s->data[(s->top)--];
}

float operate(float op1, float op2, char symbol){
    switch(symbol){
        case '+': return op1+op2;
        case '-': return op1-op2;
        case '/': return op1/op2;
        case '*': return op1*op2;
        case '^': return pow(op1, op2);
    }
}

float evaluate(STACK *s, char prefix[SIZE]){
    float op1, op2, res; int i; char symbol;
    for(i=strlen(prefix)-1;i>=0;i--){
        symbol = prefix[i];
        if(symbol==' ') continue;
        if(isdigit(symbol)) push(s, symbol-'0');
        else{
            op1 = pop(s);
            op2 = pop(s);
            res = operate(op1, op2, symbol);
            push(s, res);
        }
    }
    return pop(s);
}

int main(){
    STACK s; s.top = -1; float ans;
    char prefix[SIZE];
    printf("Enter a prefix expression: ");
    gets(prefix);
    ans = evaluate(&s, prefix);
    printf("Answer to the expression is %f\n", ans);
    return 0;
}