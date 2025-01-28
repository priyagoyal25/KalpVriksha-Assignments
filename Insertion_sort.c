#include<stdio.h>

void insertion_sort(int arr[], int size){
    for(int i=0;i<size-1;i++){
        int temp = arr[i+1];
        int j = i;
        while(temp < arr[j] && j >= 0){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
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

    insertion_sort(arr, size);

    printf("Sorted array: ");
    for(int i=0;i<size;i++){
        printf("%d ", arr[i]);
    }
    return 0;
}