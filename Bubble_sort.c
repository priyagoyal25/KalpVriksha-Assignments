#include<stdio.h>

void swap(int* num1, int* num2){
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void bubble_sort(int arr[], int size){  
    for(int i=0;i<size-1;i++){
        for(int j=0;j<size-i-1;j++){
            if(arr[j] > arr[j+1]){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

int main(){
    int arr[100000] = {0};
    int size = 0;
    printf("Enter elements in array: ");
    while(1){
        scanf("%d", &arr[size++]);
        char ch = getchar();
        if(ch == '\n' || ch == EOF) break;
    }

    bubble_sort(arr, size);

    printf("Sorted array: ");
    for(int i=0;i<size;i++){
        printf("%d ", arr[i]);
    }
    return 0;
}