#include<stdio.h>

void swap(int* num1, int* num2){
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void selection_sort(int arr[], int size){  
    for(int i=0;i<size-1;i++){
        int min = i;
        for(int j=i+1;j<size;j++){
            if(arr[min] > arr[j]){
                min = j;
            }
        }

        if(min != i){
            swap(&arr[i], &arr[min]);
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

    selection_sort(arr, size);

    printf("Sorted array: ");
    for(int i=0;i<size;i++){
        printf("%d ", arr[i]);
    }
    return 0;
}