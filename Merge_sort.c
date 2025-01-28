#include<stdio.h>

void merge(int arr[], int low, int mid, int high){
    int left=low, right=mid+1;
    int temp_size = high-low+1;
    int temp_arr[temp_size];    
    int temp_index = 0;                                

    while(left <= mid && right <= high){
        if(arr[left] <= arr[right]){
            temp_arr[temp_index]=arr[left];
            left++;
            temp_index++;
        }
        else{
            temp_arr[temp_index] = arr[right];
            right++;
            temp_index++;
        }
    }

    while(left <= mid){
        temp_arr[temp_index] = arr[left];
        left++;
        temp_index++;
    }

    while(right<=high){
        temp_arr[temp_index] = arr[right];
        right++;
        temp_index++;
    }

    for(int i=0;i<temp_size;i++){
        arr[i+low] = temp_arr[i];
    }
}

void merge_sort(int arr[], int low, int high){
    if(low<high){
        int mid = low + (high-low)/2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid+1, high);
        merge(arr, low, mid, high);
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

    merge_sort(arr, 0, size-1);

    printf("Sorted array: ");
    for(int i=0; i<size; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}