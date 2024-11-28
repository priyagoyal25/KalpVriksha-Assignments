#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "users.txt"

// Define a struct for user data
typedef struct {
    int id;
    char name[100];
    int age;
} User;

// Function to check if a user ID already exists in the file
int isIDExists(int id) {
    FILE *file = fopen(FILENAME, "r");  // Open the file in read mode
    if (!file) {
        printf("\nError opening file!\n");
        return 0;
    }

    User user;
    while (fread(&user, sizeof(User), 1, file)) {
        if (user.id == id) {
            fclose(file);
            return 1;  // ID found, exists in the file
        }
    }

    fclose(file);
    return 0;  // ID not found, it's unique
}


// Function to create a new user and add it to the file with a unique ID
void createUser() {
    FILE *file = fopen(FILENAME, "a");  // Open the file in append mode
    if (!file) {
        printf("\nError opening file!\n");
        return;
    }

    User user;
    int idExists;
    
    do {
        printf("Enter User ID: ");
        scanf("%d", &user.id);
        
        // Check if ID already exists
        idExists = isIDExists(user.id);
        if (idExists) {
            printf("\nError: User ID %d already exists. Please enter a unique ID.\n", user.id);
        }
    } while (idExists);  // Repeat until a unique ID is entered

    getchar();  // Consume the newline character left by scanf
    printf("Enter Name: ");
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';  // Remove the newline character from name
    printf("Enter Age: ");
    scanf("%d", &user.age);

    fwrite(&user, sizeof(User), 1, file);  // Write the user to the file

    fclose(file);
    printf("\nUser added successfully.....\n");
}


// Function to read and display all users from the file
void readUsers() {
    FILE *file = fopen(FILENAME, "r");  // Open the file in read mode
    if (!file) {
        printf("\nError opening file!\n");
        return;
    }

    // Check if the file is empty
    fseek(file, 0, SEEK_END);  // Move file pointer to the end
    if (ftell(file) == 0) {
        printf("\nNo users are present in the file.\n");
        fclose(file);
        return;
    }

    rewind(file);  // Move file pointer back to the beginning

    User user;
    printf("\n--- List of Users ---\n");
    while (fread(&user, sizeof(User), 1, file)) {
        printf("ID: %d, Name: %s, Age: %d\n", user.id, user.name, user.age);
    }

    fclose(file);
}


// Function to update a user's details by ID
void updateUser() {
    FILE *file = fopen(FILENAME, "r+");  // Open the file in read/write mode
    if (!file) {
        printf("\nError opening file!\n");
        return;
    }

    int id;
    printf("\nEnter the ID of the user you want to update: ");
    scanf("%d", &id);

    User user;
    int found = 0;

    while (fread(&user, sizeof(User), 1, file)) {
        if (user.id == id) {
            found = 1;

            // Present options to the user
            int choice;
            printf("\nWhat would you like to update?\n");
            printf("1. Name\n");
            printf("2. Age\n");
            printf("3. Both Name and Age\n");
            printf("Enter your choice (1/2/3): ");
            scanf("%d", &choice);

            getchar();  // Clear the newline character left by scanf

            if (choice == 1 || choice == 3) {
                printf("Enter new Name: ");
                fgets(user.name, sizeof(user.name), stdin);
                user.name[strcspn(user.name, "\n")] = '\0';  // Remove newline character
            }

            if (choice == 2 || choice == 3) {
                printf("Enter new Age: ");
                scanf("%d", &user.age);
            }

            // Move file pointer back to overwrite the user's record
            fseek(file, -sizeof(User), SEEK_CUR);
            fwrite(&user, sizeof(User), 1, file);

            printf("\nUser updated successfully......\n");
            break;
        }
    }

    if (!found) {
        printf("\nUser with ID %d not found.\n", id);
    }

    fclose(file);
}


// Function to delete a user by their ID
void deleteUser() {
    FILE *file = fopen(FILENAME, "r");  // Open the file in read mode
    if (!file) {
        printf("\nError opening file!\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");  // Temporary file for storing updated data
    if (!tempFile) {
        printf("\nError creating temporary file!\n");
        fclose(file);
        return;
    }

    int idToDelete;
    printf("Enter the User ID to delete: ");
    scanf("%d", &idToDelete);

    User user;
    int found = 0;
    while (fread(&user, sizeof(User), 1, file)) {
        if (user.id != idToDelete) {
            fwrite(&user, sizeof(User), 1, tempFile);  // Write data that is not deleted
        } else {
            found = 1;
        }
    }

    if (found) {
        printf("\nUser with ID %d deleted successfully.....\n", idToDelete);
    } else {
        printf("\nUser with ID %d not found.\n", idToDelete);
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the updated data
    remove(FILENAME);
    rename("temp.txt", FILENAME);
}

// Function to create a new file if it doesn't exist
void createFileIfNotExists() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        file = fopen(FILENAME, "w");  // Create a new file if it doesn't exist
        if (file) {
            printf("File created successfully.\n");
            fclose(file);
        }
    } else {
        fclose(file);
    }
}

int main() {
    createFileIfNotExists();  // Create file if it doesn't exist

    int choice;
    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Add User\n");
        printf("2. Display All Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createUser();
                break;
            case 2:
                readUsers();
                break;
            case 3:
                updateUser();
                break;
            case 4:
                deleteUser();
                break;
            case 5:
                printf("\nExiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}