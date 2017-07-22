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
typedef void (*Decrease_key) (StructHeap Heap);
typedef void (*Increase_key) (StructHeap Heap);
typedef void (*Inserisci_elemento) (StructHeap Heap);
typedef void *(*Prendi_input) (void);

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
    Estrai_minmax EstraiMinMax;
    Decrease_key DecreaseKey;
    Increase_key IncreaseKey;
    Inserisci_elemento InserisciElem;
    Prendi_input PrendiInput;
};



StructHeap F_alloca_heap(StructHeap Heap);              // Allocazione della struttura per la gestione di array/alberi heap
StructHeap F_crea_heap(StructHeap Heap);
void F_heapify(StructHeap Heap, int i);
int F_HeapSx(int i);
int F_HeapDx(int i);
void F_stampa_minmax(StructHeap Heap);
StructHeap F_estrai_minmax(StructHeap Heap);
void F_decrease_key(StructHeap Heap);
void F_increase_key(StructHeap Heap);
void F_inserisci_elemento(StructHeap Heap);

#endif // L_HEAP_H_INCLUDED
