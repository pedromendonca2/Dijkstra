#include "PQ.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

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
void printPath(int node, int *predecessor, FILE *out_file) {
    if (predecessor[node] == -1) {
        fprintf(out_file, "node_%d", node);
        return;
    }
    fprintf(out_file, "node_%d <- ", node);
    printPath(predecessor[node], predecessor, out_file);
}

// Algoritmo de Dijkstra
void dijkstra(Graph *graph, int source, FILE *out_file) {
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
    PQ *pq = PQ_create((int)pow(graph->num_vertices, 2));
    //PQ *pq = PQ_create(graph->num_vertices);

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
            if (distances[order[i]] > distances[order[j]] || 
               (distances[order[i]] == distances[order[j]] && order[i] > order[j])) {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    // Exibir resultados
    for (int i = 0; i < graph->num_vertices; i++) {
        int node = order[i];
        fprintf(out_file, "SHORTEST PATH TO node_%d: ", node);
        printPath(node, predecessor, out_file);
        fprintf(out_file, " (Distance: %.2f)\n", distances[node]);
    }

    free(distances);
    free(visited);
    free(predecessor);
    free(order);
    PQ_destroy(pq);
}

// Função principal
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <arquivo de entrada> <arquivo de saída>\n", argv[0]);
        return 1;
    }

    char *arquivo_entrada = argv[1];
    char *arquivo_saida = argv[2];

    FILE *in_file = fopen(arquivo_entrada, "r");
    if (!in_file) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    FILE *out_file = fopen(arquivo_saida, "w");
    if (!out_file) {
        perror("Erro ao abrir o arquivo de saída");
        fclose(in_file);
        return 1;
    }

    int source;
    fscanf(in_file, "node_%d\n", &source);

    int num_vertices = 0;
    char linha[65536];
    while (fgets(linha, sizeof(linha), in_file)) {
        if (strlen(linha) > 1) num_vertices++;
    }

    rewind(in_file);
    fscanf(in_file, "node_%d\n", &source);

    Graph *graph = createGraph(num_vertices);

    for (int i = 0; i < num_vertices; i++) {
        int v;
        fscanf(in_file, "node_%d", &v);

        for (int j = 0; j < num_vertices; j++) {
            if (i != j) {
                float weight = 0.0;
                fscanf(in_file, ", %f", &weight);
                fscanf(in_file, "%*[^,\n]");
                if (weight > 0) addEdge(graph, i, j, weight);
            }
        }

        fscanf(in_file, "\n");
    }

    fclose(in_file);

    dijkstra(graph, source, out_file);

    fclose(out_file);
    freeGraph(graph);

    return 0;
}