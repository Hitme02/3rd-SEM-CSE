#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5

struct queue{
    int front, rear;
    char data[SIZE][20];
};

typedef struct queue QUEUE;

void send(QUEUE *q, char item[20]){
    if((q->rear+1)%SIZE == q->front) printf("Queue is full\n");
    else{
        q->rear = (q->rear+1)%SIZE;
        strcpy(q->data[q->rear], item);
        if(q->front == -1) q->front = 0;
    }
}

char *receive(QUEUE *q){
    char *del;
    if(q->front == -1){
        printf("Queue is empty\n");
        return -1;
    }
    else{
        del = q->data[q->front];
        if(q->front==q->rear){
            q->front = -1;
            q->rear = -1;
        }
        else{
            q->front = (q->front+1)%SIZE;
        }
        return del;
    }
}

void display(QUEUE q){
    int i;
    if(q.front==-1) printf("Queue is empty\n");
    else{
        for(i=q.front;i!=q.rear;i=(i+1)%SIZE)
            printf("%s\t", q.data[i]);
        printf("%s\n", q.data[i]);
    }
}

int main(){
    QUEUE q; q.front = -1; q.rear = -1;
    int ch; char item[20];
    for(;;){
        printf("1. Send\n2. Receive\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch(ch){
            case 1: printf("Enter the item to be sent: ");
            scanf("%s", item);
            send(&q, item);
            break;
            case 2: printf("Received item: %s\n", receive(&q));
            break;
            case 3: display(q);
            break;
            case 4: exit(0);
        }
    }
}