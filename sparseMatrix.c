#include <stdio.h>

#define MAX 100

struct Element {
    int row;
    int col;
    int val;
};

int readMatrix(struct Element triplet[], int r, int c) {
    int value, k = 1;
    
    triplet[0].row = r;
    triplet[0].col = c;
    
    printf("Enter the matrix elements line by line:\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &value);
            if (value != 0) {
                triplet[k].row = i;
                triplet[k].col = j;
                triplet[k].val = value;
                k++;
            }
        }
    }
    triplet[0].val = k - 1;
    return k - 1;
}

void displayTriplet(struct Element triplet[]) {
    int total_elements = triplet[0].val;
    printf("\nRow\tCol\tValue\n");
    printf("------------------------\n");
    printf("%d\t%d\t%d (Metadata)\n", triplet[0].row, triplet[0].col, triplet[0].val);
    printf("------------------------\n");
    for (int i = 1; i <= total_elements; i++) {
        printf("%d\t%d\t%d\n", triplet[i].row, triplet[i].col, triplet[i].val);
    }
}

void transposeMatrix(struct Element src[], struct Element dest[]) {
    int k = 1;
    
    dest[0].row = src[0].col;
    dest[0].col = src[0].row;
    dest[0].val = src[0].val;
    
    int total_cols = src[0].col;
    int total_elements = src[0].val;
    
    for (int c = 0; c < total_cols; c++) {
        for (int i = 1; i <= total_elements; i++) {
            if (src[i].col == c) {
                dest[k].row = src[i].col;
                dest[k].col = src[i].row;
                dest[k].val = src[i].val;
                k++;
            }
        }
    }
}

void addMatrices(struct Element A[], struct Element B[], struct Element C[]) {
    if (A[0].row != B[0].row || A[0].col != B[0].col) {
        printf("\nError: Matrices must have identical dimensions to be added!\n");
        C[0].val = 0;
        return;
    }
    
    C[0].row = A[0].row;
    C[0].col = A[0].col;
    
    int i = 1, j = 1, k = 1;
    int numA = A[0].val;
    int numB = B[0].val;
    
    while (i <= numA && j <= numB) {
        if (A[i].row == B[j].row) {
            if (A[i].col == B[j].col) {
                int sum = A[i].val + B[j].val;
                if (sum != 0) {
                    C[k].row = A[i].row;
                    C[k].col = A[i].col;
                    C[k].val = sum;
                    k++;
                }
                i++;
                j++;
            }
            else if (A[i].col < B[j].col) {
                C[k] = A[i];
                i++; k++;
            }
            else {
                C[k] = B[j];
                j++; k++;
            }
        } 
        else if (A[i].row < B[j].row) {
            C[k] = A[i];
            i++; k++;
        } 
        else {
            C[k] = B[j];
            j++; k++;
        }
    }
    
    while (i <= numA) {
        C[k] = A[i];
        i++; k++;
    }
    
    while (j <= numB) {
        C[k] = B[j];
        j++; k++;
    }
    
    C[0].val = k - 1;
}

int main() {
    struct Element matrixA[MAX], matrixB[MAX], transposedA[MAX], resultSum[MAX];
    int r1, c1, r2, c2;
    
    printf("Enter rows and columns for Matrix A: ");
    scanf("%d %d", &r1, &c1);
    readMatrix(matrixA, r1, c1);
    printf("\n--- Triplet Form of Matrix A ---");
    displayTriplet(matrixA);
    
    transposeMatrix(matrixA, transposedA);
    printf("\n--- Transpose of Matrix A (in Triplet Form) ---");
    displayTriplet(transposedA);
    
    printf("\nEnter rows and columns for Matrix B: ");
    scanf("%d %d", &r2, &c2);
    readMatrix(matrixB, r2, c2);
    printf("\n--- Triplet Form of Matrix B ---");
    displayTriplet(matrixB);
    
    addMatrices(matrixA, matrixB, resultSum);
    if (resultSum[0].val > 0) {
        printf("\n--- Result of Addition (A + B in Triplet Form) ---");
        displayTriplet(resultSum);
    }
    
    return 0;
}

