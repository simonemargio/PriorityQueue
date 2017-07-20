#include <stdio.h>
#include <stdlib.h>
#include "L_Heap.h"
//#include "L_Utility.h"

void F_heapify(StructHeap Heap, int i)
{
    printf("\nSto in heapify con indice:%d\n",i);
    int l = Heap->sinistra(i);

    int r = Heap->destra(i);
    printf("\nl:%d | r:%d\n",l,r);
    int mas = Heap->FirstCheck(Heap,l,i);
    printf("\nMas:%d\n",mas);
    mas = Heap->SecondCheck(Heap,r,mas);
    printf("\nMas finale:%d\n",mas);
    printf("\nConfronto %d con %d",mas,i);
    if(mas!=i)
    {
        printf("\nSono diversi\n");
        Heap->Scambio(Heap,i,mas);
        F_heapify(Heap,mas);
    }

    return;
}

int F_HeapSx(int i)
{
    i=(2*i)+1;

    return i;
}

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

StructHeap F_crea_heap(StructHeap Heap)
{
    Heap=Heap->tipo_struttura(Heap);

    return Heap;
}

void F_stampa_minmax(StructHeap Heap)
{
    if(Heap->struttura!=NULL)
    {
        if(Heap->abr_arr == 1) // Albero
        {
            Albero radice = Heap->struttura;
            F_stampa_priorita(radice->coda->priorita);
            Heap->StampaElemento(radice->coda->elem);
        }
        else // Array
        {
            Array S = Heap->struttura;
            F_stampa_priorita(S[0].coda->priorita);
            Heap->StampaElemento(S[0].coda->elem);
        }
    }
    else
        puts("Struttura non presente!\n");

    return;
}

StructHeap F_estrai_minmax(StructHeap Heap)
{
    if(Heap->struttura!=NULL)
    {
        Heap->struttura = Heap->EstraiMinMax(Heap);

    }
    else
        puts("Struttura non presente!\n");

    return Heap;
}