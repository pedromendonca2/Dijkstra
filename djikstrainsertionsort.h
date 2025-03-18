#ifndef DJIKSTRAINSERTIONSORT_H
#define DJIKSTRAINSERTIONSORT_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "no.h"
#include "aresta.h"


/*
    ---------------------------------
    DIJKSTRA FEITO COM INSERTION SORT
    -----------------------------------------------------------------------------------------------------
    RETIRADA DO VERTICE DA FILA DE PRIORIDADE: causa o deslocamento de uma posição a esquerda de todos,
        o que é uma perda em comparação com o fix-up da heap.
    POR QUE INSERTION SORT: Simples como requisitado e pode tender a O(n) visto que há numa sequencia
        de ordenamentos em que muitos itens podem não ser atualizados, deixando o vetor parcialmente
        ordenado em cada iteração.
    ORGANIZAÇÃO DAS ARESTAS: Cada vértice tem uma lista sem sentinela simplesmente encadeada. Como a
        ordenacao das arestas nao importa, a inserçao na lista eh sempre de O(1), ocorrendo na cabeça.
        Olhar tad arestas.c
    ORGANIZAÇÃO DOS VÉRTICES: Alocados em um vetor. Olhar tad no.c
    -----------------------------------------------------------------------------------------------------
    */
void djikstraComInsertionSort(char **argv, int argc);

#endif