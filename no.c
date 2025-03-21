/*
    Autores: Pedro Henrique Mendonça, Pedro Sodré, Pedro Marquesini
*/

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "no.h"
#include "aresta.h"

struct no
{
    struct no *no_pai;
    float distance, id;
    int finalizado;
    struct aresta *aresta_list;
};

// finaliza nó
void finalizaNo(tNo *no)
{
    no->finalizado = 1;
}

// recebe se no esta finalizado
int estaFinalizado(tNo *no)
{
    return no->finalizado;
}

// inicializa nó
tNo *inicializaNo(float id)
{
    tNo *no = malloc(1 * sizeof(tNo));
    no->distance = FLT_MAX;
    no->id = id;
    no->no_pai = NULL;
    no->finalizado = 0;
    no->aresta_list = NULL;
    return no;
}

void liberaNo(tNo *no)
{
    if (no != NULL)
    {
        tAresta *aresta = no->aresta_list;
        while (aresta != NULL)
        {
            tAresta *aux = aresta;
            aresta = retornaProx(aresta);
            if (aux != NULL)
            {
                free(aux);
            }
        }
        free(no);
    }
}

tAresta *retornaArestaList(tNo *no)
{
    return no->aresta_list;
}

void setPaiDoNo(tNo *no, tNo *novoPai)
{
    no->no_pai = novoPai;
}

tNo *getPaiDoNo(tNo *no)
{
    return no->no_pai;
}

void setDistanciaNo(tNo *no, float dist)
{
    no->distance = dist;
}

float getDistDoNo(tNo *no)
{
    return no->distance;
}

void setArestaList(tNo *no, tAresta *aresta)
{
    no->aresta_list = aresta;
}

// tNo *fazListaSemFinalizados(tNo *primeiro)
// {
//     tNo *novaLista = NULL;
// }

void insertionSortNos(tNo **ArrayDeNos, int numero_de_vertices)
{
    int i, j;
    tNo *no;

    // Percorre os elementos do array de nós a partir do segundo elemento
    for (i = 1; i < numero_de_vertices; i++)
    {
        no = ArrayDeNos[i];
        j = i - 1;

        // Move os nós maiores que o nó atual uma posição à frente caso sua distancia for maior, ou, em caso de empate, se seu id for maior
        while (j >= 0 && (ArrayDeNos[j]->distance > no->distance || (ArrayDeNos[j]->distance == no->distance && ArrayDeNos[j]->id > no->id)))
        {
            ArrayDeNos[j + 1] = ArrayDeNos[j];
            j = j - 1;
        }
        ArrayDeNos[j + 1] = no;
    }
}

void liberaArrayDeNos(tNo **ArrayDeNos, int numero_de_vertices)
{
    if (ArrayDeNos != NULL)
    {
        for (int i = 0; i < numero_de_vertices; i++)
        {
            liberaNo(ArrayDeNos[i]);
        }
        free(ArrayDeNos);
    }
}

void imprimeCaminhosMaisCurtos(tNo **ArrayDeNos, int numero_de_vertices, FILE* out)
{
    for (int i = 0; i < numero_de_vertices; i++)
    {
        if(ArrayDeNos[i]->distance == FLT_MAX) fprintf(out, "Não há caminho para o vértice %.0f!\n", ArrayDeNos[i]->id);
        else{
            fprintf(out, "SHORTEST PATH TO node_%.0f: node_%.0f", ArrayDeNos[i]->id,  ArrayDeNos[i]->id);
            tNo *aux = ArrayDeNos[i];
            while(aux->no_pai != NULL)
            {
                fprintf(out, " <- node_%.0f", aux->no_pai->id);
                aux = aux->no_pai;
            }
            fprintf(out, " (Distance: %.2f)\n", ArrayDeNos[i]->distance);
        }
    }
}

// funcao para testes
void printArestasLista(tNo **ArrayDeNos, int numero_de_vertices)
{
    for (int i = 0; i < numero_de_vertices; i++)
    {
        tNo *no_atual = ArrayDeNos[i];
        printf("Nó %d:\n", (int)no_atual->id);

        tAresta *aresta_atual = retornaArestaList(no_atual);
        while (aresta_atual != NULL)
        {
            printf("\tAresta para o nó %d com peso %.2f\n", (int)retornaNoDestino(aresta_atual)->id, retornaPesoDaAresta(aresta_atual));
            aresta_atual = retornaProx(aresta_atual);
        }
    }
}