#include <stdio.h>
#include <stdlib.h>
#include "djikstrainsertionsort.h"
#include <time.h>

int main(int argc, char *argv[]){
    
    clock_t inicio, fim;
    double tempo_execucao;

    inicio = clock();

    djikstraComInsertionSort(argv, argc);

    fim = clock();

    tempo_execucao = ((double)(fim-inicio)/ CLOCKS_PER_SEC);
    printf("Tempo de execução: %f segundos\n",tempo_execucao);

    return 0;

}