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
        printf("\nQueue is full");
        return;
    }
    if(is_empty(queue)){
        queue->front = 0;
    }
    queue->rear++;
    queue->array[queue->rear] = value;
    printf("\nElement enqueued successfully");
}

void dequeue(struct Queue* queue){
    if(is_empty(queue)){
        printf("\nQueue is empty");
        return;
    }

    int item = queue->array[queue->front];

    // if there is only 1 element or it is empty then reset the queue
    if(queue->front == queue->rear){
        queue->front = -1;
        queue->rear = -1;
    }
    else{
        queue->front++;
    }
    printf("\nDequeued element: %d", item);
}

void peek(struct Queue* queue){
    if(is_empty(queue)){
        printf("\nQueue is empty");
        return;
    }
    
    printf("\nPeek element: %d", queue->array[queue->front]);
}

void display(struct Queue* queue){
    if(is_empty(queue)){
        printf("\nQueue is empty");
        return;
    }

    for(int i=queue->front;i<=queue->rear;i++){
        printf("%d ", queue->array[i]);
    }
}

int size_of_queue(struct Queue* queue){
    if(is_empty(queue)) return 0;
    else return (queue->rear -queue->front) + 1;
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
        printf("\n5. Size of queue");
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
            if(is_empty(queue)){
                printf("\nQueue is empty");
            }
            else{
                printf("\nQueue is not empty");
            }
            break;
            case 5: printf("\nSize of queue: %d", size_of_queue(queue));
            break;
            case 6: display(queue);
            break;
            case 7: free(queue->array);
            free(queue);
            exit(0);
            default: printf("\nInvalid choice\n");
        }
    }
    return 0;
} 