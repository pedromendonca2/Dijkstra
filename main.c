#include "PQ.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

struct item {
    int node;
    float distance;
};

typedef struct edge {
    int destiny;
    float weight;
} Edge;

typedef struct {
    Edge **edges;   // Lista de adjacências
    int *size;      // Número de arestas por nó
    int num_vertices; // Número total de vértices
} Graph;

// Funções do grafo
Graph* createGraph(int num_vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;

    graph->edges = malloc(num_vertices * sizeof(Edge*));
    graph->size = calloc(num_vertices, sizeof(int));

    for (int i = 0; i < num_vertices; i++) graph->edges[i] = NULL;
    return graph;
}

void addEdge(Graph *graph, int source, int destiny, float weight) {
    graph->size[source]++;
    graph->edges[source] = realloc(graph->edges[source], graph->size[source] * sizeof(Edge));
    graph->edges[source][graph->size[source] - 1] = (Edge){destiny, weight};
}

void freeGraph(Graph *graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        free(graph->edges[i]);
    }
    free(graph->edges);
    free(graph->size);
    free(graph);
}

// Função para reconstruir o caminho
void printPath(int node, int *predecessor) {
    if (predecessor[node] == -1) {
        printf("node_%d", node);
        return;
    }
    printPath(predecessor[node], predecessor);
    printf(" <- node_%d", node);
}

// Algoritmo de Dijkstra ajustado
void dijkstra(Graph *graph, int source) {
    float *distances = malloc(graph->num_vertices * sizeof(float));
    int *visited = calloc(graph->num_vertices, sizeof(int));
    int *predecessor = malloc(graph->num_vertices * sizeof(int));

    // Inicializar distâncias como infinito e predecessor como -1
    for (int i = 0; i < graph->num_vertices; i++) {
        distances[i] = FLT_MAX;
        predecessor[i] = -1;
    }
    distances[source] = 0.0;

    // Criar fila de prioridade
    PQ *pq = PQ_create(graph->num_vertices);
    Item *first = malloc(sizeof(Item));
    first->distance = 0.0;
    first->node = source;
    PQ_insert(pq, first);

    while (!PQ_is_empty(pq)) {
        Item *current = PQ_delmin(pq);
        int u = current->node;
        free(current);

        if (visited[u]) continue;
        visited[u] = 1;

        for (int i = 0; i < graph->size[u]; i++) {
            int v = graph->edges[u][i].destiny;
            float weight = graph->edges[u][i].weight;

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                predecessor[v] = u;

                Item *neighbor = malloc(sizeof(Item));
                neighbor->node = v;
                neighbor->distance = distances[v];
                PQ_insert(pq, neighbor);
            }
        }
    }

    // Criar lista para ordenação por distância
    int *order = malloc(graph->num_vertices * sizeof(int));
    for (int i = 0; i < graph->num_vertices; i++) order[i] = i;

    // Ordenar os nós pela distância
    for (int i = 0; i < graph->num_vertices - 1; i++) {
        for (int j = i + 1; j < graph->num_vertices; j++) {
            if (distances[order[i]] > distances[order[j]]) {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    // Exibir resultados
    for (int i = 0; i < graph->num_vertices; i++) {
        int node = order[i];
        printf("SHORTEST PATH TO node_%d: ", node);
        printPath(node, predecessor);
        printf(" (Distance: %.2f)\n", distances[node]);
    }

    free(distances);
    free(visited);
    free(predecessor);
    free(order);
    PQ_destroy(pq);
}

// Função principal
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo de entrada>\n", argv[0]);
        return 1;
    }

    char *arquivo = argv[1];
    FILE *file = fopen(arquivo, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    int source;
    fscanf(file, "node_%d\n", &source);

    int num_vertices = 0;
    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        num_vertices++;
    }

    rewind(file);
    fscanf(file, "node_%d\n", &source);

    Graph *graph = createGraph(num_vertices);

    for (int i = 0; i < num_vertices; i++) {
        int v;
        float w1, w2, w3, w4;
        fscanf(file, "node_%d, %f, %f, %f, %f\n", &v, &w1, &w2, &w3, &w4);

        for (int j = 0; j < num_vertices; j++) {
            if (i != j) {
                float weight = (j == 0) ? w1 : (j == 1) ? w2 : (j == 2) ? w3 : w4;
                if (weight > 0) {
                    addEdge(graph, i, j, weight);
                }
            }
        }
    }

    fclose(file);

    dijkstra(graph, source);

    freeGraph(graph);

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_NODES 100

typedef struct {
    int node;
    float weight;
} Edge;

typedef struct {
    Edge edges[MAX_NODES];
    int edge_count;
} Node;

Node graph[MAX_NODES];
float distances[MAX_NODES];
int previous[MAX_NODES];
int visited[MAX_NODES];
int num_nodes;

void initialize_graph(int nodes) {
    num_nodes = nodes;
    for (int i = 0; i < num_nodes; i++) {
        graph[i].edge_count = 0;
        distances[i] = FLT_MAX;
        previous[i] = -1;
        visited[i] = 0;
    }
}

void add_edge(int src, int dest, float weight) {
    graph[src].edges[graph[src].edge_count].node = dest;
    graph[src].edges[graph[src].edge_count].weight = weight;
    graph[src].edge_count++;
}

int extract_min() {
    int min_index = -1;
    float min_distance = FLT_MAX;

    for (int i = 0; i < num_nodes; i++) {
        if (!visited[i] && distances[i] < min_distance) {
            min_distance = distances[i];
            min_index = i;
        }
    }

    return min_index;
}

void dijkstra(int start) {
    distances[start] = 0;

    for (int i = 0; i < num_nodes; i++) {
        int u = extract_min();
        if (u == -1) break;

        visited[u] = 1;

        for (int j = 0; j < graph[u].edge_count; j++) {
            int v = graph[u].edges[j].node;
            float weight = graph[u].edges[j].weight;

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
            }
        }
    }
}

void print_path(int node, FILE *output) {
    if (node == -1) return;
    print_path(previous[node], output);
    fprintf(output, "node_%d ", node);
}

void read_input(const char *filename, int *start_node) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo de entrada");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", start_node);

    int i = 0;
    while (fscanf(file, "node_%*d") != EOF) {
        for (int j = 0; j < num_nodes; j++) {
            float weight;
            fscanf(file, ",%f", &weight);
            if (weight > 0) {
                add_edge(i, j, weight);
            }
        }
        i++;
    }

    fclose(file);
}

void write_output(const char *filename, int start_node) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erro ao abrir o arquivo de saída");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_nodes; i++) {
        if (i != start_node) {
            fprintf(file, "SHORTEST PATH TO node_%d: ", i);
            print_path(i, file);
            fprintf(file, "(Distance: %.2f)\n", distances[i]);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_entrada> <arquivo_saida>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int start_node;

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Erro ao abrir o arquivo de entrada");
        return EXIT_FAILURE;
    }

    fscanf(input_file, "%d", &num_nodes);
    fclose(input_file);

    initialize_graph(num_nodes);
    read_input(argv[1], &start_node);
    dijkstra(start_node);
    write_output(argv[2], start_node);

    return EXIT_SUCCESS;
}

*/