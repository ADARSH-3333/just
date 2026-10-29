#include <stdio.h>

#define MAX 100

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    printf("Array after Max Heap construction: ");
    printArray(arr, n);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int main() {
    int priorities[MAX];
    int n;

    printf("Enter the number of task priorities: ");
    scanf("%d", &n);

    printf("Enter the %d numerical priorities: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &priorities[i]);
    }

    printf("\nOriginal input array: ");
    printArray(priorities, n);

    heapSort(priorities, n);

    printf("Array after Heap Sort (Ascending Order): ");
    printArray(priorities, n);

    return 0;
}

