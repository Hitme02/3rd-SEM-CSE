#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 5

struct queue{
    int front, rear;
    char items[SIZE][20];
};

typedef struct queue QUEUE;

void send(QUEUE *q, char item[20]){
    if((q->rear+1)%SIZE == q->front) printf("Queue is full/n");
    else{
        q->rear = (q->rear+1)%SIZE;
        strcpy(q->items[q->rear], item);
        if(q->front==-1) q->front = 0;
    }
}

char *receive(QUEUE *q){
    char *del;
    if(q->front==-1){
        printf("Queue is empty!"); 
        return -1;
    }
    else{
        del = q->items[q->front];
        if(q->front==q->rear){
            q->front = -1; q->rear = -1;
        }
        else q->front = (q->front+1)%SIZE;
        return del;
    }
}

void display(QUEUE q){
    int i;
    if(q.front==-1) printf("Empty queue\n");
    else{
        for(i=q.front;i!=q.rear;i=(i+1)%SIZE){
            printf("%s\t", q.items[i]);
        }
        printf("%s\n", q.items[i]);
    }
}

int main(){
    QUEUE q; q.front=-1; q.rear=-1;
    int ch; char item[20]; char *del;
    for(;;){
        printf("Enter 1.Send\n2.Receive\n3.Display\n4.Exit\n");
        scanf("%d", &ch);
        getchar();
        switch(ch){
            case 1:
            printf("Enter msg to be sent: "); gets(item);
            send(&q, item); break;
            case 2:
            del = receive(&q);
            if(del != NULL) printf("The deleted msg is %s", del); break;
            case 3:
            display(q);
            break;
            default: exit(0);
        }
    }
    return 0;
}