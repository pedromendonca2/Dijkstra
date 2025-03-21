/*
    Autores: Pedro Henrique Mendonça, Pedro Sodré, Pedro Marquesini
*/
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "aresta.h"
#include "no.h"
#include "string.h"
#include "djikstrainsertionsort.h"

void djikstraComInsertionSort(char **argv, int argc)
{
    
    if (argc < 3)
    {
        printf("Uso: %s <arquivo de entrada> <arquivo de saída>\n", argv[0]);
        exit(1);
    }

    char *arquivo_entrada = argv[1];
    char *arquivo_saida = argv[2];

    FILE *in_file = fopen(arquivo_entrada, "r");
    if (!in_file)
    {
        printf("Erro ao abrir o arquivo de entrada");
        exit(1);
    }

    FILE *out_file = fopen(arquivo_saida, "w");
    if (!out_file)
    {
        printf("Erro ao abrir o arquivo de saída");
        fclose(in_file);
        exit(1);
    }

    /*
        ETAPA DE LEITURA
        ---------------------------------------------------------
        leitura = se vir bomba, leitura vai detectar via sscanf,
        numero de vertices,
        origem: numero do vertice origem
        ---------------------------------------------------------
    */

    char leitura[65536];
    int numero_de_vertices = 0, origem, i = 0, j = 0;
    float aux2;

    // acha a origem;
    fscanf(in_file, "node_%d%*c", &origem);

    // conta o numero de linhas
    while (fscanf(in_file, "%[^\n]%*c", leitura) == 1)
    {
        numero_de_vertices++;
    }

    // aloca os nos
    tNo **ArrayDeNos = malloc(numero_de_vertices * sizeof(tNo *));
    for (int k = 0; k < numero_de_vertices; k++)
    {
        ArrayDeNos[k] = inicializaNo((float)k);
    }

    // volta o arquivo para cima
    rewind(in_file);

    // ignora a primeira linha
    fscanf(in_file, "%[^\n]%*c", leitura);

    // realiza a leitura de fato
    for (i = 0; i < numero_de_vertices; i++)
    {
        fscanf(in_file, "%*[^,]");
        for (j = 0; j < numero_de_vertices; j++)
        {
            if (i != j)
            {
                fscanf(in_file, ", %f", &aux2);
                fscanf(in_file, "%*[^,\n]");
                if (aux2 > 0)
                    colocaArestaNoInicio(ArrayDeNos[i], inicializaAresta(aux2, ArrayDeNos[j], ArrayDeNos[i]));
                else if (aux2 < 0)
                {
                    printf("Grafo não pode conter uma aresta negativa!");
                    exit(1);
                }
            }
        }
    }

    fclose(in_file);

    /*
      ----------------------------------
      ETAPA DO DJIKSTRA
      ----------------------------------
    */

    // coloca o no origem como distancia 0, o resto já foi inicializado com distancia maxima
    setDistanciaNo(ArrayDeNos[origem], 0);

    // cria a fila de no, coloca o no origem como primeiro da fila e seu tamanho como 1
    tNo **fila = malloc(1 * sizeof(tNo *));
    fila[0] = ArrayDeNos[origem];
    int tamanho_fila = 1;
    while (tamanho_fila > 0)
    {
        tNo *primeiro = fila[0];
        finalizaNo(primeiro);
        // recua um elemento da fila para a posicao anterior para ajustar a fila
        for (int i = 0; i < tamanho_fila - 1; i++) {
            fila[i] = fila[i + 1];
        }
        tamanho_fila--;
        tAresta *lista_de_arestas = retornaArestaList(primeiro);
        while (lista_de_arestas != NULL)
        {
            /*
                se o no da aresta nao estiver finalizado, checa se é possivel atualizar sua distancia
                em caso positivo: coloca o nó na fila de prioridades e atualiza sua distancia e seu pai.
            */ 
            if(!estaFinalizado(retornaNoDestino(lista_de_arestas))
                && retornaPesoDaAresta(lista_de_arestas) + getDistDoNo(retornaNoOrigem(lista_de_arestas)) 
                        < getDistDoNo(retornaNoDestino(lista_de_arestas))
            )
            {
                setDistanciaNo(retornaNoDestino(lista_de_arestas), retornaPesoDaAresta(lista_de_arestas) + getDistDoNo(retornaNoOrigem(lista_de_arestas)));
                setPaiDoNo(retornaNoDestino(lista_de_arestas), retornaNoOrigem(lista_de_arestas));
                tamanho_fila++;
                fila = realloc(fila, tamanho_fila * sizeof(tNo*));
                fila[tamanho_fila-1] = retornaNoDestino(lista_de_arestas);
            }
            lista_de_arestas = retornaProx(lista_de_arestas);
        }
        // usando insertion sort, ordenamos a fila por distancia do no, se der empate, ordena pelo id.
        insertionSortNos(fila, tamanho_fila);
    }

    free(fila);
    // ordena em ordem de menores distancias
    insertionSortNos(ArrayDeNos, numero_de_vertices);

    // imprime os caminhso mais curtos para cada vertice
    imprimeCaminhosMaisCurtos(ArrayDeNos, numero_de_vertices, out_file);
    
    // libera todos os vertices
    liberaArrayDeNos(ArrayDeNos, numero_de_vertices);
    fclose(out_file);
}