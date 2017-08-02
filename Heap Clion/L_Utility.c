#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "L_Heap.h"
#include <limits.h>
#define DIMARRMASK 32
#define DIM_STRINGA 11
//#include "L_Utility.h"

void F_start()
{
    /* Inizializzo la funzione per la generazione dei numeri casuali */
    srand((unsigned)time(NULL));
    int menu_principale=-1,scelta=0;

    StructHeap Heap = NULL;     // Struttura per gestione di array/albero heap
    Heap = F_alloca_heap(Heap); // Procede all'allocazione della struttura "struttura_gestione_heap"
    Heap = F_info_heap(Heap);   // Ricava dall'utente tutte le informazioni sulla costruzione dell'heap
    Heap = F_crea_heap(Heap);   // Crea la struttura (array o albero) scelto dall'utente
    F_costruisci_heap(Heap);    // Applica le proprietà heap

    do
    {
        scelta = F_menu_principale(Heap->max_min); // Menu' principale
        switch(scelta)
        {
            case 1: // Stampa
                F_stampa_heap(Heap);
                break;

            case 2: // Inserisci elemento
                F_inserisci_elemento(Heap);
                break;

            case 3: // Stampa il primo elemento (min o max in base all'heap)
                F_stampa_minmax(Heap);
                break;

            case 4:
                if(Heap->heapsize > 1)
                    F_estrai_minmax(Heap);
                else
                    if(Heap->heapsize == 1) puts("Presente solo un elmento!\n");
                    else puts("Struttura non presente!\n");
            break;

            case 5: // Aumenta priorita'
                F_increase_key(Heap);
                break;

            case 6: // Decrementa priorita'
                F_decrease_key(Heap);
                break;

            case 7: // Elimina elemento
                F_cancella_elemento(Heap);
                break;

            case 0: // Uscita
                menu_principale = 0;
            break;

            default:
                puts("\nScelta non valida! Riprovare");
                break;
        }

    }while(menu_principale!=0);

    // Deallocazione della struttura
    Heap->DeallocaStruttura(Heap);
    Heap->struttura = NULL;
    free(Heap->struttura);

    return;
}

/* Menu' principale per la gestione heap */
int F_menu_principale(int tipo)
{
    int scelta = 0;
    puts("\n");
    puts("1] Stampa heap");
    puts("2] Inserisci un elemento");
    printf("3] Stampa il ");
    if(tipo == 1)
            puts("minimo");
        else
            puts("massimo");
    printf("4] Estrai il ");
    if(tipo == 1)
            puts("minimo");
        else
            puts("massimo");
    puts("5] Incrementa priorita");
    puts("6] Decrementa priorita");
    puts("7] Elimina un elemento");
    puts("");
    puts("0] Esci");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1,'0','9',-1);

    return scelta;
}

/* Richiesta all'utente della struttura da realizzare */
StructHeap F_info_heap(StructHeap Heap)
{
    int dim=0,tipo_heap=0,max_min=0,abr_arr=0;

    abr_arr = F_abr_arr();      // Scelta se albero o array
    max_min = F_max_min_heap(); // Scleta se minimo o massimo
    tipo_heap = F_tipo_heap();  // Tipo di dato da contenere (int,char,string...)
    dim = F_num_elem();         // Numero di elementi che di vuole costruire

    F_aggiungi_info(Heap,dim,tipo_heap,max_min,abr_arr); // Gestisce tutte le routine/callback

    return Heap;
}

/* Chiede all'utente il numero di elementi con cui formare l'heap */
int F_num_elem()
{
    int scelta=0;

    printf("\nNumero di elementi da inserire:");
    scelta=F_seleziona(2,'0','9',0);

    return scelta;
}

/* Chiede all'utente il tipo di dato che deve contenere la struttura */
int F_tipo_heap()
{
    int scelta=0;

    puts("\nDato presente nell'heap");
    puts("1] Interi");
    puts("2] Float");
    puts("3] Caratteri");
    puts("4] Stringhe");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1,'1','4',0);

    return scelta;
}

/* Chiede all'utente il tipo di heap da creare */
int F_max_min_heap()
{
    int scelta=0;


    puts("\nTipologia di heap");
    puts("1] Minimo");
    puts("2] Massimo");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1,'1','2',0);

    return scelta;
}

/* Chiede all'utente la struttura dell'heap */
int F_abr_arr()
{
    int scelta=0;

    puts("Struttura da usare");
    puts("1] Albero");
    puts("2] Array");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1,'1','2',0);

    return scelta;
}

/* Funzione per la selezione di un valore intero */
int F_seleziona(int dim,char minimo,char massimo,int escludi)
{
    /* Variabili in ingresso:
     *
     * dim: dimensione del vettore che conterrà i valori numerici presi in inmput
     * minimo: valore piu' piccolo che puo' essere preso
     * massimo: valore massimo che puo' essere preso
     * escludi: il valore preso in input non deve essere minore uguale del valore escludi
     * */

    char tmp[dim],c='*';
    int intero_preso=0,i=0,flag=0;
    fflush(stdin);

    do
    {
        while( i<dim && (c= (char) getchar()) != '\n' && c != EOF )
        {
            printf("\n%c<-\n\n",c);
            if(c>=minimo && c<=massimo)
            {
                tmp[i]=c;
                i++;
            }

        }
        sscanf(tmp,"%d",&intero_preso);

        if(intero_preso<=escludi)
        {
            printf("Valore non corretto\nInserisci di nuovo:");

            /* Inizializzo vettore */
            for(i=0;i<10;i++)
                tmp[i]='*';

            i=0;
        }
        else // Valore corretto
            flag=1;

    }while(flag==0);

    int *elemento=malloc(sizeof(int));
    memcpy(elemento,&intero_preso,sizeof(int));
    return intero_preso;
}

/* Funzione per la creazione dell'array */
StructHeap F_crea_array(StructHeap Heap)
{
    int i=0;
    Array S=(struct struttura_elemento_array *)calloc((size_t) Heap->heapsize, sizeof(struct struttura_elemento_array));

    for(i=0;i<Heap->heapsize;i++)
    {
        /* Provvede a allocare un nuovo elemento "struttura_elemento_coda" contenente priorita' e l'elemento scelto */
        S[i].coda=F_genera_elemento_coda(Heap);
    }

    Heap->struttura = S;

    return Heap;
}

