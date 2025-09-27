#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 5

struct queue{
    int front, rear;
    char data[SIZE][20];
};

typedef struct queue QUEUE;

void send(QUEUE *q, char item[20]){
    if(q->front==(q->rear+1)%SIZE) printf("Queue Full!\n");
    else{
        q->rear = (q->rear+1)%SIZE;
        strcpy(q->data[q->rear], item);
        if(q->front == -1) q->front = 0;
    }
}

char *receive(QUEUE *q){
    char *del;
    if(q->front == -1){
        printf("Queue is empty!\n");
        return 0;
    }
    else{
        del = q->data[q->front];
        if(q->rear==q->front){
            q->rear = -1; q->front = -1;
        }
        else q->front = (q->front+1) % SIZE;
        return del;
    }
}

void display(QUEUE q){
    int i;
    if(q.front==-1) printf("Empty Queue\n");
    else{
    printf("The queue contents are :\n");
    for(i=q.front;i!=q.rear;i=(i+1)%SIZE){
        printf("%s\t", q.data[i]);
    }
    printf("%s\n", q.data[i]);
    }
}

int main(){
    QUEUE q; q.front = -1; q.rear = -1; int ch;
    char *del; char item[20];
    for(;;){
        printf("Read your choice\n");
        printf("1.Send\n2.Receive\n3.Display\n4.Exit\n");
        scanf("%d", &ch); getchar();
        switch(ch){
            case 1:
                printf("Enter msg to be sent:"); gets(item);
                send(&q, item);break;
            case 2:
                del = receive(&q);
                if(del!=NULL) printf("The deleted msg is %s\n", del); break;
            case 3:
                display(q); break;
            default: exit(0);
        }
    }
    return 0;
}