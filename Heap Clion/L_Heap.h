#ifndef L_HEAP_H_INCLUDED
#define L_HEAP_H_INCLUDED
#include "L_Utility.h"

typedef struct struttura_gestione_heap *StructHeap;

/* Callback */
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
typedef void (*Dealloca) (StructHeap Heap);
typedef  void (*Cancella_elemento) (StructHeap Heap);
typedef  void (*Distruggi_tipo_elemento) (StructHeap Heap, int);

/* Struttura principale contenente info e procedure per la gestione di una struttura di tipo heap */
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
    Cancella_elemento CancellaElem;
    Distruggi_tipo_elemento DistruggiTipoElem;
    Dealloca DeallocaStruttura;
};



StructHeap F_alloca_heap(StructHeap Heap);          // Allocazione della struttura per la gestione di array/alberi heap
StructHeap F_crea_heap(StructHeap Heap);           // Funzione per la creazione del tipo di struttura specificata dall'utente
void F_heapify(StructHeap Heap, int i);           // Funzione per il ripristino della proprieta' heap
int F_HeapSx(int i);                             // Indice elemento sinistro
int F_HeapDx(int i);                            // Indice elemento destro
StructHeap F_estrai_minmax(StructHeap Heap);   // Funzione per l'estrazione ed eliminazione del primo elemento
void F_decrease_key(StructHeap Heap);         // Funzione per il decremento della priorita' di un elemento scelto
void F_increase_key(StructHeap Heap);        // Funzione per l'incremento della priorita' di un elemento scelto
void F_inserisci_elemento(StructHeap Heap); // Funzione per l'inserimento di un elemento dato dall'utente
void F_cancella_elemento(StructHeap Heap); // Funzione per la cancellazione di un elemento scelto dall'utente

#endif // L_HEAP_H_INCLUDED
