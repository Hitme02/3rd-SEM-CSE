#include <stdio.h>
#include <stdlib.h>
#define SIZE 5
int count;

struct node{
    int data;
    struct node *addr;
};

typedef struct node *NODE;

NODE insertlast(NODE last, int item){
    NODE temp;
    if(count>=SIZE){
        printf("Queue is full\n");
        return last;
    }
    count++;
    temp = (NODE)malloc(sizeof(struct node));
    temp->data=item; temp->addr = NULL;
    if(last == NULL){
        temp->addr = temp;
        return temp;
    }
    else{
        temp->addr = last->addr;
        last->addr = temp;
        return temp;
    }
}

NODE deletebegin(NODE last){
    NODE temp;
    if(last==NULL){
        printf("Queue is empty\n");
        return last;
    }
    count--;
    if(last->addr==last){
        printf("Deleted element is %d\n", last->data);
        free(last);
        return NULL;
    }
    temp = last->addr;
    last->addr = temp->addr;
    printf("Deleted element is %d\n", temp->data);
    free(temp);
    return last;
}

void display(NODE last){
    NODE temp;
    if(last==NULL) printf("Queue is empty\n");
    else{
        printf("The contents of the queue are: \n");
        temp = last->addr;
        while(temp!=last){
            printf("%d\t", temp->data);
            temp=temp->addr;
        }
        printf("%d\n", temp->data);
    }
}

int main(){
    NODE last = NULL;
    int item, ch;
    for(;;){
        printf("1.Insert\n2.Delete\n3.Display\n4.Exit\n");
        printf("Read your choice: ");
        scanf("%d", &ch); getchar();
        switch(ch){
            case 1: printf("Enter the item to enqueue: ");
            scanf("%d", &item); last = insertlast(last, item);
            break;
            case 2: last = deletebegin(last); break;
            case 3: display(last); break;
            default: exit(0);
        }
    }
    return 0;
}