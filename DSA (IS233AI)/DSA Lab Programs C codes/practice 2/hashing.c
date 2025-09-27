#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 10

int h[TABLE_SIZE] = {NULL};

void insert(){
    int i, key, index, hkey, hash2;
    printf("Enter a value to add to hash table: ");
    scanf("%d", &key);
    hkey = key % TABLE_SIZE;
    hash2 = 7 - (key % 7);
    for(i=0;i<TABLE_SIZE;i++){
        index = (hkey + i*hash2) % TABLE_SIZE;
        if(h[index] == NULL){
            h[index] = key;
            break;
        }
    }
    if(i==TABLE_SIZE) printf("Element couldnt be inserted.\n");
}

void search(){
    int key, i, index, hkey, hash2;
    printf("Enter the element to search: ");
    scanf("%d", &key);
    hkey = key % TABLE_SIZE;
    hash2 = 7 - (key % 7);
    for(i=0;i<TABLE_SIZE;i++){
        index = (hkey + i*hash2) % TABLE_SIZE;
        if(key==h[index]){
            printf("Element found at index %d\n", index);
            break;
        }
    }
    if(i==TABLE_SIZE) printf("Element not found in the hash table.\n");
}

void display(){
    int i;
    printf("The contents of hash table are: \n");
    for(i=0;i<TABLE_SIZE;i++) printf("Value %d is stored at index %d\n", h[i], i);
}

int main(){
    int ch, i;
    for(;;){
        printf("1. Insert\n2. Search\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch(ch){
            case 1: insert(); break;
            case 2: search(); break;
            case 3: display(); break;
            default: exit(0);
        }
    }
    return 0;
}