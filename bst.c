#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        printf("Admission number %d already exists! Must be unique.\n", value);
    }
    return root;
}

struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

struct Node* findMin(struct Node* root) {
    struct Node* current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

struct Node* findMax(struct Node* root) {
    struct Node* current = root;
    while (current && current->right != NULL) {
        current = current->right;
    }
    return current;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } 
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = findMin(root->right);
        
        root->data = temp->data;
        
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int main() {
    struct Node* root = NULL;
    int choice, value, n;

    do {
        printf("\n====== STUDENT RECORD BST MENU ======\n");
        printf("1. Insert a Sequence of Admission Numbers\n");
        printf("2. Search for an Admission Number\n");
        printf("3. Display All Tree Traversals\n");
        printf("4. Find Min & Max Admission Numbers\n");
        printf("5. Delete an Admission Number\n");
        printf("6. Exit Program\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("How many admission numbers to insert? ");
                scanf("%d", &n);
                printf("Enter %d numbers: ", n);
                for (int i = 0; i < n; i++) {
                    scanf("%d", &value);
                    root = insert(root, value);
                }
                printf("Sequence inserted successfully.\n");
                break;

            case 2:
                printf("Enter admission number to search: ");
                scanf("%d", &value);
                if (search(root, value) != NULL) {
                    printf("Record found: Admission number %d exists in the system.\n", value);
                } else {
                    printf("Record not found: Admission number %d does not exist.\n", value);
                }
                break;

            case 3:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    printf("\nPreorder Traversal  : "); preorder(root);
                    printf("\nInorder Traversal   : "); inorder(root);
                    printf("\nPostorder Traversal : "); postorder(root);
                    printf("\n");
                }
                break;

            case 4:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    printf("Minimum Admission Number: %d\n", findMin(root)->data);
                    printf("Maximum Admission Number: %d\n", findMax(root)->data);
                }
                break;

            case 5:
                printf("Enter admission number to delete: ");
                scanf("%d", &value);
                if (search(root, value) != NULL) {
                    root = deleteNode(root, value);
                    printf("Successfully deleted admission number %d.\n", value);
                } else {
                    printf("Action failed: Admission number %d not found.\n", value);
                }
                break;

            case 6:
                printf("Exiting program. Good luck in your DSA exam tomorrow!\n");
                break;

            default:
                printf("Invalid choice! Choose a number between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}