/* Alloca un nuovo elemento di tipo Coda contenento priorita' e il tipo di elemento scelto dall'utente */
Coda F_genera_elemento_coda(StructHeap Heap)
{
    Coda nuovo_elem=(struct struttura_elemento_coda *)malloc(sizeof(struct struttura_elemento_coda));

    nuovo_elem->priorita=F_genera_priorita();
    nuovo_elem->elem=Heap->tipo_elem();

    return nuovo_elem;
}

/* Alloca N° nodo per la creazione dell'albero */
StructHeap F_crea_albero(StructHeap Heap)
{
    int i=0;
    Albero T=NULL;

    for(i=0;i<Heap->heapsize;i++)
    {
        Coda nuovo_elem=F_genera_elemento_coda(Heap);

        T=F_inserisci_nodo_albero(T,nuovo_elem,i);
    }

    Heap->struttura = T;

    return Heap;
}

/* Funzione per la creazione di un albero completo */
Albero F_inserisci_nodo_albero(Albero T,Coda nuovo_elem,int indice)
{
    if(indice == 0)
    {
        T=F_alloca_nodo_albero(nuovo_elem);
    }
    else
    {
        Albero Tmp = T;
        int *bits = F_ottieni_bit(indice+1); // Ottiene il numero di posizione del nodo in biniario

        int j=F_salta_zero_bit(bits);   // Salta tutti i vit pari a zero e il primo bit pari a uno (radice)

        for(;j>=0;j--) // I restanti bit permettono di trovare la posizone del nodo
        {
            if(bits[j]==1) // Mi sposto a destra
            {
                if(Tmp->ptrDx == NULL)
                    Tmp->ptrDx=F_inserisci_nodo_albero(Tmp,nuovo_elem,0);
                else
                    Tmp=Tmp->ptrDx;
            }
            else // Mi sposto a sinistra
            {
                if(Tmp->ptrSx == NULL)
                    Tmp->ptrSx=F_inserisci_nodo_albero(Tmp,nuovo_elem,0);
                else
                    Tmp=Tmp->ptrSx;
            }
        }
        free(bits);
    }
    return T;
}

/* Salta i bit pari a zero */
int F_salta_zero_bit(int *bits)
{
    int j;
    for(j=DIMARRMASK-1;j>=0;j--)
    {
        if(bits[j]==1)
        {
            j--; // Salta anche il primo bit pari a uno
            break;
        }
    }
    return j;
}

/* Crea un vettore contenente il valore numerico in binario per la posizione del nodo dell'albero completo */
int *F_ottieni_bit(int n)
{
    int *bits = malloc(sizeof(int)* DIMARRMASK);

    int k;
    for(k=0;k<DIMARRMASK;k++)
    {
        int mask = 1 << k;
        int mask_n = n & mask;
        int bit_preso = mask_n >> k;
        bits[k] = bit_preso;
    }
    return bits;
}

/* Allocazione di un nodo dell'albero con inserimento di un elemento di tipo Coda */
Albero F_alloca_nodo_albero(Coda nuovo_elem)
{
    Albero nuovo_nodo=(struct struttura_nodo_albero *)malloc(sizeof(struct struttura_nodo_albero));
    nuovo_nodo->coda=nuovo_elem;
    nuovo_nodo->ptrDx=NULL;
    nuovo_nodo->ptrSx=NULL;

    return nuovo_nodo;
}

/* In base alle scelte dell'utente vengono inserite le opportune funzioni per la creazione e gestione dell'heap */
void F_aggiungi_info(StructHeap Heap,int dim,int tipo_heap,int max_min,int abr_arr)
{
    Heap->heapsize=dim;         // Numero di elementi
    Heap->sinistra = F_HeapSx;  // Figlio sinistro di un elemento
    Heap->destra = F_HeapDx;    // FIglio destro di un elemento
    Heap->max_min = max_min;    // Valore 1: Min heap - 2: Max heap
    Heap->abr_arr = abr_arr;    // Valore 1: Albero - 2: Array

    switch(abr_arr)
    {
        case 1: // Albero
            Heap->tipo_struttura = F_crea_albero;
            Heap->Scambio=F_Scambio_Albero;
            Heap->Stampa = F_stampa_albero;
            Heap->EstraiMinMax = F_estrai_minmax_albero;
            Heap->FirstCheck = F_FirstCheck_Albero_MaxMin;
            Heap->SecondCheck = F_SecondCheck_Alebro_MaxMin;
            Heap->DecreaseKey = F_decrease_key_albero;
            Heap->IncreaseKey = F_increase_key_albero;
            Heap->InserisciElem = F_inserisci_elemento_albero;
            Heap->CancellaElem = F_cancella_elemento_albero;
            Heap->DeallocaStruttura = F_dealloca_albero;
        break;

        case 2: // Array
           Heap->tipo_struttura = F_crea_array;
           Heap->Scambio = F_Scambio_Array;
           Heap->Stampa = F_stampa_array;
           Heap->EstraiMinMax = F_estrai_minmax_array;
           Heap->FirstCheck = F_FirstCheck_Array_MaxMin;
           Heap->SecondCheck = F_SecondCheck_Array_MaxMin;
           Heap->DecreaseKey = F_decrease_key_array;
           Heap->IncreaseKey = F_increase_key_array;
           Heap->InserisciElem = F_inserisci_elemento_array;
           Heap->CancellaElem = F_cancella_elemento_array;
           Heap->DeallocaStruttura = F_dealloca_array;
        break;
        default:
            puts("Error: selezione delle tipologia di struttura heap non definita!\n");
            exit(-1);
           // break;
    }

    switch(tipo_heap)
    {
        case 1: // Interi
            puts("Ineri");
            Heap->tipo_elem = F_crea_intero;
            Heap->StampaElemento = F_stampa_intero;
            Heap->PrendiInput = F_prendi_intero;
            if(abr_arr==2) Heap->DistruggiTipoElem = F_distruggi_elem_array_intero;
            else Heap->DistruggiTipoElem = F_distruggi_elem_albero_intero;
        break;

        case 2: // Float
           Heap->tipo_elem = F_crea_float;
           Heap->StampaElemento = F_stampa_float;
           Heap->PrendiInput = F_prendi_float;
        break;

        case 3: // caratteri
            Heap->tipo_elem = F_crea_carattere;
            Heap->StampaElemento = F_stampa_carattere;
            Heap->PrendiInput = F_prendi_carattere;
        break;

        case 4: // Stringhe
            Heap->tipo_elem = F_crea_stringa;
            Heap->StampaElemento = F_stampa_stringa;
            Heap->PrendiInput = F_prendi_stringa;
        break;

        default:
            puts("Error: selezione del tipo di elemento dell'heap non definito!\n");
            exit(-2);
           // break;
    }

}

