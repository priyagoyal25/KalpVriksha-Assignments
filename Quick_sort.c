#include<stdio.h>

void swap(int* num1, int* num2){
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

int partition(int arr[], int low, int high){
    int pivot = arr[low];

    int left = low, right = high;

    while(left < right){
        while(arr[left] <= pivot){
            left++;
        }
        while(arr[right] > pivot){
            right--;
        }

        if(left < right){
            swap(&arr[left], &arr[right]);
        }
    }

    swap(&arr[low], &arr[right]);
    return right;
}

void quick_sort(int arr[], int low, int high){
    if(low<high){
        int partition_index = partition(arr, low, high);
        quick_sort(arr, low, partition_index-1);
        quick_sort(arr, partition_index+1, high);
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

    quick_sort(arr, 0, size-1);

    printf("Sorted array: ");
    for(int i=0;i<size;i++){
        printf("%d ", arr[i]);
    }
    return 0;
}