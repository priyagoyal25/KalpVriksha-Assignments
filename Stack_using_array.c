#include<stdio.h>
#include<stdlib.h>

struct Stack{
    int top;
    int capacity;
    int* array;
};

int is_empty(struct Stack* stack){
    if(stack->top == -1){
        return 1;
    }
    return 0;
}

int is_full(struct Stack* stack){
    if(stack->top >= stack->capacity-1){ 
        return 1;
    }
    return 0;
}

void push(struct Stack* stack, int value){
    if(is_full(stack)){
        printf("\nStack Overflow");
        return;
    }
    stack->top++;
    stack->array[stack->top] = value;
    printf("\nPushed successfully");
}

void pop(struct Stack* stack){
    if(is_empty(stack)){
        printf("\nStack Underflow");
        return;
    }
    int item = stack->array[stack->top];
    stack->top--;
    printf("\nPopped element: %d", item);
}

void peek(struct Stack* stack){
    if(is_empty(stack)){
        printf("\nStack Underflow");
        return;
    }
    printf("\nPeek element: %d", stack->array[stack->top]);
}

void display(struct Stack* stack){
    if(is_empty(stack)){
        printf("\nStack Underflow");
        return;
    }
    for(int i=stack->top;i>=0;i--){
        printf("%d\n", stack->array[i]);
    }
}

struct Stack* create_stack(int size){
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = size;
    stack->array = (int*) malloc(sizeof(int) * size);
    return stack;
}

int main(){
    int size = 0;
    printf("\nEnter size of stack: ");
    scanf("%d", &size);

    struct Stack *stack = create_stack(size);

    int choice, value;
    while(1){   
        printf("\n\n---MENU---");
        printf("\n1. Push");
        printf("\n2. Pop");
        printf("\n3. peek");
        printf("\n4. Is empty");
        printf("\n5. Size of stack");
        printf("\n6. Display Stack");
        printf("\n7. Exit the program");
        printf("\n\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: 
            printf("Enter element: ");
            scanf("%d", &value);
            push(stack, value);
            break;
            case 2: pop(stack);
            break;
            case 3: peek(stack);
            break;
            case 4: 
            if(is_empty(stack)){
                printf("\nStack is empty");
            }
            else{
                printf("\nStack is not empty");
            }
            break;
            case 5: printf("Size of stack: %d", stack->top+1);
            break;
            case 6: display(stack);
            break;
            case 7: 
            free(stack->array);
            free(stack);
            exit(0);
            default: printf("\nInvalid choice\n");
        }
    }
    return 0;
} 