/* Generazione casuale di un valore intero */
void *F_crea_intero()
{
    void *elemento=malloc(sizeof(int));
    int i=rand();
    memcpy(elemento,&i,sizeof(int));

    return elemento;
}

/* Funzione per la stampa di un intero */
void F_stampa_intero(void *elem)
{
    printf(" %d|",*((int *)elem));

    return;
}

/* Generazione casuale di un valore float */
void *F_crea_float()
{
    float f=(float)rand()/(float)RAND_MAX;
    f=(rand()%100)+f;
    void *elemento=malloc(sizeof(float));
    memcpy(elemento,&f,sizeof(float));

    return elemento;
}

/* Richiesta all'untente di un tipo float */
void *F_prendi_float()
{
    char tmp[DIM_STRINGA+3],c='*';
    int i=0;
    float ftemp;

    printf("\nTipologia di elemento di heap: FLOAT. Inserire la parte intera:");

    while( i<DIM_STRINGA+2 && (c= (char) getchar()) != '\n' && c != EOF )
    {
        if(c>='0' && c<='9')
        {
            tmp[i]=c;
            i++;
        }

    }

    tmp[i]='.';
    i++;

    if(i<DIM_STRINGA+2)
    {
        printf("Ora inserire la Parte decimale:");

        while( i<DIM_STRINGA+2 && (c= (char) getchar()) != '\n' && c != EOF )
        {
            if(c>='0' && c<='9')
            {
                tmp[i]=c;
                i++;
            }

        }
        tmp[i]='\0';
    }

    sscanf(tmp,"%f",&ftemp);

    void *elemento=malloc(sizeof(float));
    memcpy(elemento,&ftemp,sizeof(float));

    return elemento;
}

/* Funzione per la stampa di un elemento float */
void F_stampa_float(void *elem)
{
    printf(" %f|",*((float *)elem));
    return;
}

// CARATTERE
void *F_crea_carattere()
{
    /* DICHIARAZIONE VARIABILI */
    int min=0,max=0;
    char c;

    void *elemento=malloc(sizeof(char));
    int scelta_carattere=rand()%2;

    switch(scelta_carattere)
    {
        case 0:
            min=65,max=90;
            break;

        case 1:
            min=97,max=122;
            break;
        default:
            puts("Errore creazione carattere!");
            break;

    }
    c= (char) (rand() % (max - min) + min);
    memcpy(elemento,&c,sizeof(char));

    return elemento;
}

void *F_prendi_carattere()
{
    /* DICHIARAZIONE VARIABILI*/
    char c='*';
    void *elemento=NULL;
    int flag=1;
    printf("\nTipologia di elemento di heap: CARATTERE. Inserire un solo carattere.\nEventuali altri caratteri verranno ignorati (Max: 1):");

    while(flag==1)
    {
        c= (char) getchar();
        if((c>='a' && c<='z') || (c>='A' && c<='Z'))
        {
            flag=0;
        }
        else
        {
            while('\n'!=getchar());
            printf("Non e' stato inserito un carattere, riprovare:");
        }
    }

    while('\n'!=getchar());
    elemento=malloc(sizeof(char));
    memcpy(elemento,&c,sizeof(char));

    return elemento;
    return NULL;
}

/* Funzione per la stampa di un carattere */
void F_stampa_carattere(void *elem)
{
    printf(" %c|",*((char *)elem));
    return;
}

// STRINGA
void *F_crea_stringa()
{
    /* DICHIARAZIONE VARIABILI*/
    int dim_stringa=0,scelta_carattere=0,i=0,max=0,min=0;
    char *stringa=NULL;

    /* Randomizzo la lunghezza della stringa */
    dim_stringa=4+(rand()%DIM_STRINGA);

    /* Alloco lo spazio necessario */
    stringa=malloc(sizeof(char)*dim_stringa);

    while(i<dim_stringa-1) // Ciclo eseguito dim_stringa -1 per inserire nell'ultimo elemento \0
    {
        scelta_carattere=rand()%3;

        switch(scelta_carattere)
        {
            /* Lettere A-Z maiuscole */
            case 0:
                min=65,max=90;
                break;

                /* Lettere A-Z minuscole */
            case 1:
                min=97,max=122;
                break;

                /* Numeri 0-9 */
            case 2:
                min=48,max=57;
                break;
            default:
                puts("Errore creazione stringa!");
                break;
        }

        stringa[i]= (char) (rand() % (max - min ) + min);
        i++;
    }
    stringa[i]='\0';

    return stringa;
}
void *F_prendi_stringa()
{
    /* DICHIARAZIONE VARIABILI */
    char *tmp=NULL,c='*';
    void *stringa_uscita=NULL;
    int i=0;

    tmp=(char *)malloc((DIM_STRINGA+3)*sizeof(char)); // Default: Max stringa 14 (4+DIM_STRINGA).

    printf("\nInserisci la stringa (MAX:%d):",DIM_STRINGA+2);

    for(i=0; (i<DIM_STRINGA+2 && (c= (char) getchar()) != '\n' && c != EOF); i++)
    {
        tmp[i]=c;
    }
    tmp[i]='\0';

    stringa_uscita=malloc(i*sizeof(char)); // Allocazione del giusto spazio per stringhe minori di DIM_STRINGA
    strcpy(stringa_uscita,tmp); // Copia della stringa nello spazio abitio al suo contenimento
    free(tmp);

    return stringa_uscita;
}

/* Funzione per la stampa di una stringa */
void F_stampa_stringa(void *elem)
{
    printf(" %s|",((char *)elem));
    return;
}

