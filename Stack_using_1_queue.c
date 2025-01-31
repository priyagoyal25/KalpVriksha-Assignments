#include<stdio.h>
#include<stdlib.h>

struct Queue{
    int front;
    int rear;
    int capacity;
    int* array;
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

    if (!is_empty(queue)) {
        for (int i = queue->front; i <= queue->rear; i++) {
            queue->array[i - queue->front] = queue->array[i];
        }
        queue->rear -= queue->front;
        queue->front = 0;
    }
    return item;
}

void peek(struct Queue* queue){
    if(is_empty(queue)){
        printf("\nStack is empty");
        return;
    }
    
    printf("\nPeek element: %d", queue->array[queue->front]);
}

void display(struct Queue* queue){
    if(is_empty(queue)){
        printf("\nStack is empty");
        return;
    }

    for(int i=queue->front;i<=queue->rear;i++){
        printf("%d\n", queue->array[i]);
    }
}

int size_of_queue(struct Queue* queue){
    if(is_empty(queue)) return 0;
    else return (queue->rear -queue->front) + 1;
}

void push(struct Queue* queue, int value){
    if(is_full(queue)){
        printf("\nStack is full");
        return;
    }
    enqueue(queue, value);

    int size = queue->rear - queue->front + 1;

    for(int i = 0; i < size - 1; i++) {
        int temp = queue->array[queue->front];
        dequeue(queue);
        enqueue(queue, temp);
    }
    printf("\nElement pushed successfully");
}

void pop(struct Queue* queue){
    int item = dequeue(queue);
    if (item != -1) {
        printf("\nPopped element: %d\n", item);
    }
}

struct Queue* create_queue(int size){
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    queue->capacity = size;
    queue->array = (int*) malloc(sizeof(int) * size);
    return queue;
}

int main(){
    int size = 0;
    printf("\nEnter size of Stack: ");
    scanf("%d", &size);

    struct Queue *queue = create_queue(size);

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
            push(queue, value);
            break;
            case 2: pop(queue);
            break;
            case 3: peek(queue);
            break;
            case 4:
            if(is_empty(queue)){
                printf("\nStack is empty");
            }
            else{
                printf("\nStack is not empty");
            }
            break;
            case 5: printf("\nSize of Stack: %d", size_of_queue(queue));
            break;
            case 6: display(queue);
            break;
            case 7: 
            free(queue->array);
            free(queue);
            exit(0);
            default: printf("\nInvalid choice\n");
        }
    }
    return 0;
} 