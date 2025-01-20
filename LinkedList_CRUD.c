#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
}*head, *newnode;

int is_empty_list(){
    if(head == NULL){
        printf("Empty list.");
        return 1;
    }
    return 0;
}

void free_linkedlist(){
    struct node* cur_node = head;
    struct node* next_node;

    while(cur_node != NULL){
        next_node = cur_node->next;
        free(cur_node);
        cur_node = next_node;
    }
}

void allocate_memory(){
    newnode = (struct node *) malloc(sizeof(struct node));
    if(newnode == NULL){
        printf("\nMemory not allocated for newnode");
        free_linkedlist();
        exit(0);
    }
}

void insert_at_begin(int value){
    allocate_memory();
    newnode->data = value;
    newnode->next = head;
    head = newnode;
}

void insert_at_last(int value){
    if(head == NULL){
        insert_at_begin(value);
        return;
    }

    struct node* cur_node = head;

    while(cur_node->next != NULL){
        cur_node = cur_node->next;
    }

    allocate_memory();
    cur_node->next = newnode;
    newnode->next = NULL;
    newnode->data = value;
}

void insert_at_position(int value, int pos){
    if(pos < 1){
        printf("Invalid Position.");
        free_linkedlist();
        exit(0);
    }
    
    if(pos == 1){
        insert_at_begin(value);
        return;
    }

    if(is_empty_list()) exit(0);

    struct node* cur_node = head;
    
    for(int i=1;i<pos-1;i++){ 
        cur_node = cur_node->next;
        if(cur_node ==  NULL){
            printf("Invalid Position.");
            free_linkedlist();
            exit(0);
        }
    }
    allocate_memory();
    newnode->data = value;
    newnode->next = cur_node->next;
    cur_node->next = newnode;
}

void display_elements(){
    if(is_empty_list()) exit(0);

    struct node* cur_node = head;
    while(cur_node != NULL){
        printf("%d ", cur_node->data);
        cur_node = cur_node->next;
    }
    printf("\n");
}

void delete_at_begin(){
    if(is_empty_list()) exit(0);

    struct node *cur_node = head;
    head = cur_node->next;
    free(cur_node);
}

void delete_at_last(){
    if(is_empty_list()) exit(0);

    struct node* cur_node = head;
    if(cur_node->next == NULL){
        head = NULL;
        free(cur_node);
        return;
    }

    while(cur_node->next->next != NULL){
        cur_node = cur_node->next;
    }
    free(cur_node->next);
    cur_node->next = NULL;
}

void delete_at_position(int pos){
    if(pos < 1){
        printf("Invalid Position.");
        free_linkedlist();
        exit(0);
    }

    if(pos == 1){
        delete_at_begin();
        return;
    }

    if(head->next == NULL){
        printf("Invalid Position.");
        free_linkedlist();
        exit(0);
    }

    struct node* cur_node = head;
    for(int i=1;i<pos-1;i++){
        cur_node = cur_node->next;
        if(cur_node ==  NULL){
            printf("Invalid Position.");
            free_linkedlist();
            exit(0);
        }
    }

    struct node* node_to_delete = cur_node->next;
    cur_node->next = node_to_delete->next;
    free(node_to_delete);
}

void update_at_position(int new_value, int pos){
    if(pos < 1){
        printf("Invalid Position.");
        free_linkedlist();
        exit(0);
    }

    if(pos == 1){
        head->data = new_value;
        return;
    }

    struct node* cur_node = head;
    for(int i=1;i<pos;i++){
        cur_node = cur_node->next;
        if(cur_node ==  NULL){
            printf("Invalid Position.");
            free_linkedlist();
            exit(0);
        }
    }

    cur_node->data = new_value;
}

int main(){
    int value, choice, pos, node_value, operations;
    head = NULL;

    scanf("%d", &operations);
    while(operations != 0){

        scanf("%d", &choice);

        switch(choice){
            case 1: 
            scanf("%d", &value);
            insert_at_last(value);
            break;
            
            case 2: 
            scanf("%d", &value);
            insert_at_begin(value);
            break;

            case 3: 
            scanf("%d %d", &pos, &value);
            insert_at_position(value, pos);
            break;

            case 4:  display_elements();
            break;

            case 5: if(is_empty_list()) exit(0);
            scanf("%d %d", &pos, &value);
            update_at_position(value, pos);
            break;

            case 6: delete_at_begin();
            break;

            case 7: delete_at_last();
            break;

            case 8: if(is_empty_list()) exit(0);
            scanf("%d", &pos);
            delete_at_position(pos);
            break;

            default:{
                printf("Invalid choice.\n");
                free_linkedlist();
                exit(0);
            }
        }
        operations--;
    }

    free_linkedlist();
    return 0;
}