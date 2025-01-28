#include<stdio.h>

void linear_search(int arr[], int size, int value){
    for (int i = 0; i < size; i++)
        if (arr[i] == value){
            printf("Element %d found at index %d", value, i);
            return;
        }
    printf("%d not found", value);
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

    linear_search(arr, size, value);

    return 0;
}