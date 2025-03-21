/*
    Autores: Pedro Henrique Mendonça, Pedro Sodré, Pedro Marquesini
*/

#ifndef NO_H
#define NO_H

#include "aresta.h"

typedef struct aresta tAresta;

typedef struct no tNo;

void finalizaNo(tNo *no);

int estaFinalizado(tNo *no);

tNo *inicializaNo(float id);

void liberaNo(tNo *no);

void setArestaList(tNo *no, tAresta *aresta);

tAresta *retornaArestaList(tNo *no);

void setPaiDoNo(tNo *no, tNo *novoPai);

tNo *getPaiDoNo(tNo *no);

void setDistanciaNo(tNo *no, float dist);

float getDistDoNo(tNo *no);

tNo *fazListaSemFinalizados(tNo *primeiro);

void printArestasLista(tNo **ArrayDeNos, int numero_de_vertices);

void insertionSortNos(tNo **ArrayDeNos, int numero_de_vertices);

void liberaArrayDeNos(tNo **ArrayDeNos, int numero_de_vertices);

void imprimeCaminhosMaisCurtos(tNo **ArrayDeNos,int numero_de_vertices, FILE *out);

#endif