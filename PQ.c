#include "PQ.h" //

struct item {
    int node;
    float distance;
};

struct pq {
    Item** items;
    int size;
    int max;
};

void exch(Item** e1, Item** e2) {
    Item* aux = *e1;
    *e1 = *e2;
    *e2 = aux;
}

bool greater(Item* e1, Item* e2) {
    return e1->distance > e2->distance;
}

void fix_up(PQ *pq, int k) { 
    while (k > 1 && greater(pq->items[k / 2], pq->items[k])) {
        exch(&pq->items[k], &pq->items[k / 2]);
        k = k / 2;
    }
}

void fix_down(PQ *pq, int k) {
    while (2 * k <= pq->size) {
        int j = 2 * k;
        if (j < pq->size && greater(pq->items[j], pq->items[j + 1])) {
            j++;
        }
        if (!greater(pq->items[k], pq->items[j])) {
            break;
        }
        exch(&pq->items[k], &pq->items[j]);
        k = j;
    }
}

/*
 * Cria uma nova fila de prioridade mínima com o limite de elementos informado.
 */
PQ* PQ_create(int max_N) {
    PQ* heap = malloc(sizeof(PQ));
    if (heap == NULL) {
        return NULL;  // Falha na alocação de memória
    }

    heap->items = malloc((max_N + 1) *sizeof(Item*));
    if (heap->items == NULL) {
        free(heap);  // Libera a memória alocada para a estrutura
        return NULL;  // Falha na alocação de memória
    }
    heap->size = 0;
    heap->max = max_N;

    return heap;
}

/*
 * Libera a memória da fila.
 */
void PQ_destroy(PQ *pq) {
    for(int i = 1; i <= pq->size; i++){
        free(pq->items[i]);
    }
    free(pq->items);
    free(pq);
}

/*
 * Insere o evento na fila segundo o seu tempo.
 */
void PQ_insert(PQ *pq, Item *e) {
    if(pq->size >= pq->max){
        perror("Deu ruim na insert\n");
        printf("tam: %d\n", pq->size);
        printf("max: %d\n", pq->max);
        exit(1);
    }
    pq->items[++pq->size] = e;
    fix_up(pq, pq->size);
    printf("Inserted node %d with distance %.2f\n", e->node, e->distance);
}

/*
 * Remove e retorna o evento mais próximo.
 */
Item* PQ_delmin(PQ *pq) {
    if(PQ_is_empty(pq) || pq->size < 1) return NULL;
    Item* min = pq->items[1];
    exch(&pq->items[1], &pq->items[pq->size]);
    pq->size--;
    fix_down(pq, 1);
    printf("Removed node %d with distance %.2f\n", min->node, min->distance);
    return min;
}

/*
 * Testa se a fila está vazia.
 */
bool PQ_is_empty(PQ *pq) {
    if(pq->size == 0) return true;
    return false;
}

/*
 * Retorna o tamanho da fila.
 */
int PQ_size(PQ *pq) {
    return pq->size;
}