#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define MAX_WORD_LEN 50

struct Node {
    char word[MAX_WORD_LEN];
    struct Node* next;
};

struct Node* hashTable[TABLE_SIZE];

int calculateHash(char* word) {
    int sum = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        sum += word[i];
    }
    return sum % TABLE_SIZE;
}

void insertWord(char* newWord) {
    int index = calculateHash(newWord);

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->word, newWord);
    
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

int searchWord(char* findWord) {
    int index = calculateHash(findWord);
    struct Node* temp = hashTable[index];

    while (temp != NULL) {
        if (strcmp(temp->word, findWord) == 0) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void displayHashTable() {
    printf("\n====== DICTIONARY HASH TABLE GRAPH ======\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Slot [%d]:", i);
        struct Node* temp = hashTable[i];
        
        if (temp == NULL) {
            printf(" NULL");
        } else {
            while (temp != NULL) {
                printf(" -> %s", temp->word);
                temp = temp->next;
            }
        }
        printf("\n");
    }
    printf("=========================================\n");
}

int main() {
    int choice, n;
    char inputWord[MAX_WORD_LEN];

    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    do {
        printf("\n====== SPELL-CHECKER DICTIONARY MENU ======\n");
        printf("1. Insert a Set of Valid Words\n");
        printf("2. Search / Spell-Check a Word\n");
        printf("3. Display Full Hash Table Chains\n");
        printf("4. Exit Program\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("How many words do you want to load? ");
                scanf("%d", &n);
                printf("Enter %d words:\n", n);
                for (int i = 0; i < n; i++) {
                    printf("Word %d: ", i + 1);
                    scanf("%s", inputWord);
                    insertWord(inputWord);
                }
                printf("Words uploaded successfully!\n");
                break;

            case 2:
                printf("Enter word to search/spell-check: ");
                scanf("%s", inputWord);
                if (searchWord(inputWord)) {
                    printf("Spelled correctly! '%s' exists in the dictionary.\n", inputWord);
                } else {
                    printf("Spell check failed: '%s' NOT found in dictionary.\n", inputWord);
                }
                break;

            case 3:
                displayHashTable();
                break;

            case 4:
                printf("Exiting dictionary application. Rest well and good luck tomorrow!\n");
                break;

            default:
                printf("Invalid choice! Please select a valid option (1-4).\n");
        }
    } while (choice != 4);

    return 0;
}

