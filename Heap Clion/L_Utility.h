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

/* Funzioni */
void F_start();                                                      // Funzione iniziale
int F_menu_principale(int tipo);                                     // Stampa il menu' in cui l'utente puo' svolgere azioni sull'heap
int F_seleziona(int dim,char minimo,char massimo,int escludi);       // Chiede all'untete un valore numerico (generalemente usato per selezionare la scelta in nei menu')

StructHeap F_info_heap(StructHeap Heap);                             // Alloca la struttura in base alle scelte dell'utente
int F_tipo_heap();                                                   // Menu' per la richiesta del tipo di elmento dello heap: intero, carattere, float, stringa
int F_max_min_heap();                                                // Menu' per la richiesta del tipo di heap: minimo o massimo
int F_abr_arr();                                                     // Menu' per la richiesta del tipo di heap: array o albero
int F_num_elem();                                                    // Chiede all'utente il numero di elementi da inserire nell'heap
Coda F_genera_elemento_coda(StructHeap Heap);                        // Alloca un elemento di tipo Coda
void F_aggiungi_info(StructHeap Heap,int dim,int tipo_heap,int max_min,int abr_arr); // In base alle richieste dell'utente vengono associate alla struttura le relative funzioni

StructHeap F_crea_array(StructHeap Heap);                            // Funzione per la creazione dell'array di tipo heap
StructHeap F_crea_albero(StructHeap Heap);                           // Funzione per la creazione dell'albero di tipo heap

Albero F_inserisci_nodo_albero(Albero T,Coda nuovo_elem,int indice); // Inserisce un nuovo nodo nell'albero
Albero F_alloca_nodo_albero(Coda nuovo_elem);                        // Crea un nuovo nodo
Albero F_preleva_nodo(StructHeap Heap,int indice);                   // Preleva un nodo in base all'indisce preso

/* Maschera */
int *F_ottieni_bit(int indice); // Crea un vettore contenente il valore numerico in binario per la posizione del nodo dell'albero completo
int F_salta_zero_bit(int *bits); // Salta i bit pari a zero

int F_genera_priorita();                    // Funziona per la generazione random della priorita' di un elemento
void F_costruisci_heap(StructHeap Heap);   // Procede alla chiamata alla funzione heapify

int F_FirstCheck_Array_MaxMin(StructHeap Heap,int l,int i);      // Funzione heapify: primo controllo per array massimo/minimo
int F_SecondCheck_Array_MaxMin(StructHeap Heap,int r,int mas);   // Funzione heapify: secondo controllo per array

int F_FirstCheck_Albero_MaxMin(StructHeap Heap,int l,int i);     // Funzione heapify: primo controllo per albero massimo/minimo
int F_SecondCheck_Alebro_MaxMin(StructHeap Heap, int r,int mas); // Funzione heapify: secondo controllo per albero massimo/minimo

void F_Scambio_Albero(StructHeap Heap,int i,int mas);           // Scambio elementi per rispettare proprieta' heap albero
void F_Scambio_Array(StructHeap Heap,int i,int mas);            // Scambio elementi per rispettare proprieta' heap array

void F_stampa_heap(StructHeap Heap);     // Funzione di appoggio per la stampa dell'heap
void F_stampa_array(StructHeap Heap);   // Stampa dell'heap array
void F_stampa_albero(StructHeap Heap);  // Stampa dell'heap albero

/* Funzioni per la generazione di un tipo di dato, la sua presa in input e la stampa */
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
void F_preorder(Albero T,StampaTipo Stampa);            // Stampa dell'heap albero in maniera preorder
void *F_estrai_minmax_array(StructHeap Heap);           // Estrazione del primo elemento dell'array
void *F_estrai_minmax_albero(StructHeap Heap);          // Estrazione della radice dell'albero
void F_stampa_elem_coda(StructHeap Heap, Coda minmax);  // Funzione per la stampa
void F_elimina_foglia(StructHeap Heap);                 // Provvede all'eleiminazione dell'ultima foglia dell'albero

int F_seleziona_indice(StructHeap Heap,int elem_selezionato);   //Permette la coretta selezione dell'indice scelto dall'utente

void F_decrease_key_array(StructHeap Heap);                             // Funzione per decrementare la priorita' di un elemento con struttura array
void F_esegui_decrease_key_array_max(StructHeap Heap,int i,int val);    // Funzione decrease per Max array
void F_esegui_decrease_key_array_min(StructHeap Heap,int i,int val);    // Funzione decrease per Min array

void F_decrease_key_albero(StructHeap Heap);                            // Funzione per decrementare la priorita' di un elemento con struttura albero
void F_esegui_decrease_key_albero_max(StructHeap Heap,int i,int val);   // Funzione decrease per Max albero
void F_esegui_decrease_key_albero_min(StructHeap Heap,int i, int val);  // Funzione decrease per Min albero

void F_increase_key_array(StructHeap Heap);                             // Funzione per incrementare la priorita' di un elemento con struttura array
void F_esegui_increase_key_array_max(StructHeap Heap,int i,int val);    // Funzione increase per Max array
void F_esegui_increase_key_array_min(StructHeap Heap,int i,int val);    // Funzione increase per Min array

void F_increase_key_albero(StructHeap Heap);                            // Funzione per incrementare la priorita' di un elemento con struttura albero
void F_esegui_increase_key_albero_max(StructHeap Heap,int i,int val);   // Funzione increase per Max albero
void F_esegui_increase_key_albero_min(StructHeap Heap,int i, int val);  // Funzione increase per Min albero

void F_inserisci_elemento_array(StructHeap Heap);                            // Funzione per l'inserimento di un nuovo elemento in una struttura heap array
Coda F_genera_elememento_coda_utente(StructHeap Heap);                       // Costruisce mediate l'interazione dell'utente un elemento della coda
void F_inserisci_elemento_albero(StructHeap Heap);                           // Funzione per l'inserimento di un nuovo elemento in una struttura heap albero
void F_cancella_elemento_array(StructHeap Heap);                             // Funzione per la cancellazione di un elemento nella struttura heap array
void F_cancella_elemento_albero(StructHeap Heap);                            // Funzione per la cancellazione di un elemento nella struttura heap albero
void F_distruggi_elem_array_intero(StructHeap Heap,int indice);              // Eliminazione elemento array intero
void F_distruggi_elem_albero_intero(StructHeap Heap,int indice);             // Eliminazione elemento albero intero
void F_distruggi_elem_array_float(StructHeap Heap,int indice);               // Eliminazione elemento array float
void F_distruggi_elem_albero_float(StructHeap Heap,int indice);              // Eliminazione elemento albero float
void F_distruggi_elem_array_carattere_stringa(StructHeap Heap,int indice);   // Eliminazione elemento array carattere
void F_distruggi_elem_albero_carattere_stringa(StructHeap Heap,int indice);  // Eliminazione elemento albero carattere


void F_dealloca_array(StructHeap Heap);         // Esegue la deallocazione della struttura array
void F_dealloca_albero(StructHeap Heap);        // Prepara la deallocazione della struttura albero
void F__dealloca_albero(Albero T);
void F_stampa_minmax(StructHeap Heap);

#endif // L_UTILITY_H_INCLUDED
