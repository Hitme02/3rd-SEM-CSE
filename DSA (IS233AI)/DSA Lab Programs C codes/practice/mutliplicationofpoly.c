#include <stdio.h>
#include <stdlib.h>

struct node{
    int po, co;
    struct node *addr;
};

typedef struct node *NODE;

NODE insertend(NODE start, int co, int po){
    NODE temp, cur;
    temp = (NODE)malloc(sizeof(struct node));
    temp->co = co; temp->po = po; temp->addr = NULL;
    if(start==NULL) return temp;
    cur = start;
    while(cur->addr!=NULL) cur=cur->addr;
    cur->addr = temp;
    return start;
}

void display(NODE start){
    NODE cur;
    if(start==NULL) printf("Empty polynomial\n");
    else{
        cur = start;
        while(cur->addr!=NULL){
            printf("%dx^%d+", cur->co, cur->po);
            cur = cur->addr;
        }
        printf("%dx^%d\n", cur->co, cur->po);
    }
}

NODE addterm(NODE res, int co, int po){
    NODE temp, cur;
    temp = (NODE)malloc(sizeof(struct node));
    temp->co = co; temp->po = po; temp->addr = NULL;
    if(res==NULL) return temp;
    cur = res;
    while(cur!=NULL){
        if(cur->po==po){
            cur->co += co;
        }
        cur=cur->addr;
    }
    if(cur==NULL) cur->addr = temp;
    return res;
}

NODE multiply(NODE poly1, NODE poly2){
    NODE p1, p2, res=NULL;
    for(p1=poly1;p1!=NULL;p1=p1->addr)
        for(p2=poly2;p2!=NULL;p2=p2->addr)
            res = addterm(res, p1->co*p2->co, p1->po+p2->po);
    return res;
}

int main(){
    NODE poly1=NULL, poly2=NULL, poly;
    int co, po;
    int m,n;
    printf("Enter the number of terms in the 1st polynomial: ");
    scanf("%d", &m);
    for(int i=1;i<=m;i++){
        printf("Enter the CO and PO of %d terms: ", i);
        scanf("%d %d", &co, &po);
        poly1 = insertend(poly1, co, po);
    }
    printf("The first polynomial is ");
    display(poly1);
    printf("Enter the number of terms in the 2nd polynomial: ");
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        printf("Enter the CO and PO of %d terms: ", i);
        scanf("%d %d", &co, &po);
        poly2 = insertend(poly2, co, po);
    }
    printf("The second polynomial is ");
    display(poly2);
    poly = multiply(poly1, poly2);
    printf("The third polynomial is ");
    display(poly);
    return 0;
}