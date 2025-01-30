#include<stdio.h>
#include<stdlib.h>

struct Stack{
    int data;
    struct Stack* next;
};

int size=0;

int is_empty(struct Stack* top_head){
    if(top_head == NULL){
        printf("\nStack Underflow");
        return 1;
    }
    return 0;
}

struct Stack * create_node(int value){
    struct Stack* newnode = (struct Stack*) malloc(sizeof(struct Stack));
    newnode->data = value;
    newnode->next = NULL;
    return newnode;
}

struct Stack* push(struct Stack* top_head, int value){
    struct Stack* newnode = create_node(value);
    newnode->next = top_head;
    top_head = newnode;
    printf("\nPushed successfully");
    size++;
    return top_head;
}

struct Stack* pop(struct Stack* top_head){
    if(is_empty(top_head)) return top_head;
    struct Stack* cur_node = top_head;
    top_head = cur_node->next;
    printf("\nPopped element: %d", cur_node->data);
    free(cur_node);
    size--;
    return top_head;
}

void peek(struct Stack* top_head){
    if(is_empty(top_head)) return;
    printf("\nPeek element: %d", top_head->data);
}

void display(struct Stack* top_head){
    if(is_empty(top_head)) return;
    struct Stack* cur_node = top_head;
    while(cur_node != NULL){
        printf("%d\n", cur_node->data);
        cur_node = cur_node->next;
    }
}

int main(){
    struct Stack *top_head = NULL;

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
            top_head = push(top_head, value);
            break;
            case 2: top_head = pop(top_head);
            break;
            case 3: peek(top_head);
            break;
            case 4: {int empty = is_empty(top_head);
            if(empty == 0){
                printf("\nStack not empty");
            }
            break;}
            case 5: printf("Size of stack: %d", size);
            break;
            case 6: display(top_head);
            break;
            case 7: exit(0);
            default: printf("\nInvalid choice\n");
        }
    }
    return 0;
} 