/* Funzione per la generazione di priorita' */
int F_genera_priorita()
{
    int i=rand() % (100 + 1 - 1) + 1;
    printf("Priorita: %d\n",i);

    return i;
}

/* Funzione per la costruzione dell'heap */
void F_costruisci_heap(StructHeap Heap)
{
    int n = (Heap->heapsize / 2 );
    while(n>=0)
    {
        F_heapify(Heap,n);
        n--;
    }

    return;
}

/* Heapify: primo controllo per array */
int F_FirstCheck_Array_MaxMin(StructHeap Heap,int l,int i)
{
    int mas=i;
    Array S = Heap->struttura;

    if(l<Heap->heapsize)
    {
        if(Heap->max_min == 1) // Minimo
        {
            if(S[l].coda->priorita<S[i].coda->priorita)
            {
                mas=l;
            }
            else
            {
                mas=i;
            }

        } else // Massimo
        {
            if(S[l].coda->priorita>S[i].coda->priorita)
            {
                mas=l;
            }
            else
            {
                mas=i;
            }
        }
    }

    return mas;
}

/* Heapify: secondo controllo per array */
int F_SecondCheck_Array_MaxMin(StructHeap Heap,int r,int mas)
{
    Array S = Heap->struttura;

    if(r<Heap->heapsize)
    {
        if(Heap->max_min == 1) // Minimo
        {
            if(S[r].coda->priorita<S[mas].coda->priorita)
            {
                mas=r;
            }
        } else // Massimo
        {
            if(S[r].coda->priorita>S[mas].coda->priorita)
            {
                mas=r;
            }
        }

    }

    return mas;
}

/* Heapify: primo controllo per l'albero */
int F_FirstCheck_Albero_MaxMin(StructHeap Heap,int l,int i)
{
    int mas=i;

    /* Prende i nodi per effettuare i confronti delle priorita' */
    Albero nodo_l=F_preleva_nodo(Heap,l);
    Albero nodo_i=F_preleva_nodo(Heap,i);

    if(l < Heap->heapsize)
        {
            int priorita_l = nodo_l->coda->priorita;
            int priorita_i = nodo_i->coda->priorita;
            //printf("\n1 Ho preso le loro due priorira l:%d | i%d\n",priorita_l,priorita_i);

            if(Heap->max_min == 1) // Minimo
            {
                if (priorita_l < priorita_i)
                {
              //      printf("\n1 |%d e' piu grande di %d\n",priorita_l,priorita_i);
                    mas = l;
                }
                else
                {
               //     printf("\n1 |%d e' piu piccola di %d\n",priorita_l,priorita_i);
                    mas = i;
                }

            } else // Massimo
            {
                if (priorita_l > priorita_i)
                {
                //    printf("\n1 |%d e' piu grande di %d\n",priorita_l,priorita_i);
                    mas = l;
                }
                else
                {
             //       printf("\n1 |%d e' piu piccola di %d\n",priorita_l,priorita_i);
                    mas = i;
                }
            }

        }
   // printf("\n1 Ritorno con priorira mas per ora %d\n",mas);
    return mas;
}

/* Heapify: secondo controllo per l'albero */
int F_SecondCheck_Alebro_MaxMin(StructHeap Heap, int r,int mas)
{
    /* Prende i nodi per effettuare i confronti delle priorita' */
    Albero nodo_r=F_preleva_nodo(Heap,r);
    Albero nodo_mas=F_preleva_nodo(Heap,mas);
   // printf("\n2 Preso il nodo di indice r:%d | mas:%d\n",r,mas);
        if(r<Heap->heapsize)
        {
            int priorita_r = nodo_r->coda->priorita;
            int priorita_mas = nodo_mas->coda->priorita;
     //       printf("\n2 Ho preso le loro due priorira r:%d | mas%d\n",priorita_r,priorita_mas);

            if(Heap->max_min == 1) // Minimo
            {
                if(priorita_r<priorita_mas)
                {
                    //printf("\n2 La priorita %d e' piu grande di %d",priorita_r,priorita_mas);
                    mas=r;
                }
            } else // Massimo
            {
                if(priorita_r>priorita_mas)
                {
                    //printf("\n2 La priorita %d e' piu grande di %d",priorita_r,priorita_mas);
                    mas=r;
                }
            }

        }
   // printf("\n2 Ritorno con priorira mas definitiva %d\n",mas);

    return mas;
}

/* Funzione per prelevare un nodo dell'albero in base all'indice passato */
Albero F_preleva_nodo(StructHeap Heap,int indice)
{
    Albero nodo = Heap->struttura;

    int *bits = F_ottieni_bit(indice+1); // Ottengo la posizione in binario del nodo

    int j=F_salta_zero_bit(bits); // Salto gli zero e il primo uno in bit

    for(;j>=0;j--)  // Prelevo il nodo spostandomi con i bit restanti
    {
        if(bits[j]==1)
        {
            nodo=nodo->ptrDx;
        }
        else
        {
            nodo=nodo->ptrSx;
        }
    }
    free(bits);

    return nodo;
}

/* Funzione per lo scambio delle informazioni tra due celle dell'array */
void F_Scambio_Array(StructHeap Heap,int i,int mas)
{
   // puts("\nFatto scambio");
    Array S = Heap->struttura;

    int tpriorita = S[i].coda->priorita;
    void *telem = S[i].coda->elem;
    S[i].coda->priorita = S[mas].coda->priorita;
    S[i].coda->elem = S[mas].coda->elem;
    S[mas].coda->priorita = tpriorita;
    S[mas].coda->elem = telem;

    return;
}

/* Funzione per lo scambio delle informazioni tra due nodo dell'albero */
void F_Scambio_Albero(StructHeap Heap,int i,int mas)
{
    Albero nodo_i=F_preleva_nodo(Heap,i);
    Albero nodo_mas=F_preleva_nodo(Heap,mas);

    int priorita_i = nodo_i->coda->priorita;
    void *telem = nodo_i->coda->elem;

  //  printf("\nInizio lo scambio della priorira i:%d con la prioria mas:%d\n",i,mas);
   // printf("\nIn i ho %d. In mas ho %d",nodo_i->coda->priorita,nodo_mas->coda->priorita);

    nodo_i->coda->priorita = nodo_mas->coda->priorita;
    nodo_i->coda->elem = nodo_mas->coda->elem;

    nodo_mas->coda->elem = telem;
    nodo_mas->coda->priorita = priorita_i;

  //  printf("\nHo terminato lo scambio ora ho in i ho %d. In mas ho %d",nodo_i->coda->priorita,nodo_mas->coda->priorita);

    return;
}

