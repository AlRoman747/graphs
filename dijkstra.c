#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define inf 9999999

typedef struct {
    int **matrix;
    int nodes;
} Graph;

Graph* init_graph(int nodes) {
    Graph* graph = malloc(sizeof(Graph));
    graph->nodes = nodes;
    graph->matrix = (int**)malloc(nodes * sizeof(int*));
    for (int i = 0; i < nodes; i++) {
        graph->matrix[i] = (int*)malloc(nodes * sizeof(int));
    }
    printf("init your graph\n");
    for (int i=0; i < nodes; i++) {
        for (int j=0; j < nodes; j++) {
            int distance;
            if (i == j) {
                graph->matrix[i][j] = 0;
                break;
            }
            printf("init distance btw %d and %d\n", i, j);
            scanf("%d", &distance);
            graph->matrix[i][j] = distance;
            graph->matrix[j][i] = distance;
        }
    }
    return graph;
}

void print_graph(Graph* graph) {
    for (int i=0; i<graph->nodes; i++) {
        for (int j=0; j<graph->nodes;j++) {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}

int index_min_from_arr(int* arr) {
    int mini = inf;
    int res = 0;
    int len_arr = sizeof(arr) / sizeof(arr[0]);
    for (int i=0; i < len_arr; i++) {
        if (arr[i] <= mini) {
            mini = arr[i];
            res = i;
    }
    }
    return res;
}

int dijkstra(Graph* graph, int node1, int node2) {
    int distances[graph->nodes];
    int visited[graph->nodes];

    for (int i=0; i < graph->nodes; i++) {
        if (node1 == i) {distances[i] = 0; continue;}
        if (graph->matrix[node1][i] != 0) { distances[i] = graph->matrix[node1][i];}
        else {
            distances[i] = inf;
        }
        visited[i] = 0;
    }

    for (int i=0; i < graph->nodes; i++) {
        int mini=inf;
        int u=-1;
        for (int j = 0; j < graph->nodes;j++) {
            if (!visited[j] && distances[j] <= mini) {
                mini = distances[j];
                u = i;
        }
    }
        if (u == -1) break;
        visited[u] = 1;
        for (int j = 0; j < graph->nodes;j++) {
            if (!visited[j] && graph->matrix[u][j] != 0
                && (distances[u] + graph->matrix[u][j] < distances[j])) {
                    distances[j] = distances[u] + graph->matrix[u][j];
                }
        }
    }
    return distances[node2];
}

int main() {

    Graph* graph = init_graph(4);
    print_graph(graph);
    printf("\n");
    int res = dijkstra(graph, 0, 3);
    printf("%d", res);
    return 0;
}
