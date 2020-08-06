#include <stdio.h>
#include <stdlib.h>
#include "L_Heap.h"
#include "L_Utility.h"

/* Funzione per il ripristino della proprieta' heap */
void F_heapify(StructHeap Heap, int i)
{
    /* Callback chiamate:
     * sinista/destra: richiama le funzioni F_HeapSx/F_HeapDx. Utilizzate per entrambe le strutture array/albero.
     * Si e' preferito introdurle come callback nel caso in cui si voglia aggiungere una nuova struttura senza alterare
     * la funzione F_heapify.
     * FirstCheck: richiama le funzioni: F_FirstCheck_Albero||array_MaxMin
     * SecondCheck: richiama le funzioni: F_SecondCheck_Albero||array_MaxMin
     * Scambio: richiama le sunzioni: F_Scambio_Albero||array
     * */
    int l = Heap->sinistra(i);
    int r = Heap->destra(i);
    int mas = Heap->FirstCheck(Heap,l,i);
    mas = Heap->SecondCheck(Heap,r,mas);

    if(mas!=i)
    {
        Heap->Scambio(Heap,i,mas);
        F_heapify(Heap,mas);
    }
}

/* Indice elemento sinistro */
int F_HeapSx(int i)
{
    i=(2*i)+1;

    return i;
}

/* Indice elemento destro */
int F_HeapDx(int i)
{
    i=(2*i)+2;

    return i;
}


/* Allocazione della struttura per la gestione di array/alberi heap */
StructHeap F_alloca_heap(StructHeap Heap)
{
    Heap = (struct struttura_gestione_heap *)malloc(sizeof(struct struttura_gestione_heap));

    return Heap;
}

/* Funzione per la creazione del tipo di struttura specificata dall'utente */
StructHeap F_crea_heap(StructHeap Heap)
{
    Heap=Heap->tipo_struttura(Heap); // Richiama: F_crea_albero||array

    return Heap;
}

/* Funzione per l'estrazione ed eliminazione del primo elemento */
StructHeap F_estrai_minmax(StructHeap Heap)
{
    if(Heap->struttura!=NULL)
    {
        Heap->struttura = Heap->EstraiMinMax(Heap); // Richiama: F_estrai_minmax_albero||array
    }
    else
        puts("Struttura non presente!\n");

    return Heap;
}

/* Funzione per il decremento della priorita' di un elemento scelto */
void F_decrease_key(StructHeap Heap)
{
    if(Heap->struttura!=NULL)
    {
        Heap->DecreaseKey(Heap); // Richiama: F_decrease_key_albero||array
    }
    else
        puts("Struttura non presente!\n");
}

/* Funzione per l'incremento della priorita' di un elemento scelto */
void F_increase_key(StructHeap Heap)
{
    if(Heap->struttura!=NULL)
    {
        Heap->IncreaseKey(Heap); // Richiama: F_increase_key_albero||array
    }
    else
        puts("Struttura non presente!\n");
}

/* Funzione per l'inserimento di un elemento dato dall'utente */
void F_inserisci_elemento(StructHeap Heap)
{
    if(Heap->struttura!=NULL)
    {
        Heap->InserisciElem(Heap); // Richiama: F_inserisci_elemento_albero||array
    }
    else
        puts("Struttura non presente!\n");
}

/* Funzione per la cancellazione di un elemento scelto dall'utente */
void F_cancella_elemento(StructHeap Heap)
{
    if(Heap->struttura!=NULL)
    {
        Heap->CancellaElem(Heap);   // Richiama: F_cancella_elemento_albero||array
    }
    else
        puts("Struttura non presente!\n");
}