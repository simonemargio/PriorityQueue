#ifndef L_UTILITY_H_INCLUDED
#define L_UTILITY_H_INCLUDED
#include "L_Heap.h"



struct struttura_nodo_albero
{
   // void *elem;
   // int priorita;
    struct struttura_elemento_coda *coda;
    struct struttura_nodo_albero *ptrSx;
    struct struttura_nodo_albero *ptrDx;
};

struct struttura_elemento_array
{
    struct struttura_elemento_coda *coda;
    //int priorita;
    //void * elemArray;
};

struct struttura_elemento_coda
{
    void *elem;
    int priorita;
};

typedef struct struttura_nodo_albero *Albero;
typedef struct struttura_elemento_array *Array;
typedef  struct struttura_elemento_coda *Coda;
typedef struct struttura_gestione_heap *StructHeap;

void F_start();
int F_menu_principale(int tipo);
int F_seleziona(int dim);
StructHeap F_info_heap(StructHeap Heap);
int F_tipo_heap();
int F_max_min_heap();
int F_abr_arr();
int F_num_elem();
void F_aggiungi_info(StructHeap Heap,int dim,int tipo_heap,int max_min,int abr_arr);
Coda F_genera_elemento_coda(StructHeap Heap);

StructHeap F_crea_array(StructHeap Heap);
StructHeap F_crea_albero(StructHeap Heap);

//Albero F_inserisci_nodo_albero(Albero T,void *elemento, int priorita,int indice);
Albero F_inserisci_nodo_albero(Albero T,Coda nuovo_elem,int indice);
//Albero F_alloca_nodo_albero(void *elemento,int priorita);
Albero F_alloca_nodo_albero(Coda nuovo_elem);
Albero F_preleva_nodo(StructHeap Heap,int indice);

/* Maschera */
int *F_ottieni_bit(int indice);
int F_salta_zero_bit(int *bits);

void *F_crea_intero();
int F_genera_priorita();

void F_costruisci_heap(StructHeap Heap);


//int F_FirstCheck_Array_Max(StructHeap Heap,int l,int i);
int F_FirstCheck_Array_MaxMin(StructHeap Heap,int l,int i);
//int F_SecondCheck_Array_Max(StructHeap Heap,int r,int mas);
int F_SecondCheck_Array_MaxMin(StructHeap Heap,int r,int mas);

//int F_FirstCheck_Array_Min(StructHeap Heap,int l,int i);
//int F_SecondCheck_Array_Min(StructHeap Heap,int r,int mas);

//int F_FirstCheck_Albero_Max(StructHeap Heap,int l,int i);
int F_FirstCheck_Albero_MaxMin(StructHeap Heap,int l,int i);
//int F_SecondCheck_Alebro_Max(StructHeap Heap, int r,int mas);
int F_SecondCheck_Alebro_MaxMin(StructHeap Heap, int r,int mas);

void F_Scambio_Albero(StructHeap Heap,int i,int mas);

void F_Scambio_Array(StructHeap Heap,int i,int mas);

void F_stampa_heap(StructHeap Heap);
void F_stampa_array(StructHeap Heap);
void F_stampa_albero(StructHeap Heap);

void F_stampa_intero(void *elem);
void F_stampa_priorita(int elem);

typedef void(*StampaTipo) (void *);
void F_preorder(Albero T,StampaTipo Stampa);

void *F_estrai_minmax_array(StructHeap Heap);
void *F_estrai_minmax_albero(StructHeap Heap);
void F_stampa_elem_coda(StructHeap Heap, Coda minmax);
void F_elimina_foglia(StructHeap Heap);

#endif // L_UTILITY_H_INCLUDED
