#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "djikstra.h"
#include <time.h>

int main(int argc, char *argv[]) {

    clock_t inicio, fim;
    double tempo_execucao;

    inicio = clock();


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

    fim = clock();

    tempo_execucao = ((double)(fim-inicio)/ CLOCKS_PER_SEC);
    printf("Tempo de execução: %f segundos\n",tempo_execucao);

    return 0;
}