/* Funzione per la stampa dell'heap */
void F_stampa_heap(StructHeap Heap)
{
    Heap->Stampa(Heap); // Richiama: F_stampa_array || F_stampa_albero

    return;
}

/* Provvede alla stampa dell'array */
void F_stampa_array(StructHeap Heap)
{
    int i=0;
    Array S = Heap->struttura;

    puts("Ecco l'array:");
    for(i=0;i<Heap->heapsize;i++)
    {
        F_stampa_priorita(S[i].coda->priorita);
        Heap->StampaElemento(S[i].coda->elem); // Richiiama: F_stampa_intero||float||carattere||stringa
    }

    return;
}

/* Provvede alla stampa dell'albero */
void F_stampa_albero(StructHeap Heap)
{
    Albero T = Heap->struttura;
    F_preorder(T,Heap->StampaElemento); // Stampa preorder con l'invio della procedura per la stampa del tipo di elemento

    return;
}

/* Stampa preorder dell'albero */
void F_preorder(Albero T,StampaTipo Stampa)
{
    if(T!=NULL)
    {
        F_stampa_priorita(T->coda->priorita);
        Stampa(T->coda->elem);
        F_preorder(T->ptrSx,Stampa);
        F_preorder(T->ptrDx,Stampa);
    }

    return;
}

/* Funzione per la stampa della priorita' */
void F_stampa_priorita(int elem)
{
    printf("|%d -",elem);

    return;
}

/* Funzione per l'estrazione del primo elemento di un Min/Max array */
void *F_estrai_minmax_array(StructHeap Heap)
{
    Array new_arr = Heap->struttura;

    if(new_arr!=NULL)
    {
        Coda minmax=new_arr[0].coda; // Preleva il primo elemento

        printf("\nL'elemento estratto e':\n");
        F_stampa_elem_coda(Heap,minmax);

        Heap->DistruggiTipoElem(Heap,0);
        free(new_arr[0].coda);

        puts("");
        new_arr[0].coda=new_arr[Heap->heapsize-1].coda;                         // Prelevo l'ultimo elemento dell'array e lo inserisco in testa
        new_arr = (Array) realloc(new_arr, (Heap->heapsize-1) * sizeof(Array)); // Rialloco l'array
        Heap->heapsize=Heap->heapsize-1;                                        // Setto la giusta dimensione
        Heap->struttura = new_arr;
        F_heapify(Heap,0);                                                      // Richiamo heapify per ripristinare la proprita' heap
    }
    else
        puts("Error: struttura non presente!\n");

    return  new_arr;
}

/* Funzione per la stampa di un elemento della coda */
void F_stampa_elem_coda(StructHeap Heap,Coda minmax)
{
    F_stampa_priorita(minmax->priorita);
    Heap->StampaElemento(minmax->elem); // Richiama: F_stampa_intero||float||carattere||stringa

    return;
}

/* Funzione per l'estrazione del primo elemento di un Min/Max dell'albero */
void *F_estrai_minmax_albero(StructHeap Heap)
{
    Albero new_abr = Heap ->struttura;

    if(new_abr != NULL)
    {
        Coda minmax = new_abr->coda;

        printf("\nL'elmento estratto e':\n");
        F_stampa_elem_coda(Heap,minmax);
        puts("");

        F_Scambio_Albero(Heap,0,Heap->heapsize-1); // Scambio i valori della radice con quelli dell'ultima foglia
        F_elimina_foglia(Heap); // Elimino la foglia
        F_heapify(Heap,0);  // Richiamo heapify per ripristinare la proprieta' heap

    } else
        puts("Error: struttura non presente!\n");

    return new_abr;
}

/* Provvede all'eliminazione dell'ultima foglia dell'albero */
void F_elimina_foglia(StructHeap Heap)
{
    Albero ultima_foglia = F_preleva_nodo(Heap,Heap->heapsize-1);       // Prelevo la foglia da eliminare
    ultima_foglia->coda->priorita = -1;
    Albero padre_foglia = F_preleva_nodo(Heap,((Heap->heapsize-2)/2)); // Prelevo il padre della foglia
    F_stampa_elem_coda(Heap,padre_foglia->coda);

    Heap->DistruggiTipoElem(Heap,Heap->heapsize-1); // Richiama: F_distruggi_elemento_array/albero||intero||float||carattere||stringa
    if(padre_foglia->ptrDx != NULL) // Elimino il legame con il figlio
    {
        //puts("\nHO MESSO DESTRA NULL");
        padre_foglia->ptrDx = NULL;
    }
    else{
      if(padre_foglia->ptrSx != NULL)
      {
          //puts("\nHO MESSO SINISTRA NULL");
          padre_foglia->ptrSx = NULL;
      }
    }
    free(ultima_foglia);
    Heap->heapsize=Heap->heapsize-1;

    return;
}

/* Funzione per decrementare la priorita' di un elemento con struttura array */
void F_decrease_key_array(StructHeap Heap)
{
    Array new_arr = Heap->struttura;

    puts("\nL'array e':");
    F_stampa_array(Heap);
    printf("\nSrivimi il numero di indice (da 1 a N) della priorita' che vuoi cambiare:");
    int elem_selezionato = F_seleziona(2,'1','9',0);
    int i = F_seleziona_indice(Heap,elem_selezionato);

    if(i!=-1)   // Verifico che sia stato scelto un indice corretto
    {
        printf("\nInserisci un valore per la nuova chiave che sia piu' piccolo di (%d):",new_arr[i].coda->priorita);
        int val = F_seleziona(3,'0','8',-1);

        if(Heap->max_min == 1) // Minimo
            F_esegui_decrease_key_array_min(Heap,i,val);
        else    // Massimo
            F_esegui_decrease_key_array_max(Heap,i,val);
    }

    return;
}

