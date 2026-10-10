
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Linked List for files
struct File {
    char name[MAX];
    struct File *next;
};

// Tree Node for folders
struct Folder {
    char name[MAX];
    struct Folder *firstChild;
    struct Folder *nextSibling;
    struct File *files;
};

struct Folder *createFolder(const char *name) {
    struct Folder *folder =
        (struct Folder *)malloc(sizeof(struct Folder));

    if (folder == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    strcpy(folder->name, name);
    folder->firstChild = NULL;
    folder->nextSibling = NULL;
    folder->files = NULL;

    return folder;
}

// Find a folder by name
struct Folder *findFolder(struct Folder *root,
                          const char *name) {
    if (root == NULL)
        return NULL;

    if (strcmp(root->name, name) == 0)
        return root;

    struct Folder *found =
        findFolder(root->firstChild, name);

    if (found != NULL)
        return found;

    return findFolder(root->nextSibling, name);
}

// Add a subfolder
void addFolder(struct Folder *root) {
    char parentName[MAX], childName[MAX];

    printf("Enter parent folder name (Root for main folder): ");
    scanf(" %99[^\n]", parentName);

    struct Folder *parent = findFolder(root, parentName);

    if (parent == NULL) {
        printf("Parent folder not found!\n");
        return;
    }

    printf("Enter new folder name: ");
    scanf(" %99[^\n]", childName);

    if (findFolder(root, childName) != NULL) {
        printf("Folder name already exists!\n");
        return;
    }

    struct Folder *child = createFolder(childName);
    child->nextSibling = parent->firstChild;
    parent->firstChild = child;

    printf("Folder created successfully!\n");
}

// Add file to a folder
void addFile(struct Folder *root) {
    char folderName[MAX], fileName[MAX];

    printf("Enter folder name: ");
    scanf(" %99[^\n]", folderName);

    struct Folder *folder = findFolder(root, folderName);

    if (folder == NULL) {
        printf("Folder not found!\n");
        return;
    }

    printf("Enter file name: ");
    scanf(" %99[^\n]", fileName);

    struct File *file =
        (struct File *)malloc(sizeof(struct File));

    if (file == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    strcpy(file->name, fileName);
    file->next = folder->files;
    folder->files = file;

    printf("File added successfully!\n");
}

// Display folders recursively
void displayTree(struct Folder *root, int level) {
    if (root == NULL)
        return;

    for (int i = 0; i < level; i++)
        printf("    ");

    printf("[Folder] %s\n", root->name);

    struct File *file = root->files;

    while (file != NULL) {
        for (int i = 0; i <= level; i++)
            printf("    ");

        printf("[File] %s\n", file->name);
        file = file->next;
    }

    displayTree(root->firstChild, level + 1);
    displayTree(root->nextSibling, level);
}

// Search for a file or folder
void searchItem(struct Folder *root) {
    char name[MAX];

    printf("Enter file or folder name: ");
    scanf(" %99[^\n]", name);

    struct Folder *folder = findFolder(root, name);

    if (folder != NULL) {
        printf("Folder found: %s\n", folder->name);
        return;
    }

    // Search files in the tree
    struct Folder *stack[1000];
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        struct Folder *current = stack[top--];

        struct File *file = current->files;

        while (file != NULL) {
            if (strcmp(file->name, name) == 0) {
                printf("File found in folder: %s\n",
                       current->name);
                return;
            }
            file = file->next;
        }

        struct Folder *child = current->firstChild;

        while (child != NULL) {
            if (top < 999)
                stack[++top] = child;

            child = child->nextSibling;
        }
    }

    printf("File or folder not found!\n");
}

// Free allocated memory
void freeTree(struct Folder *root) {
    if (root == NULL)
        return;

    freeTree(root->firstChild);
    freeTree(root->nextSibling);

    struct File *file = root->files;

    while (file != NULL) {
        struct File *temp = file;
        file = file->next;
        free(temp);
    }

    free(root);
}

int main() {
    struct Folder *root = createFolder("Root");
    int choice;

    do {
        printf("\n=== File-Folder Organization System ===\n");
        printf("1. Create Folder\n");
        printf("2. Add File\n");
        printf("3. Display Folders and Files\n");
        printf("4. Search File or Folder\n");
        printf("0. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                addFolder(root);
                break;

            case 2:
                addFile(root);
                break;

            case 3:
                displayTree(root, 0);
                break;

            case 4:
                searchItem(root);
                break;

            case 0:
                printf("Program closed.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 0);

    freeTree(root);
    return 0;
}

