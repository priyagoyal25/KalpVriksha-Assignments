#include<stdio.h>
#include<stdlib.h>

struct Queue{
    int data;
    struct Queue* next;
};

int size=0;

int is_empty(struct Queue* front){
    if(front == NULL){
        return 1;
    }
    return 0;
}

struct Queue* create_node(int value){
    struct Queue* newnode = (struct Queue*) malloc(sizeof(struct Queue));
    newnode->data = value;
    newnode->next = NULL;
    return newnode;
}

void enqueue(struct Queue** front, struct Queue** rear, int value){
    // insert at_end using head and tail
    struct Queue* newnode = create_node(value);
    if(is_empty(*front)){
        *front = newnode;
        *rear = newnode;
    }
    else{
        (*rear)->next = newnode;
        *rear = (*rear)->next;
    }
    printf("\nElement enqueued successfully");
    size++;
}

void dequeue(struct Queue** front){
    // delete from begin
    if(is_empty(*front)){
        printf("\nQueue is empty");
        return;
    }
    struct Queue* cur_node = *front;
    *front = (*front)->next;
    printf("\nDequeued element: %d", cur_node->data);
    free(cur_node);
    size--;
}

void peek(struct Queue* front){
    if(is_empty(front)){
        printf("\nQueue is empty");
        return;
    }
    printf("\nPeek element: %d", front->data);
}

void display(struct Queue* front){
    if(is_empty(front)){
        printf("\nQueue is empty");
        return;
    }
    struct Queue* cur_node = front;
    while(cur_node != NULL){
        printf("%d ", cur_node->data);
        cur_node = cur_node->next;
    }  
}

void free_queue(struct Queue* front){
    while (front != NULL) {
        struct Queue* cur_node = front;
        front = front->next;
        free(cur_node);
    }
}

int main(){
    struct Queue* front = NULL;
    struct Queue* rear = NULL;

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
            enqueue(&front, &rear, value);
            break;
            case 2: dequeue(&front);
            break;
            case 3: peek(front);
            break;
            case 4:
            if(is_empty(front)){
                printf("\nQueue is empty");
            }
            else{
                printf("\nQueue is not empty");
            }
            break;
            case 5: printf("\nSize of queue: %d", size);
            break;
            case 6: display(front);
            break;
            case 7: 
            free_queue(front);
            exit(0);
            default: printf("\nInvalid choice\n");
        }
    }
    return 0;
} 