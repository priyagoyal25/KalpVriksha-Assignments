#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TABLE_SIZE 10
struct node{
    int key;
    int value;
    struct node *next;
};

struct hashmap{
    int capacity;
    int size;
    struct node** data;
};

struct hashmap *map = NULL;

struct node* create_node(int key, int value){
    struct node* newnode = (struct node*) malloc(sizeof(struct node));
    newnode->key = key;
    newnode->value = value;
    newnode->next = NULL;
    return newnode;
}

void initialise_hashmap(){
    map = (struct hashmap*) malloc(sizeof(struct hashmap));
    map->capacity = TABLE_SIZE;
    map->size = 0;
    map->data = (struct node **)calloc(map->capacity, sizeof(struct node*));
}

int hash_function(int key){
    int index = key % TABLE_SIZE;
    return index;
}

int search(int key){
    int index = hash_function(key);
    struct node* cur_node = map->data[index];
    while(cur_node != NULL){
        if(cur_node->key == key){
            return cur_node->value;
        }
        cur_node = cur_node->next;
    }
    return -1;
}

void insert_into_hashmap(int key, int value){
    int index = hash_function(key);
    struct node* newnode = create_node(key, value);
    
    if(map->data[index] == NULL){
        map->data[index] = newnode;
    }
    else{
        newnode->next = map->data[index];
        map->data[index] = newnode;
    }
    map->size++;
    printf("\nInserted successfully");
}

void delete_from_hashmap(int  key){
    int index = hash_function(key);
    struct node* cur_node = map->data[index];
    struct node* prev = NULL;

    while(cur_node != NULL){
        if(cur_node->key == key){
            if(prev == NULL){
                map->data[index] = cur_node->next;
            }
            else{
                prev->next = cur_node->next;
            }
            free(cur_node);
            printf("\nKey %d deleted", key);
            map->size--;
            return;
        }
        prev = cur_node;
        cur_node = cur_node->next;
    }
    printf("\nKey not found");
}

void display(){
    printf("\nHash Table:\n");
    for(int i=0;i<map->capacity;i++){
        int is_arrow = 0;
        struct node* cur_node = map->data[i];
        if(cur_node != NULL){
            printf("\nIndex %d: ", i);
        }
        while(cur_node != NULL){
            if(is_arrow) printf("-> ");
            printf("(%d, %d) ", cur_node->key, cur_node->value);
            cur_node = cur_node->next;
            is_arrow = 1;
        }
    }
}


int main(){
    initialise_hashmap();

    int choice;
    int key, value;

    while(1){
        printf("\n\n---MENU---");
        printf("\n1. Insert in hashmap");
        printf("\n2. Search in hashmap");
        printf("\n3. Delete in hashmap");
        printf("\n4. Display hashmap");
        printf("\n5. Exit\n");

        printf("\nEnter choice: ");
        if(scanf("%d", &choice) != 1){
            printf("Invalid choice type");
            exit(0);
        }

        switch(choice){
            case 1: 
            printf("\nEnter key: ");
            scanf("%d", &key);
            printf("Enter value: ");
            scanf("%d", &value);
            insert_into_hashmap(key, value);
            break;

            case 2:
            printf("\nEnter key to search: ");
            scanf("%d", &key);
            int result = search(key);
            if(result == -1){
                printf("\nKey not found");
                break;
            }
            printf("\nCorresponding value: %d", result);
            break;

            case 3: 
            printf("\nEnter key to delete: ");
            scanf("%d", &key);
            delete_from_hashmap(key);
            break;

            case 4:
            display();
            break;

            case 5:
            printf("Exiting program");
            free(map->data);
            free(map);
            exit(0);
            
            default: 
            printf("\nInvalid choice");
            break;
        }
    }

    return 0;
}