/* Funzione decrease per Max array */
void F_esegui_decrease_key_array_max(StructHeap Heap,int i,int val)
{
    Array arr = Heap->struttura;
    if(val > arr[i].coda->priorita ) puts("\nNuova chiave piu' grande!");
    else
    {
        arr[i].coda->priorita = val;
        F_heapify(Heap,i);
    }
    return;
}

/* Funzione decrease per Min array */
void F_esegui_decrease_key_array_min(StructHeap Heap,int i,int val)
{
    Array arr = Heap->struttura;

    if(val > arr[i].coda->priorita ) puts("\nNuova chiave piu' grande!");
    else
    {
        arr[i].coda->priorita = val;
        //printf("\nINDICE PASSATO: %d\n",i);
        //printf("\nINDICE DEL PADRE: %d\n",((i+1)/2)-1);
        while(i>0 && arr[i].coda->priorita < arr[(((i+1)/2)-1)].coda->priorita)
        {
            F_Scambio_Array(Heap,i,(((i+1)/2)-1));
            i = (((i+1)/2)-1);
          //  printf("\nINDICE DEL PADRE CICLO: %d\n",((i+1)/2)-1);
        }
    }

    return;
}

/* Permette la coretta selezione dell'indice scelto dall'utente */
int F_seleziona_indice(StructHeap Heap,int elem_selezionato)
{
    int indice=-1;

    if(elem_selezionato <= Heap->heapsize)
    {
            indice = elem_selezionato -1;
    } else
        puts("\nHai selezionato un indice troppo grande!\n");

    return indice;
}

/* Funzione per decrementare la priorita' di un elemento con struttura albero */
void F_decrease_key_albero(StructHeap Heap)
{
    puts("\nL'albero e':");
    F_stampa_albero(Heap);
    printf("\nAttenzione, la stampa dell'albero e' in preorder!\nSrivimi il numero di indice (da 1 a N) della priorita' che vuoi cambiare:");
    int elem_selezionato = F_seleziona(2,'1','9',0);
    int i = F_seleziona_indice(Heap,elem_selezionato);

    if(i!=-1)    // Verifico che sia stato scelto un indice corretto
    {
        Albero cambio_nodo = F_preleva_nodo(Heap,i);
        printf("\nInserisci un valore per la nuova chiave che sia piu' piccolo di (%d):",cambio_nodo->coda->priorita);
        int val = F_seleziona(3,'0','9',-1);

        if(Heap->max_min == 1) // Minimo
            F_esegui_decrease_key_albero_min(Heap,i,val);
        else    // Massimo
            F_esegui_decrease_key_albero_max(Heap,i,val);
    }
    return;
}

/* Funzione decrease per Max albero */
void F_esegui_decrease_key_albero_max(StructHeap Heap,int i,int val)
{
    //Albero alb = Heap->struttura;
    Albero nodo = F_preleva_nodo(Heap,i);

    if(val > nodo->coda->priorita) puts("\nNuova chiave piu' grande!");
    else
    {
        nodo->coda->priorita = val;
        F_heapify(Heap,i);
    }

    return;
}

/* Funzione decrease per Min albero */
void F_esegui_decrease_key_albero_min(StructHeap Heap,int i, int val)
{
    Albero nodo = F_preleva_nodo(Heap,i);

    if(val > nodo->coda->priorita) puts("\nNuova chiave piu' grande!");
    else
    {
       // printf("\n->|%d|<- INDICE PASSATO\n",i);
        nodo->coda->priorita = val;
        Albero nodo_padre = F_preleva_nodo(Heap,((i+1)/2)-1);
       // printf("\n->|%d|<- INDICE\n", ((i+1)/2)-1);
        while(i > 0 && nodo_padre->coda->priorita > nodo->coda->priorita)
        {
            F_Scambio_Albero(Heap,i,((i+1)/2)-1);
            i = ((i+1)/2)-1;
            nodo_padre = F_preleva_nodo(Heap,((i+1)/2)-1);
            nodo = F_preleva_nodo(Heap,i);
        }
    }
    return;
}

/* Funzione per incrementare la priorita' di un elemento con struttura array */
void F_increase_key_array(StructHeap Heap)
{
    Array new_arr = Heap->struttura;

    puts("\nL'array e':");
    F_stampa_array(Heap);
    printf("\nSrivimi il numero di indice (da 1 a N) della priorita' che vuoi cambiare:");
    int elem_selezionato = F_seleziona(2,'1','9',0);
    int i = F_seleziona_indice(Heap,elem_selezionato);

    if(i!=-1)
    {
        printf("\nInserisci un valore per la nuova chiave che sia piu' grande di (%d):",new_arr[i].coda->priorita);
        int val = F_seleziona(3,'0','9',-1);

        if(Heap->max_min == 1) // MINIMO
            F_esegui_increase_key_array_min(Heap,i,val);
        else
            F_esegui_increase_key_array_max(Heap,i,val);
    }

    return;
}

/* Funzione increase per Max array */
void F_esegui_increase_key_array_max(StructHeap Heap,int i,int val)
{
    Array arr = Heap->struttura;

    if(val < arr[i].coda->priorita ) puts("\nNuova chiave piu' piccola!");
    else
    {
        arr[i].coda->priorita = val;
        while(i>0 && arr[i].coda->priorita > arr[(((i+1)/2)-1)].coda->priorita)
        {
            F_Scambio_Array(Heap,i,(((i+1)/2)-1));
            i = (((i+1)/2)-1);
        }
    }
    return;
}

/* Funzione increase per Min array */
void F_esegui_increase_key_array_min(StructHeap Heap,int i,int val)
{
    Array arr = Heap->struttura;
    if(val < arr[i].coda->priorita ) puts("\nNuova chiave piu' piccola!");
    else
    {
        arr[i].coda->priorita = val;
        F_heapify(Heap,i);
    }
    return;
}

