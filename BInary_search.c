#include<stdio.h>

void swap(int* num1, int* num2){
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void sort(int arr[], int size){
    for(int i=0;i<size-1;i++){
        for(int j=0;j<size-i-1;j++){
            if(arr[j] > arr[j+1]){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

int binary_search(int arr[], int low, int high, int value)
{
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == value)
            return mid;
        if (arr[mid] < value)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}


int main(){
    int arr[100000] = {0};
    int size = 0;
    int value;
    printf("Enter elements in array: ");
    while(1){
        scanf("%d", &arr[size++]);
        char ch = getchar();
        if(ch == '\n' || ch == EOF) break;
    }

    printf("Enter element to seach: ");
    scanf("%d", &value);

    sort(arr, size);

    int pos = binary_search(arr, 0, size-1, value);

    printf("Sorted array: ");
    for(int i=0;i<size;i++){
        printf("%d ", arr[i]);
    }

    if(pos != -1) printf("\n%d found at index %d", value, pos);
    else printf("\n%d not found", value);

    return 0;
}