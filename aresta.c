#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "no.h"
#include "aresta.h"

struct aresta{
    struct no *noOrigem, *noDestino;
    float peso;
    struct aresta *prox;
};

tAresta *inicializaAresta(float peso, tNo* destino, tNo *origem){
    tAresta *a = malloc(sizeof(tAresta));
    a->noDestino = destino;
    a->prox = NULL;
    a->peso = peso;
    a->noOrigem = origem;
    return a;
}

// retorna no origem
tNo *retornaNoOrigem(tAresta *aresta){
    return aresta->noOrigem;
}

// retorna no destino
tNo *retornaNoDestino(tAresta *aresta){
    return aresta->noDestino;
}

// retorna no destino
float retornaPesoDaAresta(tAresta *aresta){
    return aresta->peso;
}

tAresta *retornaProx(tAresta *aresta){
    return aresta->prox;
}

void colocaArestaNoInicio(tNo *raiz, tAresta *aresta) {
    if (raiz == NULL) {
        printf("Aresta está sendo colocada em um nó não inicializado\n");
        exit(1);
    }

    // Se não há nenhuma aresta na lista, a nova aresta é a primeira
    if (retornaArestaList(raiz) == NULL) {
        setArestaList(raiz, aresta);
    } else {
        // Coloca a nova aresta no início da lista
        aresta->prox = retornaArestaList(raiz);
        setArestaList(raiz, aresta);
    }
}