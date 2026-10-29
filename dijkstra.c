#include <stdio.h>
#include <limits.h>

#define MAX 20
#define INF INT_MAX

int graph[MAX][MAX];
int dist[MAX];
int visited[MAX];
int parent[MAX];
int totalVertices;

int findMinDistanceVertex() {
    int min = INF, min_index = -1;
    
    for (int v = 0; v < totalVertices; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printPath(int currentVertex) {
    if (parent[currentVertex] == -1) {
        printf("%d", currentVertex);
        return;
    }
    printPath(parent[currentVertex]);
    printf(" -> %d", currentVertex);
}

void dijkstra(int source, int destination) {
    for (int i = 0; i < totalVertices; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    
    dist[source] = 0;
    
    for (int count = 0; count < totalVertices - 1; count++) {
        int u = findMinDistanceVertex();
        
        if (u == -1 || dist[u] == INF) break;
        
        visited[u] = 1;
        
        for (int v = 0; v < totalVertices; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }
    
    printf("\n--- RESULT ANALYSIS ---\n");
    if (dist[destination] == INF) {
        printf("Destination vertex %d is UNREACHABLE from source vertex %d.\n", destination, source);
    } else {
        printf("Total Shortest Distance: %d\n", dist[destination]);
        printf("Shortest Path: ");
        printPath(destination);
        printf("\n");
    }
}

int main() {
    int source, destination;
    
    printf("Enter total number of vertices (Distribution Centres): ");
    scanf("%d", &totalVertices);
    
    printf("Enter the weighted adjacency matrix (%dx%d):\n", totalVertices, totalVertices);
    printf("(Enter 0 if there is no direct road between two nodes)\n");
    for (int i = 0; i < totalVertices; i++) {
        for (int j = 0; j < totalVertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    printf("\nEnter the Source vertex: ");
    scanf("%d", &source);
    printf("Enter the Destination vertex: ");
    scanf("%d", &destination);
    
    if (source < 0 || source >= totalVertices || destination < 0 || destination >= totalVertices) {
        printf("Error: Invalid vertex selections!\n");
        return 1;
    }
    
    dijkstra(source, destination);
    
    return 0;
}

