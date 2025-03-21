/*
    Autores: Pedro Henrique Mendonça, Pedro Sodré, Pedro Marquesini
*/
#ifndef ARESTA_H
#define ARESTA_H

#include "no.h"

typedef struct aresta tAresta;

typedef struct no tNo;

float retornaPesoDaAresta(tAresta *aresta);

tAresta *inicializaAresta(float peso, tNo* destino, tNo *origem);

tNo *retornaNoOrigem(tAresta *aresta);

tNo *retornaNoDestino(tAresta *aresta);

tAresta *retornaProx(tAresta *aresta);

void colocaArestaNoInicio(tNo *raiz, tAresta *aresta);


#endif