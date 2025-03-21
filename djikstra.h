/*
    Autores: Pedro Henrique Mendonça, Pedro Sodré, Pedro Marquesini
*/
#ifndef _djikstra
#define _djikstra

#include "PQ.h"

typedef struct graph Graph;

Graph* createGraph(int num_vertices);
void addEdge(Graph *graph, int source, int destiny, float weight);
void freeGraph(Graph *graph);
void printPath(int node, int *predecessor, FILE *out_file);
void dijkstra(Graph *graph, int source, FILE *out_file);

#endif