/* Funzione per incrementare la priorita' di un elemento con struttura albero */
void F_increase_key_albero(StructHeap Heap)
{
    puts("\nL'albero e':");
    F_stampa_albero(Heap);
    printf("\nAttenzione, la stampa dell'albero e' in preorder!\nSrivimi il numero di indice (da 1 a N) della priorita' che vuoi cambiare:");
    int elem_selezionato = F_seleziona(2,'1','9',0);
    int i = F_seleziona_indice(Heap,elem_selezionato);

    if(i!=-1)
    {
        Albero cambio_nodo = F_preleva_nodo(Heap,i);
        printf("\nInserisci un valore per la nuova chiave che sia piu' grande di (%d):",cambio_nodo->coda->priorita);
        int val = F_seleziona(3,'0','9',-1);

        if(Heap->max_min == 1) // Minimo
            F_esegui_increase_key_albero_min(Heap,i,val);
        else    // Massimo
            F_esegui_increase_key_albero_max(Heap,i,val);
    }

    return;
}

/* Funzione increase per Max albero */
void F_esegui_increase_key_albero_max(StructHeap Heap,int i,int val)
{
    Albero nodo = F_preleva_nodo(Heap,i);

    if(val < nodo->coda->priorita) puts("\nNuova chiave piu' piccola!");
    else
    {
        nodo->coda->priorita = val;
        Albero nodo_padre = F_preleva_nodo(Heap,((i+1)/2)-1);
        while(i > 0 && nodo_padre->coda->priorita < nodo->coda->priorita)
        {
            F_Scambio_Albero(Heap,i,((i+1)/2)-1);
            i = ((i+1)/2)-1;
            nodo_padre = F_preleva_nodo(Heap,((i+1)/2)-1);
            nodo = F_preleva_nodo(Heap,i);
        }
    }

    return;
}

/* Funzione increase per Min albero */
void F_esegui_increase_key_albero_min(StructHeap Heap,int i, int val)
{
    Albero nodo = F_preleva_nodo(Heap,i);

    if(val < nodo->coda->priorita) puts("\nNuova chiave piu' piccola!");
    else
    {
        nodo->coda->priorita = val;
        F_heapify(Heap,i);
    }
    return;
}

/* Funzione per l'inserimento di un nuovo elemento in una struttura heap array */
void F_inserisci_elemento_array(StructHeap Heap)
{
    Array new_arr = Heap->struttura;

    puts("\nL'array e':");
    F_stampa_array(Heap);
    Coda elemento_coda = F_genera_elememento_coda_utente(Heap); // Chiede all'utente l'inserimento di priorita' e dell'elemento dell'heap
    new_arr = (Array) realloc(new_arr, (Heap->heapsize+1) * sizeof(Array)); // Rialloco il vettore
    Heap->heapsize=Heap->heapsize+1;    // Setto la dimensione giusta
    new_arr[Heap->heapsize-1].coda=elemento_coda; // Associo l'elemento creato
    Heap->struttura = new_arr;
    //printf("\n\nELM: %d \n\n",new_arr[Heap->heapsize-1].coda->priorita);
    int i = Heap->heapsize-1;

    // Ripristino proprieta' heap
    if(Heap->max_min==1) // Minimo
    {
        // printf("\n\n%d\n\n",i);
        while(i>0 && new_arr[i].coda->priorita < new_arr[(((i+1)/2)-1)].coda->priorita)
        {
            F_Scambio_Array(Heap,i,(((i+1)/2)-1));
            i = (((i+1)/2)-1);
        }
    }
    else // Massimo
    {
        // printf("\n\n%d\n\n",i);
        while(i>0 && new_arr[i].coda->priorita > new_arr[(((i+1)/2)-1)].coda->priorita)
            {
                F_Scambio_Array(Heap,i,(((i+1)/2)-1));
                i = (((i+1)/2)-1);
            }
    }
    return;
}

/* Funzione per l'inserimento di un nuovo elemento in una struttura heap albero */
void F_inserisci_elemento_albero(StructHeap Heap)
{
   Albero T = Heap->struttura;

    puts("L'albero e':");
    F_stampa_albero(Heap);
    Coda elemento_coda = F_genera_elememento_coda_utente(Heap); // Chiede all'utente l'inserimento di priorita' e dell'elemento dell'heap
    T = F_inserisci_nodo_albero(T,elemento_coda,Heap->heapsize); // Inserisco il nuovo nodo mantenendo l'albero completo
    Heap->heapsize=Heap->heapsize+1;
    Heap->struttura = T;
    int i = Heap->heapsize-1;
    Albero nodo_padre = F_preleva_nodo(Heap,((i+1)/2)-1);
    Albero nodo = F_preleva_nodo(Heap,i);

    // Ripristino proprieta' heap
    if(Heap->max_min==1) // Minimo
    {
        while(i > 0 && nodo_padre->coda->priorita > nodo->coda->priorita)
        {
            F_Scambio_Albero(Heap,i,((i+1)/2)-1);
            i = ((i+1)/2)-1;
            nodo_padre = F_preleva_nodo(Heap,((i+1)/2)-1);
            nodo = F_preleva_nodo(Heap,i);
        }
    }
    else    // Massimo
    {
        while(i > 0 && nodo_padre->coda->priorita < nodo->coda->priorita)
        {
            F_Scambio_Albero(Heap,i,((i+1)/2)-1);
            i = ((i+1)/2)-1;
            nodo_padre = F_preleva_nodo(Heap,((i+1)/2)-1);
            nodo = F_preleva_nodo(Heap,i);
        }
    }

    return;
}

/* Funzione per prelevare un valore intero */
void *F_prendi_intero()
{
    /* DICHIARAZIONI VARIABILI */
    char tmp[]="**********",c='*';
    int intero_preso=0,i=0,flag=0;

    printf("\nTipologia di elemento di heap: INTERI.\nI valori vengono presi in modulo.\nInserire un valore intero (Max: %d):",INT_MAX);

    do
    {
        while( i<10 && (c= (char) getchar()) != '\n' && c != EOF )
        {
            if(c>='0' && c<='9')
            {
                tmp[i]=c;
                i++;
            }

        }
        sscanf(tmp,"%d",&intero_preso);

        if(intero_preso<0) // Superato il liminte viene preso un valore negativo.
        {
            printf("Valore inserito maggiore del limite massimo!\nInserisci di nuovo:");
            while('\n'!=getchar());

            /* Inizializzo vettore */
            for(i=0;i<11+2;i++)
                tmp[i]='*';

            i=0;
        }
        else // Valore corretto
            flag=1;

    }while(flag==0);

    int *elemento=malloc(sizeof(int));
    memcpy(elemento,&intero_preso,sizeof(int));

    return elemento;
}

