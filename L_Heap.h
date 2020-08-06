#ifndef L_HEAP_H_INCLUDED
#define L_HEAP_H_INCLUDED
#include "L_Utility.h"

typedef struct struttura_gestione_heap *StructHeap;

/* Callback (info in struttura_gestione_heap) */
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
    int heapsize;       // Mantiene l'informazione sul numero di elementi
    int max_min;        // Mantiene l'informazione sul tipo di heap: minimo o massimo
    int abr_arr;        // Mantiene l'informazione sul costrutto di heap: array o albero

    TipoStruttura tipo_struttura;   // Call: F_crea_albero - F_crea_array
    TipoElemento tipo_elem;         // Call: F_crea_intero/float/carattere/stringa
    Heapify_sxdx sinistra;          // Call: F_heapSx (ritorno figlio sx di un elemento)
    Heapify_sxdx destra;            // Call: F_heapDx (ritorno figlio dx di un elemento)
    Heapify_check FirstCheck;       // Call: F_FirstCheck_Albero_MaxMin - F_FirstCheck_Array_MaxMin
    Heapify_check SecondCheck;      // Call: F_SecondCheck_Alebro_MaxMin - F_SecondCheck_Array_MaxMin
    Heapify_scambio Scambio;        // Call: F_Scambio_Albero - F_Scambio_Array
    StampaHeap Stampa;              // Call: F_stampa_array - F_stampa_Albero
    StampaTipo StampaElemento;      // Call: F_stampa_intero/float/carattere/stringa
    Estrai_minmax EstraiMinMax;     // Call: F_estrai_minmax_array - F_estrai_minmax_albero
    Decrease_key DecreaseKey;       // Call: F_decrease_key_array - F_decrease_key_albero
    Increase_key IncreaseKey;       // Call: F_increase_key_array - F_increase_key_albero
    Inserisci_elemento InserisciElem;   // Call: F_inserisci_elemento_array - F_inserisci_elemento_albero
    Prendi_input PrendiInput;           // Call: F_prendi_intero/float/carattere/stringa
    Cancella_elemento CancellaElem;     // Call: F_cancella_elemento_array - F_cancella_elemento_albero
    Distruggi_tipo_elemento DistruggiTipoElem;  // Call: F_distruggi_elem_array_intero/float/carattere/stringa
    Dealloca DeallocaStruttura;         // Call: F_dealloca_array - F_dealloca_albero
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
