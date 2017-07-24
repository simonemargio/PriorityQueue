#ifndef L_UTILITY_H_INCLUDED
#define L_UTILITY_H_INCLUDED
#include "L_Heap.h"


/* Struttura albero */
struct struttura_nodo_albero
{
    struct struttura_elemento_coda *coda;
    struct struttura_nodo_albero *ptrSx;
    struct struttura_nodo_albero *ptrDx;
};

/* Struttura array */
struct struttura_elemento_array
{
    struct struttura_elemento_coda *coda;
};

/* Struttura con priorita' ed alemento scelto */
struct struttura_elemento_coda
{
    void *elem;
    int priorita;
};

typedef struct struttura_nodo_albero *Albero;
typedef struct struttura_elemento_array *Array;
typedef  struct struttura_elemento_coda *Coda;
typedef struct struttura_gestione_heap *StructHeap;

void F_start();         // Funzione iniziale
int F_menu_principale(int tipo);        // Stampa il menu' in cui l'utente puo' svolgere azioni sull'heap
int F_seleziona(int dim);               // Chiede all'untete un valore numerico (generalemente usato per selezionare la scelta in nei menu')
StructHeap F_info_heap(StructHeap Heap);    // Alloca la struttura in base alle scelte dell'utente
int F_tipo_heap();      // Menu' per la richiesta del tipo di elmento dello heap: intero, carattere, float, stringa
int F_max_min_heap();   // Menu' per la richiesta del tipo di heap: minimo o massimo
int F_abr_arr();        // Menu' per la richiesta del tipo di heap: array o albero
int F_num_elem();       // Chiede all'utente il numero di elementi da inserire nell'heap
void F_aggiungi_info(StructHeap Heap,int dim,int tipo_heap,int max_min,int abr_arr); // In base alle richieste dell'utente vengono associate alla struttura le relative funzioni
Coda F_genera_elemento_coda(StructHeap Heap);   // Alloca un elemento di tipo Coda

StructHeap F_crea_array(StructHeap Heap); // Funzione per la creazione dell'array di tipo heap
StructHeap F_crea_albero(StructHeap Heap); // Funzione per la creazione dell'albero di tipo heap

Albero F_inserisci_nodo_albero(Albero T,Coda nuovo_elem,int indice); // Inserisce un nuovo nodo nell'albero
Albero F_alloca_nodo_albero(Coda nuovo_elem);   // Crea un nuovo nodo
Albero F_preleva_nodo(StructHeap Heap,int indice); // Preleva un nodo in base all'indisce preso

/* Maschera */
int *F_ottieni_bit(int indice);
int F_salta_zero_bit(int *bits);


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

void *F_crea_intero();
void *F_prendi_intero();
void F_stampa_intero(void *elem);

void *F_crea_float();
void *F_prendi_float();
void F_stampa_float(void *elem);

void *F_crea_carattere();
void *F_prendi_carattere();
void F_stampa_carattere(void *elem);

void *F_crea_stringa();
void *F_prendi_stringa();
void F_stampa_stringa(void *elem);

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

Coda F_genera_elememento_coda_utente(StructHeap Heap);

void F_inserisci_elemento_albero(StructHeap Heap);

void F_cancella_elemento_array(StructHeap Heap);
void F_cancella_elemento_albero(StructHeap Heap);

//void F_distruggi_elem(StructHeap Heap,int indice);
void F_distruggi_elem_array_intero(StructHeap Heap,int indice);

void F_distruggi_elem_albero_intero(StructHeap Heap,int indice);

#endif // L_UTILITY_H_INCLUDED
