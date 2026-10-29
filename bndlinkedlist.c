#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL 100

struct Node {
    char url[MAX_URL];
    struct Node* prev;
    struct Node* next;
};

struct Node* head = NULL;
struct Node* current = NULL;

void clearForwardHistory(struct Node* startNode) {
    if (startNode == NULL) return;
    
    struct Node* temp = startNode;
    while (temp != NULL) {
        struct Node* nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
}

void visitPage() {
    char newUrl[MAX_URL];
    printf("Enter webpage URL/Name to visit: ");
    scanf("%s", newUrl);

    if (current != NULL && current->next != NULL) {
        clearForwardHistory(current->next);
        current->next = NULL;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->url, newUrl);
    newNode->next = NULL;
    newNode->prev = NULL;

    if (head == NULL) {
        head = newNode;
        current = newNode;
    } else {
        current->next = newNode;
        newNode->prev = current;
        current = newNode;
    }
    printf("Successfully visited: %s\n", current->url);
}

void moveBackward() {
    if (current == NULL || current->prev == NULL) {
        printf("Cannot go back! No previous webpage in history.\n");
        return;
    }
    current = current->prev;
    printf("Moved back to: %s\n", current->url);
}

void moveForward() {
    if (current == NULL || current->next == NULL) {
        printf("Cannot go forward! No next webpage in history.\n");
        return;
    }
    current = current->next;
    printf("Moved forward to: %s\n", current->url);
}

void displayCurrentPage() {
    if (current == NULL) {
        printf("No webpage currently open.\n");
    } else {
        printf("Current Webpage: [%s]\n", current->url);
    }
}

void displayHistory() {
    if (head == NULL) {
        printf("Browsing history is completely empty.\n");
        return;
    }

    printf("\n--- COMPLETE BROWSING HISTORY ---\n");
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp == current) {
            printf(" -> %s (CURRENT VIEW)", temp->url);
        } else {
            printf(" -> %s", temp->url);
        }
        temp = temp->next;
    }
    printf("\n---------------------------------\n");
}

int main() {
    int choice;

    do {
        printf("\n====== BROWSER HISTORY MENU ======\n");
        printf("1. Visit New Webpage\n");
        printf("2. Move to Previous Webpage (Back)\n");
        printf("3. Move to Next Webpage (Forward)\n");
        printf("4. Display Current Webpage\n");
        printf("5. Display Complete Browsing History\n");
        printf("6. Exit Lab Program\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: visitPage(); break;
            case 2: moveBackward(); break;
            case 3: moveForward(); break;
            case 4: displayCurrentPage(); break;
            case 5: displayHistory(); break;
            case 6: printf("Exiting browser simulation. Good luck in the exam!\n"); break;
            default: printf("Invalid choice! Please choose a number between 1 and 6.\n");
        }
    } while (choice != 6);

    clearForwardHistory(head);
    return 0;
}

