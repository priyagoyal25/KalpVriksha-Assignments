#include<stdio.h>
#include<stdlib.h>

struct Queue{
    int front;
    int rear;
    int capacity;
    int* array;
};

struct Stack{
    struct Queue* queue1;
    struct Queue* queue2;
};

int is_empty(struct Queue* queue){
    if(queue->front == -1 || queue->front > queue->rear){
        return 1;
    }
    return 0;
}

int is_full(struct Queue* queue){
    if(queue->rear >= queue->capacity - 1){ 
        return 1;
    }
    return 0;
}

void enqueue(struct Queue* queue, int value){
    if(is_full(queue)){
        printf("\nStack is full");
        return;
    }
    if(is_empty(queue)){
        queue->front = 0;
    }
    queue->rear++;
    queue->array[queue->rear] = value;
}

int dequeue(struct Queue* queue){
    if(is_empty(queue)){
        printf("\nStack is empty");
        return -1;
    }

    int item = queue->array[queue->front];

    if(queue->front == queue->rear){
        queue->front = -1;
        queue->rear = -1;
    }
    else{
        queue->front++;
    }
    return item;
}

void display(struct Queue* queue1){
    if(is_empty(queue1)){
        printf("\nStack is empty");
        return;
    }

    for(int i=queue1->front;i<=queue1->rear;i++){
        printf("%d\n", queue1->array[i]);
    }
}

int size_of_queue(struct Queue* queue){
    if(is_empty(queue)) return 0;
    else return (queue->rear - queue->front) + 1;
}

void push(struct Stack* stack, int value){
    if(is_full(stack->queue1)){
        printf("\nStack is full");
        return;
    }

    enqueue(stack->queue2, value);

    while(!is_empty(stack->queue1)){
        int item = dequeue(stack->queue1);
        enqueue(stack->queue2, item);
    }

    struct Queue *temp = stack->queue1;
    stack->queue1 = stack->queue2;
    stack->queue2 = temp;
    printf("\nElement pushed successfully");
}

void pop(struct Stack* stack){
    if (is_empty(stack->queue1)) {
        printf("\nStack is empty");
        return;
    }
    int item = dequeue(stack->queue1);
    printf("\n%d Element popped successfully", item);
}

void peek(struct Stack* stack){
    if(is_empty(stack->queue1)){
        printf("\nStack is empty");
        return;
    }
    
    printf("\nPeek element: %d", stack->queue1->array[stack->queue1->front]);
}

struct Queue* create_queue(int size){
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    queue->capacity = size;
    queue->array = (int*) malloc(sizeof(int) * size);
    return queue;
}

struct Stack* create_stack(int size){
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->queue1 = create_queue(size);
    stack->queue2 = create_queue(size);
    return stack;
}

int main(){
    int size = 0;
    printf("\nEnter size of Stack: ");
    scanf("%d", &size);

    struct Stack* stack = create_stack(size); 

    int choice, value;
    while(1){   
        printf("\n\n---MENU---");
        printf("\n1. Push");
        printf("\n2. Pop");
        printf("\n3. peek");
        printf("\n4. Is empty");
        printf("\n5. Size of Stack");
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
            if(is_empty(stack->queue1)){
                printf("\nStack is empty");
            }
            else{
                printf("\nStack is not empty");
            }
            break;
            case 5: printf("\nSize of Stack: %d", size_of_queue(stack->queue1));
            break;
            case 6: display(stack->queue1);
            break;
            case 7: 
            free(stack->queue1->array);
            free(stack->queue2->array);
            free(stack->queue1);      
            free(stack->queue2);      
            free(stack);  
            exit(0);
            default: printf("\nInvalid choice\n");
        }
    }
    return 0;
} 