#ifndef L_UTILITY_H_INCLUDED
#define L_UTILITY_H_INCLUDED
#include "L_Heap.h"



struct struttura_nodo_albero
{
    struct struttura_elemento_coda *coda;
    struct struttura_nodo_albero *ptrSx;
    struct struttura_nodo_albero *ptrDx;
};

struct struttura_elemento_array
{
    struct struttura_elemento_coda *coda;
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


Albero F_inserisci_nodo_albero(Albero T,Coda nuovo_elem,int indice);

Albero F_alloca_nodo_albero(Coda nuovo_elem);
Albero F_preleva_nodo(StructHeap Heap,int indice);

/* Maschera */
int *F_ottieni_bit(int indice);
int F_salta_zero_bit(int *bits);

void *F_crea_intero();
int F_genera_priorita();
void F_costruisci_heap(StructHeap Heap);


int F_FirstCheck_Array_MaxMin(StructHeap Heap,int l,int i);
int F_SecondCheck_Array_MaxMin(StructHeap Heap,int r,int mas);

int F_FirstCheck_Albero_MaxMin(StructHeap Heap,int l,int i);
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

int F_seleziona_indice(StructHeap Heap,int elem_selezionato);

void F_decrease_key_array(StructHeap Heap);
void F_esegui_decrease_key_array_max(StructHeap Heap,int i,int val);
void F_esegui_decrease_key_array_min(StructHeap Heap,int i,int val);

void F_decrease_key_albero(StructHeap Heap);
void F_esegui_decrease_key_albero_max(StructHeap Heap,int i,int val);
void F_esegui_decrease_key_albero_min(StructHeap Heap,int i, int val);


void F_increase_key_array(StructHeap Heap);
void F_esegui_increase_key_array_max(StructHeap Heap,int i,int val);
void F_esegui_increase_key_array_min(StructHeap Heap,int i,int val);

void F_increase_key_albero(StructHeap Heap);
void F_esegui_increase_key_albero_max(StructHeap Heap,int i,int val);
void F_esegui_increase_key_albero_min(StructHeap Heap,int i, int val);

void F_inserisci_elemento_array(StructHeap Heap);
void *F_prendi_intero();
Coda F_genera_elememento_coda_utente(StructHeap Heap);

void F_inserisci_elemento_albero(StructHeap Heap);

void F_cancella_elemento_array(StructHeap Heap);
void F_cancella_elemento_albero(StructHeap Heap);

void F_distruggi_elem(StructHeap Heap,int indice);
void F_distruggi_elem_array_intero(StructHeap Heap,int indice);

#endif // L_UTILITY_H_INCLUDED