/* Costruisce mediate l'interazione dell'utente un elemento della coda */
Coda F_genera_elememento_coda_utente(StructHeap Heap)
{
    Coda nuovo_elem=(struct struttura_elemento_coda *)malloc(sizeof(struct struttura_elemento_coda));

    printf("\nInserisci la priorita' del nuovo elemento:");
    int priorita = F_seleziona(3,'0','9',-1);
    printf("\nInserisci l'elemento che vuoi sia associato alla priorita' (%d)",priorita);
    void * elem = Heap->PrendiInput();

    nuovo_elem->priorita=priorita;
    nuovo_elem->elem=elem;

    //printf("Priorita inserita: %d - Elem inserito: %d\n",nuovo_elem->priorita,*((int *)nuovo_elem->elem));

    return nuovo_elem;
}

/* Funzione per la cancellazione di un elemento nella struttura heap array */
void F_cancella_elemento_array(StructHeap Heap)
{

    Array new_arr = Heap->struttura;
    puts("L'array e':");
    F_stampa_array(Heap);
    printf("\nSeleziona l'elemento da cancellare:");
    int elem_selezionato = F_seleziona(2,'1','9',0);
    int i = F_seleziona_indice(Heap,elem_selezionato);

    if(i!=-1)
    {
        if(new_arr[Heap->heapsize-1].coda->priorita > new_arr[i].coda->priorita) // Eseguo increase
        {
            if(Heap->max_min==1) // Minimo
                F_esegui_increase_key_array_min(Heap,i,new_arr[Heap->heapsize-1].coda->priorita);
            else    // Massimo
                F_esegui_increase_key_array_max(Heap,i,new_arr[Heap->heapsize-1].coda->priorita);
        } else  // Eseguo decrease
        {
            if(Heap->max_min==1) // Minimo
                F_esegui_decrease_key_array_min(Heap,i,new_arr[Heap->heapsize-1].coda->priorita);
            else    // Massimo
                F_esegui_decrease_key_array_max(Heap,i,new_arr[Heap->heapsize-1].coda->priorita);
        }

        // Dealloco l'elemento
        Heap->DistruggiTipoElem(Heap,Heap->heapsize-1);
        Heap->heapsize=Heap->heapsize-1;
    }

    return;
}

/* Funzione per la cancellazione di un elemento nella struttura heap albero */
void F_cancella_elemento_albero(StructHeap Heap)
{
    puts("L'albero e':");
    F_stampa_albero(Heap);
    printf("\nAttenzione, la stampa dell'albero e' in preorder!\nSeleziona l'elemento da cancellare:");
    int elem_selezionato = F_seleziona(2,'1','9',0);
    int i = F_seleziona_indice(Heap,elem_selezionato);

    if(i!=-1)
    {
        Albero foglia = F_preleva_nodo(Heap, Heap->heapsize - 1);
        Albero  padre_foglia = F_preleva_nodo(Heap,((((Heap->heapsize-1)+1)/2)-1));

       // printf("\nI %d - - HPS %d",i,Heap->heapsize);

        if(Heap->heapsize>1 && i!=Heap->heapsize-1)
        {
            Albero nodo = F_preleva_nodo(Heap, i);
         //   printf("\nELEM SELEZIONATO: %d",nodo->coda->priorita);

            if (foglia->coda->priorita > nodo->coda->priorita) // Eseguo increase
            {
                if (Heap->max_min == 1) // Minimo
                    F_esegui_increase_key_albero_min(Heap, i, foglia->coda->priorita);
                else // Massimo
                    F_esegui_increase_key_albero_max(Heap, i, foglia->coda->priorita);
            } else // Eseguo decrease
            {
                if (Heap->max_min == 1) // Minimo
                    F_esegui_decrease_key_albero_min(Heap, i, foglia->coda->priorita);
                else    // Massimo
                    F_esegui_decrease_key_albero_max(Heap, i, foglia->coda->priorita);
            }
        }

        //  printf("\nHEPS:%d\n",Heap->heapsize);
        Heap->DistruggiTipoElem(Heap,Heap->heapsize-1);

        if(Heap->heapsize-1==0) // Non sono più presenti elementi nella struttura
        {
            Heap->struttura=NULL;
        } else  // Elimino il collegamento con l'elemento
        {
            int figliodxsn = ((Heap->heapsize-1)%2); // Tutti i nodi posti a destra hanno indice pari, dispari altrimenti
            if(figliodxsn==0) padre_foglia->ptrDx=NULL;
            else padre_foglia->ptrSx=NULL;
        }

        free(foglia);
        Heap->heapsize=Heap->heapsize-1;

    }
    return;
}

/* Eliminazione elemento array intero */
void F_distruggi_elem_array_intero(StructHeap Heap,int indice)
{
    Array A = Heap->struttura;
    printf("\nELIMINO %d\n",A[indice].coda->priorita);
    free(((int *)A[indice].coda->elem));
    return;
}

/* Eliminazione elemento albero intero */
void F_distruggi_elem_albero_intero(StructHeap Heap,int indice)
{
    Albero nodo = F_preleva_nodo(Heap,indice);
    printf("\nELIMINO %d\n",nodo->coda->priorita);
    free(((int *)nodo->coda->elem));
    return;
}

/* Esegue la deallocazione della struttura array */
void F_dealloca_array(StructHeap Heap)
{
    Array arr = Heap->struttura;
    int i=0;

    for(i=0;i<Heap->heapsize;i++)
    {
        Heap->DistruggiTipoElem(Heap,i); // Richiama: F_distruggi_elem_array_intero||float||carattere||stringa
        free(arr[i].coda);
    }

    return;
}

/* Prepara la deallocazione della struttura albero */
void F_dealloca_albero(StructHeap Heap)
{
    Albero T = Heap->struttura;
    F__dealloca_albero(T);  // Effettua la deallocazione

    return;
}

/* Deallocazione di una struttura albero */
void F__dealloca_albero(Albero T)
{
    if(T!=NULL)
    {
        F__dealloca_albero(T->ptrSx);
        F__dealloca_albero(T->ptrDx);
        free(T->coda);
        free(T);
    }
    return;
}

/* Funzione per la stampa del primo elemento */
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