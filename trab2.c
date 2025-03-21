/*
    Autores: Pedro Henrique Mendonça, Pedro Sodré, Pedro Marquesini
*/

#include <stdio.h>
#include "djikstrainsertionsort.h"
// #include <time.h>

int main(int argc, char *argv[]){
    
    // clock_t inicio, fim;
    // double tempo;

    // inicio = clock();


    djikstraComInsertionSort(argv, argc);

    // fim = clock();
    // tempo = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    // printf("Tempo de execução: %f\n", tempo);

    return 0;

}