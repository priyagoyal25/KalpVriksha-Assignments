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
        printf("\nQueue is full");
        return;
    }
    stack->top++;
    stack->array[stack->top] = value;
}

int pop(struct Stack* stack){
    if(is_empty(stack)){
        printf("\nQueue is empty");
        return -1;
    }
    int item = stack->array[stack->top];
    stack->top--;
    return item;
}

void peek(struct Stack* stack){
    if(is_empty(stack)){
        printf("\nQueue is empty");
        return;
    }
    printf("\nPeek element: %d", stack->array[stack->top]);
}

void display(struct Stack* stack){
    if(is_empty(stack)){
        printf("\nQueue is empty");
        return;
    }
    for(int i =0 ;i<=stack->top;i++){
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}

void enqueue(struct Stack* stack, int value) {
    if(is_full(stack)){
        printf("\nQueue is full");
        return;
    }
    push(stack, value);
    printf("\nElement enqueued successfully");
}

int dequeue(struct Stack* stack) {
    if (is_empty(stack)) {
        printf("\nQueue is empty\n");
        return -1;
    }
    int x = pop(stack);

    if (is_empty(stack)) {
        printf("\nDequeued: %d\n", x);
        return x;
    }

    int res = dequeue(stack);
    push(stack, x);
    return res;
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
        printf("\n1. Enqueue");
        printf("\n2. Dequeue");
        printf("\n3. peek");
        printf("\n4. Is empty");
        printf("\n5. Size of Quueue");
        printf("\n6. Display Queue");
        printf("\n7. Exit the program");
        printf("\n\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: 
            printf("Enter element: ");
            scanf("%d", &value);
            enqueue(stack, value);
            break;
            case 2: dequeue(stack);
            break;
            case 3: peek(stack);
            break;
            case 4: 
            if(is_empty(stack)){
                printf("\nQueue is empty");
            }
            else{
                printf("\nQueue is not empty");
            }
            break;
            case 5: printf("Size of Queue: %d", stack->top+1);
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