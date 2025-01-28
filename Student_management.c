#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    int id;
    char *name;
    int marks;
    struct node *next;
};

struct node* head = NULL;

void display(){
    if(head == NULL){
        printf("\nEmpty list\n");
        return;
    }
    struct node* cur_node = head;
    while(cur_node != NULL){
        printf("ID: %d, Name: %s, Marks: %d\n", cur_node->id, cur_node->name, cur_node->marks);
        cur_node = cur_node->next;
    }
}

struct node* create_node(int id, char *name, int marks){
    struct node* newnode = (struct node*) malloc(sizeof(struct node));
    newnode->id = id;
    newnode->name = (char*) malloc(strlen(name) + 1);
    strcpy(newnode->name, name);
    newnode->marks = marks;
    newnode->next = NULL;
    return newnode;
}


void search(){
    if(head == NULL){
        printf("\nEmpty list, Search cannot be performed\n");
        return;
    }
    int search_id;
    printf("Enter id to search: ");
    scanf("%d", &search_id);

    struct node* cur_node = head;
    while(cur_node != NULL){
        if(search_id == cur_node->id){
            printf("\nStudent found");
            printf("\nID: %d, Name: %s, Marks: %d\n", cur_node->id, cur_node->name, cur_node->marks);
            return;
        }
        cur_node = cur_node->next;
    }
    printf("\nStudent not found");
}

struct node* find_middle(struct node* head){
    struct node* slow = head;
    struct node* fast = head->next;

    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

struct node* merge_recursive(struct node* left, struct node* right){
    if(left == NULL) return right;
    if(right == NULL) return left;

    if(left->marks > right->marks){
        left->next = merge_recursive(left->next, right);
        return left;
    }
    else{
        right->next = merge_recursive(left, right->next);
        return right;
    }
}

struct node* sort_by_marks(struct node* head) {

    if(head == NULL) {
        printf("\nEmpty list, sorting cannot be performed\n");
        return head;
    }
    else if(head->next == NULL) return head;

    struct node* middle = find_middle(head);
    struct node* left = head;
    struct node* right = middle->next;
    middle->next = NULL;

    left = sort_by_marks(left);
    right = sort_by_marks(right);
    head = merge_recursive(left, right);
    return head;
}

struct node* add_student(int id, char *name, int marks){
    struct node* newnode = create_node(id, name, marks);
    if(head == NULL){
        head = newnode;
        return head;
    }
    else{
        struct node* cur_node = head;
        while(cur_node->next != NULL){
            cur_node = cur_node->next;
        }
        cur_node->next = newnode;
    }

    return head;
}

int main(){
    int choice;
    int id, marks;
    char name[50];

    while(1){   
        printf("\n---MENU---");
        printf("\n1. Add Student");
        printf("\n2. Search Student by id");
        printf("\n3. Sort Students by marks");
        printf("\n4. Display Students");
        printf("\n5. Exit the program");
        printf("\n\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: 
            printf("Enter id: ");
            scanf("%d", &id);
            printf("Enter name: ");
            getchar();
            scanf("%[^\n]%*c", name);
            printf("Enter marks: ");
            scanf("%d", &marks);
            if(marks < 0 || marks > 100){
                printf("\nInvalid marks\n");
                break;
            }
            head = add_student(id, name, marks);
            break;
            case 2: search();
            break;
            case 3: head = sort_by_marks(head);
            break;
            case 4: display();
            break;
            case 5: exit(0);
            default: printf("\nInvalid choice\n");
        }
    }
    return 0;
}