#include<stdio.h>

int two_pointer(int arr[], int value, int size)
{
    int start = 0, end = size-1;
    while(start <= end){
        if(value == arr[start]) return start;
        else if(value == arr[end]) return end;
        start++;
        end--;
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
    
    int pos = two_pointer(arr, value, size);

    if(pos != -1) printf("%d found at index %d", value, pos);
    else printf("%d not found", value);

    return 0;
}