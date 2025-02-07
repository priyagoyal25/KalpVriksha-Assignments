#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    char *key;
    char *value;
    struct node *next;
};

struct hashmap{
    int capacity;
    int size;
    struct node** data;
};

struct hashmap *map = NULL;

struct node* create_node(char *key, char *value){
    struct node* newnode = (struct node*) malloc(sizeof(struct node));
    newnode->key = (char*) malloc(sizeof(char)*strlen(key)+1);
    newnode->value = (char*) malloc(sizeof(char)*strlen(value)+1);

    strcpy(newnode->key, key);
    strcpy(newnode->value, value);
    newnode->next = NULL;
    return newnode;
}

void initialise_hashmap(){
    map = (struct hashmap*) malloc(sizeof(struct hashmap));
    map->capacity = 100;
    map->size = 0;
    map->data = (struct node **)calloc(map->capacity, sizeof(struct node*));
}

int hash_function(char* key){
    int sum = 0;
    for(int i=0;key[i] != '\0';i++){
        sum += key[i];
    }
    return sum%map->capacity;
}

char* search(char * key){
    int index = hash_function(key);
    struct node* cur_node = map->data[index];
    while(cur_node != NULL){
        if(strcmp(cur_node->key, key) == 0){
            return cur_node->value;
        }
        cur_node = cur_node->next;
    }
    return NULL;
}

void insert_into_hashmap(char *key, char *value){
    if(search(key) != NULL){
        printf("\nDuplicate keys are not allowed");
        return;
    }
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

void delete_from_hashmap(char* key){
    int index = hash_function(key);
    struct node* cur_node = map->data[index];
    struct node* prev = NULL;

    while(cur_node != NULL){
        if(strcmp(cur_node->key, key) == 0){
            if(prev == NULL){
                map->data[index] = cur_node->next;
            }
            else{
                prev->next = cur_node->next;
            }
            free(cur_node->key);
            free(cur_node->value);
            free(cur_node);
            printf("\nKey deleted");
            map->size--;
            return;
        }
        prev = cur_node;
        cur_node = cur_node->next;
    }
    printf("\nKey not found");
}

void display(){
    for(int i=0;i<map->capacity;i++){
        struct node* cur_node = map->data[i];
        while(cur_node != NULL){
            printf("key: %s value: %s\n", cur_node->key, cur_node->value);
            cur_node = cur_node->next;
        }
    }
}


int main(){
    initialise_hashmap();

    int choice;
    char* key = (char*) malloc(sizeof(char)*100);
    char* value = (char*) malloc(sizeof(char)*100);

    while(1){
        printf("\n\n---MENU---");
        printf("\n1. Insert in hashmap");
        printf("\n2. Delete in hashmap");
        printf("\n3. Search in hashmap");
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
            scanf("%s", key);
            printf("Enter value: ");
            scanf("%s", value);
            insert_into_hashmap(key, value);
            break;

            case 2: 
            printf("\nEnter key to delete: ");
            scanf("%s", key);
            delete_from_hashmap(key);
            break;

            case 3:
            printf("\nEnter key to search: ");
            scanf("%s", key);
            char* result = search(key);
            if(result == NULL){
                printf("\nKey not found");
                break;
            }
            printf("\nCorresponding value: %s", result);
            break;

            case 4:
            display();
            break;

            case 5:
            printf("Exiting..");
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