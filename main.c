
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char name[100];
    struct Node *next;
};

struct Node *head = NULL;

// Add a file
void addFile() {
    struct Node *newNode =
        (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter file name: ");
    scanf(" %99[^\n]", newNode->name);

    newNode->next = head;
    head = newNode;

    printf("File added successfully!\n");
}

// Display all files
void displayFiles() {
    struct Node *temp = head;

    if (temp == NULL) {
        printf("No files found!\n");
        return;
    }

    printf("\n--- File List ---\n");

    while (temp != NULL) {
        printf("File: %s\n", temp->name);
        temp = temp->next;
    }
}

// Search for a file
void searchFile() {
    char name[100];
    struct Node *temp = head;

    printf("Enter file name to search: ");
    scanf(" %99[^\n]", name);

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("File found: %s\n", name);
            return;
        }

        temp = temp->next;
    }

    printf("File not found!\n");
}

// Delete a file
void deleteFile() {
    char name[100];

    printf("Enter file name to delete: ");
    scanf(" %99[^\n]", name);

    struct Node *temp = head;
    struct Node *prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            if (prev == NULL) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }

            free(temp);
            printf("File deleted successfully!\n");
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("File not found!\n");
}

// Main function
int main() {
    int choice;

    do {
        printf("\n=== File-Folder Organization System ===\n");
        printf("1. Add File\n");
        printf("2. Display Files\n");
        printf("3. Search File\n");
        printf("4. Delete File\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                addFile();
                break;

            case 2:
                displayFiles();
                break;

            case 3:
                searchFile();
                break;

            case 4:
                deleteFile();
                break;

            case 0:
                printf("Program closed.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 0);

    while (head != NULL) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
