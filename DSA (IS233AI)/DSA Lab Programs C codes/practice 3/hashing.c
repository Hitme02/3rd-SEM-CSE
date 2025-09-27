#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 10

int h[TABLE_SIZE] = {NULL};

void insert(){
    int i, key, hkey, hash2, index;
    printf("Enter a value to enter into the hash table: ");
    scanf("%d", &key);
    hkey = key % TABLE_SIZE;
    hash2 = 7 - (key % TABLE_SIZE);
    for(i=0;i<TABLE_SIZE;i++){
        index = (hkey + hash2*i) % TABLE_SIZE;
        if(h[index]==NULL){
            h[index] = key;
            break;
        }
    }
    if(i==TABLE_SIZE) printf("Element can't be inserted\n");
}

void search(){
    int i, index, key, hkey, hash2;
    printf("Enter a value to search in the hash table: ");
    scanf("%d", &key);
    hkey = key % TABLE_SIZE;
    hash2 = 7 - (key % 7);
    for(i=0;i<TABLE_SIZE;i++){
        index = (hkey + hash2 * i) % TABLE_SIZE;
        if(h[index]==key){
            printf("Element found at index %d", index);
            break;
        }
    }
    if(i==TABLE_SIZE) printf("Element can't be found in the hash table\n");
}

void display(){
    int i;
    printf("The contents of hash table are:\n");
    for(i=0;i<TABLE_SIZE;i++)
        printf("Value %d at index %d\n", h[i], i);
}

int main(){
    int ch, i;
    for(;;){
        printf("1.Insert\n2.Search\n3.Display\n4.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch); getchar();
        switch(ch){
            case 1: insert(); break;
            case 2: search(); break;
            case 3: display(); break;
            default: exit(0);
        }
    }
    return 0;
}