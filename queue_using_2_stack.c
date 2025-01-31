#include<stdio.h>
#include<stdlib.h>

struct Stack{
    int top;
    int capacity;
    int* array;
};

struct Queue{
    struct Stack* stack1;
    struct Stack* stack2;
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

void display(struct Stack* stack){
    if(is_empty(stack)){
        printf("\nQueue is empty");
        return;
    }
    for(int i=stack->top;i>=0;i--){
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}

void enqueue(struct Queue* queue, int value){
    if(is_full(queue->stack1)){
        printf("\nQueue is full");
        return;
    }

    while(!is_empty(queue->stack1)){
        int item = pop(queue->stack1);
        push(queue->stack2, item);
    }

    push(queue->stack1, value);


    while(!is_empty(queue->stack2)){
        int item = pop(queue->stack2);
        push(queue->stack1, item);
    }
    printf("\nElement enqueued successfully");
}

void dequeue(struct Queue* queue){
    if(is_empty(queue->stack1)){
        printf("\nQueue is empty");
        return;
    }
    int item = pop(queue->stack1);
    printf("\n%d Element dequeued successfully", item);
}

void peek(struct Queue* queue){
    if(is_empty(queue->stack1)){
        printf("\nQueue is empty");
        return;
    }
    printf("\nPeek element: %d", queue->stack1->array[queue->stack1->top]);
}

struct Stack* create_stack(int size){
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = size;
    stack->array = (int*) malloc(sizeof(int) * size);
    return stack;
}

struct Queue* create_queue(int size){
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    queue->stack1 = create_stack(size);
    queue->stack2 = create_stack(size);
    return queue;
}

int main(){
    int size = 0;
    printf("\nEnter size of queue: ");
    scanf("%d", &size);

    struct Queue *queue = create_queue(size);

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
            enqueue(queue, value);
            break;
            case 2: dequeue(queue);
            break;
            case 3: peek(queue);
            break;
            case 4: 
            if(is_empty(queue->stack1)){
                printf("\nQueue is empty");
            }
            else{
                printf("\nQueue is not empty");
            }
            break;
            case 5: printf("Size of Queue: %d", queue->stack1->top+1);
            break;
            case 6: display(queue->stack1);
            break;
            case 7: 
            free(queue->stack1->array);
            free(queue->stack2->array);
            free(queue->stack1);
            free(queue->stack2);
            free(queue);
            exit(0);
            default: printf("\nInvalid choice\n");
        }
    }
    return 0;
} 