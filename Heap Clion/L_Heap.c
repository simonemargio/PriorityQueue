#include <stdio.h>
#include <stdlib.h>
#include "L_Heap.h"
#include "L_Utility.h"




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
