#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define SIZE 5

struct node{
    int co, po;
    struct node *addr;
};

typedef struct node *NODE;

NODE insertend(NODE start, int co, int po){
    NODE temp, cur;
    temp = (NODE)malloc(sizeof(struct node));
    temp->addr = NULL; temp->co = co; temp->po = po;
    if(start==NULL) return temp;
    cur = start;
    while(cur->addr!=NULL) cur=cur->addr;
    cur->addr = temp;
    return start;
}

void display(NODE start){
    NODE temp=start;
    if(start==NULL) printf("Empty Polynomial!\n");
    else{
        while(temp->addr!=NULL){
            printf("%dx^%d+", temp->co, temp->po);
            temp = temp->addr;
        }
        printf("%dx^%d\n", temp->co, temp->po);
    }
}

NODE addterm(NODE res, int co, int po){
    NODE temp, cur;
    temp = (NODE)malloc(sizeof(struct node));
    temp->co = co; temp->po = po;
    temp->addr = NULL;
    if(res==NULL) return temp;
    cur = res;
    while(cur!=NULL){
        if(cur->po==po){
            cur->co += co; return res;
        }
        cur = cur->addr;
    }
    if(cur==NULL) res = insertend(res, co, po);
    return res;
}

NODE multiply(NODE poly1, NODE poly2){
    NODE p1, p2, res = NULL;
    for(p1=poly1;p1!=NULL;p1=p1->addr)
        for(p2=poly2;p2!=NULL;p2=p2->addr)
            res = addterm(res, p1->co*p2->co, p1->po*p2->po);
    return res;
}

