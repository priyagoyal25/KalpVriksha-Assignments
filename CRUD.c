#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define FILENAME "users.txt"
#define MAX 100

typedef struct
{
    int id;
    char name[MAX];
    int age;
} User;

typedef enum
{
    Add_user = 1,
    Display_user,
    Update_user,
    Delete_user,
    Exit
} Menuchoice;

int typeCheck(int value){
    if(value != 1){
        printf("\nInvalid input..\n");
        while (getchar() != '\n');
        return 0;
    }
    return 1;
}

FILE *isFileEmpty(FILE *file)
{
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        printf("\nEmpty File....\n");
        fclose(file);
        return NULL;
    }
    rewind(file);
    return file;
}

int isIdExists(int id)
{
    FILE *file = fopen(FILENAME, "rb");
    if (!file)
    {
        printf("\nError in opening file!\n");
        return 0;
    }
    User user;
    while (fread(&user, sizeof(User), 1, file))
    {
        if (user.id == id)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void createUser()
{
    FILE *file = fopen(FILENAME, "ab");
    if (!file)
    {
        printf("\nError in opening file!\n");
        return;
    }
    User user;
    int idExists;
    do
    {
        printf("\nEnter User ID: ");
        if (!typeCheck(scanf("%d", &user.id)))
        {
            continue;
        }
        idExists = isIdExists(user.id);
        if (idExists)
        {
            printf("\nError: User ID %d already exists. Please enter a unique ID.\n", user.id);
        }
    } while (idExists);

    getchar();
    printf("\nEnter Name: ");
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';
    
    do{
        printf("\nEnter Age: ");
        if (!typeCheck(scanf("%d", &user.age)) || user.age <= 0)
        {
            continue;
        }
        break;
    } while(1);
    
    fwrite(&user, sizeof(User), 1, file);
    printf("\nUser added successfully.....\n");
   
    fclose(file);
}

void readUsers()
{
    FILE *file = fopen(FILENAME, "rb");
    if (!file)
    {
        printf("\nError in opening file!\n");
        return;
    }
    file = isFileEmpty(file);
    if (!file)
        return;

    User user;
    printf("\n--- List of Users ---\n");
    while (fread(&user, sizeof(User), 1, file))
    {
        printf("ID: %d, Name: %s, Age: %d\n", user.id, user.name, user.age);
    }
    fclose(file);
}

void updateUser()
{
    FILE *file = fopen(FILENAME, "rb+");
    if (!file)
    {
        printf("\nError in opening file!\n");
        return;
    }
    file = isFileEmpty(file);
    if (!file)
        return;

    int id;

    do{
        printf("\nEnter the ID of the user you want to update: ");
        if (!typeCheck(scanf("%d", &id)))
        {
            continue;
        }
        break;
    }while(1);

    User user;
    int found = 0;

    while (fread(&user, sizeof(User), 1, file))
    {
        if (user.id == id)
        {
            found = 1;

            int choice;
            do {
                printf("\nWhat would you like to update?\n");
                printf("1. Name\n");
                printf("2. Age\n");
                printf("3. Both Name and Age\n");
                printf("Enter your choice (1/2/3): ");
                if (!typeCheck(scanf("%d", &choice)) || (choice < 1 || choice > 3))
                {
                    continue;
                }
                break;
            } while (1);

            getchar(); // Clear newline left by scanf

            if (choice == 1 || choice == 3)
            {
                printf("Enter new Name: ");
                fgets(user.name, sizeof(user.name), stdin);
                user.name[strcspn(user.name, "\n")] = '\0';
            }

            if (choice == 2 || choice == 3)
            {
                do {
                    printf("Enter new Age: ");
                    if (!typeCheck(scanf("%d", &user.age)) || user.age <= 0)
                    {
                        printf("\nInvalid input. Please enter a valid positive age.\n");
                        while (getchar() != '\n'); // Clear input buffer
                        continue;
                    }
                    break;
                } while (1);
            }

            fseek(file, -sizeof(User), SEEK_CUR);
            fwrite(&user, sizeof(User), 1, file);

            printf("\nUser updated successfully......\n");
            break;
        }
    }
    if (!found)
    {
        printf("\nUser with ID %d not found.\n", id);
    }
    fclose(file);
}

void deleteUser()
{
    FILE *file = fopen(FILENAME, "rb");
    if (!file)
    {
        printf("\nError in opening file!\n");
        return;
    }

    file = isFileEmpty(file);
    if (!file)
        return;
    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile)
    {
        printf("\nError in creating temporary file!\n");
        fclose(file);
        return;
    }

    int idToDelete;
    do {
        printf("Enter the User ID to delete: ");
        if (!typeCheck(scanf("%d", &idToDelete)))
        {
            continue;
        }
        break;
    } while(1);

    User user;
    int found = 0;
    while (fread(&user, sizeof(User), 1, file))
    {
        if (user.id != idToDelete)
        {
            fwrite(&user, sizeof(User), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }

    if (found)
    {
        printf("\nUser with ID %d deleted successfully.....\n", idToDelete);
    }
    else
    {
        printf("\nUser with ID %d not found.\n", idToDelete);
    }
    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);
}

void createFileIfNotExists()
{
    FILE *file = fopen(FILENAME, "rb");
    if (!file)
    {
        file = fopen(FILENAME, "wb");
        if (file)
        {
            printf("\nFile created successfully.\n");
            fclose(file);
        }
        else{
            printf("\nError in creating file...\n");
        }
    }
    else
    {
        fclose(file);
    }
}

int main()
{
    createFileIfNotExists();
    int choice;
    
    while (1)
    {
        printf("\n--- Menu ---\n");
        printf("1. Add User\n");
        printf("2. Display All Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (!typeCheck(scanf("%d", &choice))){
            continue;
        }

        switch (choice)
        {
        case Add_user:
            createUser();
            break;
        case Display_user:
            readUsers();
            break;
        case Update_user:
            updateUser();
            break;
        case Delete_user:
            deleteUser();
            break;
        case Exit:
            printf("\nExiting...\n");
            exit(0);
        default:
            printf("\nInvalid choice! Try again.\n");
        }
    }
    return 0;
}
