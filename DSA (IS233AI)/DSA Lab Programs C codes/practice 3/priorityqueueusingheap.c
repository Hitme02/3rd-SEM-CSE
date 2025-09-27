#include <stdio.h>
#include <stdlib.h>

void heapify(int a[10], int n){
    int i,j,k,v,flag=0;
    for(i=n/2;i>=1;i--){
        k = i; v = a[k];
        while(!flag && 2*k<=n){
            j = 2*k;
            if(j<n){
                if(a[j]<a[j+1]) j++;
            }
            if(v>=a[j]) flag=1;
            else{
                a[k] = a[j];
                k = j;
            }
        }
        a[k] = v;
        flag = 0;
    }
}

int main(){
    int i, ch, a[10], n, ele;
    for(;;){
        printf("\n1. Create a heap\n2. ExtractMax\n3. Insert\n4.Exit");
        printf("Enter your choice: \n");
        scanf("%d", &ch);
        switch(ch){
            case 1:
                printf("Enter number of elements: ");
                scanf("%d", &n);
                printf("Enter the elements: ");
                for(i=1;i<=n;i++) scanf("%d", &a[i]);
                heapify(a, n);
                printf("After heap construction, elements: ");
                for(i=1;i<=n;i++) printf("%d\t", a[i]);
                break;
            case 2:if(n>=1){
                printf("Element deleted is %d\n", a[1]);
                a[1] = a[n];
                n--;
                heapify(a, n);
                if(n!=0){
                    printf("After heap reconstruction, elements: \n");
                    for(i=1;i<=n;i++) printf("%d ", a[i]);
                    }
                }  
                else{
                    printf("No element to delete\n");
                }
                break;
            case 3:
                printf("Enter element to insert: ");
                scanf("%d", &ele);
                a[n+1] = ele;
                n++;
                heapify(a, n);
                printf("After heap reconstruction, elements: ");
                for(i=1;i<=n;i++) printf("%d\t", a[i]);
                break;
            default: exit(0);
            }
        }
        return 0;
    }