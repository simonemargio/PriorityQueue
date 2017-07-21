#ifndef L_HEAP_H_INCLUDED
#define L_HEAP_H_INCLUDED
#include "L_Utility.h"

typedef struct struttura_gestione_heap *StructHeap;


/* Call */
typedef StructHeap (*TipoStruttura) (StructHeap Heap);
typedef void *(*TipoElemento) (void);
typedef int(*Heapify_sxdx) (int);
typedef int(*Heapify_check) (StructHeap Heap,int,int);
typedef void(*Heapify_scambio) (StructHeap Heap,int,int);
typedef void(*StampaHeap) (StructHeap Heap);
typedef void(*StampaTipo) (void *);
typedef  void * (*Estrai_minmax) (StructHeap Heap);

struct struttura_gestione_heap
{
    void *struttura;
    int heapsize;
    int max_min;
    int abr_arr;

    TipoStruttura tipo_struttura;
    TipoElemento tipo_elem;
    Heapify_sxdx sinistra;
    Heapify_sxdx destra;
    Heapify_check FirstCheck;
    Heapify_check SecondCheck;
    Heapify_scambio Scambio;
    StampaHeap Stampa;
    StampaTipo StampaElemento;

    // build
    Estrai_minmax EstraiMinMax;

};



StructHeap F_alloca_heap(StructHeap Heap);              // Allocazione della struttura per la gestione di array/alberi heap
StructHeap F_crea_heap(StructHeap Heap);
void F_heapify(StructHeap Heap, int i);
int F_HeapSx(int i);
int F_HeapDx(int i);
void F_stampa_minmax(StructHeap Heap);
StructHeap F_estrai_minmax(StructHeap Heap);


#endif // L_HEAP_H_INCLUDED
