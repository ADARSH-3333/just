#include <stdio.h>

#define MAX 100

struct Student {
    int regNo;
    int marks;
};

int comparisonCount = 0;

int partition(struct Student arr[], int low, int high) {
    struct Student pivot = arr[high]; 
    int i = (low - 1); 
    struct Student temp;

    for (int j = low; j < high; j++) {
        comparisonCount++;
        
        if (arr[j].marks < pivot.marks) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return (i + 1);
}

void quickSort(struct Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    struct Student records[MAX];
    int n;

    printf("Enter the number of student records: ");
    scanf("%d", &n);

    printf("Enter register number and total marks for each student:\n");
    for (int i = 0; i < n; i++) {
        printf("Student %d (RegNo Marks): ", i + 1);
        scanf("%d %d", &records[i].regNo, &records[i].marks);
    }

    quickSort(records, 0, n - 1);

    printf("\n--- SORTED STUDENT RECORDS (ASCENDING ORDER) ---\n");
    printf("Register No\tTotal Marks\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\n", records[i].regNo, records[i].marks);
    }
    printf("---------------------------------------------\n");
    
    printf("Total number of comparisons performed: %d\n", comparisonCount);

    return 0;
}

