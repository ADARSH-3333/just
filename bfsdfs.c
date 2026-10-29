#include <stdio.h>

#define MAX 20

int adj[MAX][MAX];
int visited[MAX];
int totalVertices;

int queue[MAX];
int front = -1, rear = -1;

void enqueue(int val) {
    if (front == -1) front = 0;
    queue[++rear] = val;
}

int dequeue() {
    int val = queue[front];
    if (front == rear) {
        front = rear = -1;
    } else {
        front++;
    }
    return val;
}

int isQueueEmpty() {
    return front == -1;
}

void resetVisited() {
    for (int i = 0; i < totalVertices; i++) {
        visited[i] = 0;
    }
}

void printUnreachable(int start) {
    int foundUnreachable = 0;
    for (int i = 0; i < totalVertices; i++) {
        if (visited[i] == 0) {
            printf("%d ", i);
            foundUnreachable = 1;
        }
    }
    if (!foundUnreachable) {
        printf("None (All computers are connected!)");
    }
    printf("\n");
}

void performBFS(int start) {
    resetVisited();
    printf("BFS Traversal: ");
    
    enqueue(start);
    visited[start] = 1;
    
    while (!isQueueEmpty()) {
        int curr = dequeue();
        printf("%d ", curr);
        
        for (int i = 0; i < totalVertices; i++) {
            if (adj[curr][i] == 1 && visited[i] == 0) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
    
    printf("Vertices unreachable via BFS from %d: ", start);
    printUnreachable(start);
}

void recursiveDFS(int curr) {
    printf("%d ", curr);
    visited[curr] = 1;
    
    for (int i = 0; i < totalVertices; i++) {
        if (adj[curr][i] == 1 && visited[i] == 0) {
            recursiveDFS(i);
        }
    }
}

void performDFS(int start) {
    resetVisited();
    printf("DFS Traversal: ");
    recursiveDFS(start);
    printf("\n");
    
    printf("Vertices unreachable via DFS from %d: ", start);
    printUnreachable(start);
}

int main() {
    int edges, u, v, startVertex;
    
    printf("Enter the total number of vertices (computers): ");
    scanf("%d", &totalVertices);
    
    for (int i = 0; i < totalVertices; i++) {
        for (int j = 0; j < totalVertices; j++) {
            adj[i][j] = 0;
        }
    }
    
    printf("Enter the number of connections (edges): ");
    scanf("%d", &edges);
    
    printf("Enter edges connecting two vertices (format: source destination):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;
    }
    
    printf("\nEnter the starting vertex for traversals: ");
    scanf("%d", &startVertex);
    
    if (startVertex < 0 || startVertex >= totalVertices) {
        printf("Invalid starting vertex!\n");
        return 1;
    }
    
    printf("\n--- RUNNING NETWORK ANALYSIS ---\n");
    performBFS(startVertex);
    printf("\n");
    performDFS(startVertex);
    
    return 0;
}

