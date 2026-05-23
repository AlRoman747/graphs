#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int** matrix;
    int nodes;
    int edges;
} Graph;

Graph* create_graph(int nodes, int edges) {
    Graph* graph = malloc(sizeof(Graph));
    graph->nodes = nodes;
    graph->edges = edges;
    graph->matrix = malloc(nodes * sizeof(int*));
    for (int i = 0; i < nodes; i++) {
        graph->matrix[i] = calloc(edges, sizeof(int));
    }
    return graph;
}

void add_node(Graph* graph, int node, int* neighbours, int neighbours_count, int* current_edge) {
    if (node >= graph->nodes) {
        int new_nodes = node + 1;
        graph->matrix = realloc(graph->matrix, new_nodes * sizeof(int*));
        for (int i = graph->nodes; i < new_nodes; i++) {
            graph->matrix[i] = calloc(graph->edges, sizeof(int));
        }
        graph->nodes = new_nodes;
    }
    for (int i = 0; i < neighbours_count; i++) {
        int edge = *current_edge;
        if (edge >= graph->edges) {
            int new_edges = edge + 1;
            for (int j = 0; j < graph->nodes; j++) {
                graph->matrix[j] = realloc(graph->matrix[j], new_edges * sizeof(int));
                for (int k = graph->edges; k < new_edges; k++) {
                    graph->matrix[j][k] = 0;
                }
            }
            graph->edges = new_edges;
        }
        graph->matrix[node][edge] = 1;
        if (neighbours[i] >= graph->nodes) {
            int new_nodes = neighbours[i] + 1;
            graph->matrix = realloc(graph->matrix, new_nodes * sizeof(int*));
            for (int j = graph->nodes; j < new_nodes; j++) {
                graph->matrix[j] = calloc(graph->edges, sizeof(int));
            }
            graph->nodes = new_nodes;
        }
        graph->matrix[neighbours[i]][edge] = 1;
        (*current_edge)++;
    }
}

void merge_nodes(Graph* graph, int node_one, int node_two, int* edge) {
    if (node_one >= graph->nodes || node_two >= graph->nodes) {
        printf("Error: Node doesn't exist\n");
        return;
    }
    if (*edge >= graph->edges) {
        int new_edges = *edge + 1;
        for (int j = 0; j < graph->nodes; j++) {
            graph->matrix[j] = realloc(graph->matrix[j], new_edges * sizeof(int));
            for (int k = graph->edges; k < new_edges; k++) {
                graph->matrix[j][k] = 0;
            }
        }
        graph->edges = new_edges;
    }
    graph->matrix[node_one][*edge] = 1;
    graph->matrix[node_two][*edge] = 1;
    (*edge)++;
}

void print_graph(Graph* graph) {
    printf("Graph (%d nodes, %d edges):\n", graph->nodes, graph->edges);
    for (int i = 0; i < graph->nodes; i++) {
        printf("Node %d: ", i);
        for (int j = 0; j < graph->edges; j++) {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}


void free_graph(Graph* graph) {
    for (int i = 0; i < graph->nodes; i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);
    free(graph);
}

int main() {
    Graph* graph = create_graph(4, 3);
    int current_edge = 0;

    int neighbours[] = {1, 2, 3};
    add_node(graph, 0, neighbours, sizeof(neighbours) / sizeof(neighbours[0]), &current_edge);
    print_graph(graph);
    printf("\n");

    merge_nodes(graph, 1, 3, &current_edge);
    print_graph(graph);
    printf("\n");

    int neighbours2[] = {3};
    add_node(graph, 4, neighbours2, sizeof(neighbours2) / sizeof(neighbours2[0]), &current_edge);
    print_graph(graph);

    free_graph(graph);
    return 0;
}
