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

    StructHeap Heap = NULL;
    Heap = F_alloca_heap(Heap);
    Heap = F_info_heap(Heap);
    Heap = F_crea_heap(Heap);
    F_costruisci_heap(Heap);

    do
    {
        scelta = F_menu_principale(Heap->max_min);
        switch(scelta)
        {
            case 1:
                F_stampa_heap(Heap);
            break;
            case 2:
                F_inserisci_elemento(Heap);
                break;
            case 3:
                F_stampa_minmax(Heap);
            break;

            case 4:
                if(Heap->heapsize != 1)
                    F_estrai_minmax(Heap);
                else
                    puts("Presente solo la radice!\n");
            break;

            case 5:
                F_increase_key(Heap);
                break;
            case 6:
                F_decrease_key(Heap);
                break;
            case 7:
                F_cancella_elemento(Heap);
                break;
            case 0:
                menu_principale = 0;
            break;

            default:
                puts("Error");
                break;

        }

    }while(menu_principale!=0);


    return;
}

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
    scelta=F_seleziona(1);

    return scelta;
}


StructHeap F_info_heap(StructHeap Heap)
{
    int dim=0,tipo_heap=0,max_min=0,abr_arr=0;

    abr_arr = F_abr_arr();
    max_min = F_max_min_heap();
    tipo_heap = F_tipo_heap();
    dim = F_num_elem();

    F_aggiungi_info(Heap,dim,tipo_heap,max_min,abr_arr);

    return Heap;
}

int F_num_elem()
{
    int scelta=0;

    printf("\nNumero di elementi da inserire:");
    scelta=F_seleziona(2);

    return scelta;
}

int F_tipo_heap()
{
    int scelta=0;

    puts("\nDato presente nell'heap");
    puts("1] Interi");
    puts("2] Float");
    puts("3] Caratteri");
    puts("4] Stringhe");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1);

    return scelta;
}

int F_max_min_heap()
{
    int scelta=0;


    puts("\nTipologia di heap");
    puts("1] Minimo");
    puts("2] Massimo");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1);

    return scelta;
}

int F_abr_arr()
{
    int scelta=0;

    puts("Struttura da usare");
    puts("1] Albero");
    puts("2] Array");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1);

    return scelta;
}

int F_seleziona(int dim)
{
    /* DICHIARAZIONE VARIABILI */
        char tmp[dim],c='*';
        int intero_preso=0,i=0;


        fflush(stdin);

            while( i<dim && (c= (char) getchar()) != '\n' && c != EOF )
            {
                if(c>='0' && c<='9')
                {
                      tmp[i]=c;
                      i++;
                }
            }
        tmp[i]='\0';
        sscanf(tmp,"%d",&intero_preso);
    printf("\nHai scelto:%d\n",intero_preso);
    return intero_preso;
}

StructHeap F_crea_array(StructHeap Heap)
{
    int i=0;
    Array S=(struct struttura_elemento_array *)calloc((size_t) Heap->heapsize, sizeof(struct struttura_elemento_array));

    for(i=0;i<Heap->heapsize;i++)
    {
        S[i].coda=F_genera_elemento_coda(Heap);
    }

    Heap->struttura = S;

    return Heap;
}

Coda F_genera_elemento_coda(StructHeap Heap)
{
    Coda nuovo_elem=(struct struttura_elemento_coda *)malloc(sizeof(struct struttura_elemento_coda));

    nuovo_elem->priorita=F_genera_priorita();
    nuovo_elem->elem=Heap->tipo_elem();


    printf("Priorita: %d - Elem: %d\n",nuovo_elem->priorita,*((int *)nuovo_elem->elem));

    return nuovo_elem;
}

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


Albero F_inserisci_nodo_albero(Albero T,Coda nuovo_elem,int indice)
{
    if(indice == 0)
    {
        puts("ALLOCO");
        T=F_alloca_nodo_albero(nuovo_elem);
    }
    else
    {
        Albero Tmp = T;
        int *bits = F_ottieni_bit(indice+1);

        int j=F_salta_zero_bit(bits);

        for(;j>=0;j--)
        {
            printf("\nLEGGO:%d\n",bits[j]);
            if(bits[j]==1)
            {

                puts("Destra");
                if(Tmp->ptrDx == NULL)
                    Tmp->ptrDx=F_inserisci_nodo_albero(Tmp,nuovo_elem,0);
                else
                    Tmp=Tmp->ptrDx;
            }
            else
            {
                puts("Sinistra");
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

int F_salta_zero_bit(int *bits)
{
    int j;
    for(j=DIMARRMASK-1;j>=0;j--)
    {
        if(bits[j]==1)
        {
            j--;
            break;
        }
    }
    return j;
}


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


Albero F_alloca_nodo_albero(Coda nuovo_elem)
{
    Albero nuovo_nodo=(struct struttura_nodo_albero *)malloc(sizeof(struct struttura_nodo_albero));
    nuovo_nodo->coda=nuovo_elem;
    nuovo_nodo->ptrDx=NULL;
    nuovo_nodo->ptrSx=NULL;

    return nuovo_nodo;
}


void F_aggiungi_info(StructHeap Heap,int dim,int tipo_heap,int max_min,int abr_arr)
{
    Heap->heapsize=dim;
    Heap->sinistra = F_HeapSx;
    Heap->destra = F_HeapDx;
    Heap->max_min = max_min;
    Heap->abr_arr = abr_arr;
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
        break;
        default:
            puts("Error");
            break;
    }

    switch(tipo_heap)
    {
        case 1: // Interi
            puts("Ineri");
            Heap->tipo_elem = F_crea_intero;
            Heap->StampaElemento = F_stampa_intero;
            Heap->PrendiInput = F_prendi_intero;
            if(abr_arr==2) Heap->DistruggiTipoElem = F_distruggi_elem_array_intero;
            else puts("Ci metto distruggi elem albero");
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
            puts("Error");
            break;
    }

}

// INTERI
void *F_crea_intero()
{
    void *elemento=malloc(sizeof(int));
    int i=rand();
    memcpy(elemento,&i,sizeof(int));

    return elemento;
}

void F_stampa_intero(void *elem)
{
    printf(" %d|",*((int *)elem));

    return;
}

// FLOAT
void *F_crea_float()
{
    float f=(float)rand()/(float)RAND_MAX;
    f=(rand()%100)+f;
    void *elemento=malloc(sizeof(float));
    memcpy(elemento,&f,sizeof(float));

    return elemento;
}

void *F_prendi_float()
{
    /* DICHIARAZIONE VARIABILI */
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

void F_stampa_stringa(void *elem)
{
    printf(" %s|",((char *)elem));
    return;
}


int F_genera_priorita()
{
    int i=rand() % (100 + 1 - 1) + 1;
    printf("Priorita: %d\n",i);

    return i;
}

//////////////////// HEAPIFY ////////////////////////
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

int F_FirstCheck_Array_MaxMin(StructHeap Heap,int l,int i)
{
    int mas=i;
    Array S = Heap->struttura;

    if(l<Heap->heapsize)
    {
        if(Heap->max_min == 1) // MINIMO
        {
            if(S[l].coda->priorita<S[i].coda->priorita)
            {
                mas=l;
            }
            else
            {
                mas=i;
            }

        } else // MASSIMO
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

int F_SecondCheck_Array_MaxMin(StructHeap Heap,int r,int mas)
{
    Array S = Heap->struttura;

    if(r<Heap->heapsize)
    {
        if(Heap->max_min == 1) // MINIMO
        {
            if(S[r].coda->priorita<S[mas].coda->priorita)
            {
                mas=r;
            }
        } else // MASSIMO
        {
            if(S[r].coda->priorita>S[mas].coda->priorita)
            {
                mas=r;
            }
        }

    }

    return mas;
}

int F_FirstCheck_Albero_MaxMin(StructHeap Heap,int l,int i)
{
    int mas=i;

    Albero nodo_l=F_preleva_nodo(Heap,l);
    Albero nodo_i=F_preleva_nodo(Heap,i);
    printf("\n1 Preso il nodo di indice l:%d | i:%d\n",l,i);

    if(l < Heap->heapsize)
        {
            int priorita_l = nodo_l->coda->priorita;
            int priorita_i = nodo_i->coda->priorita;
            printf("\n1 Ho preso le loro due priorira l:%d | i%d\n",priorita_l,priorita_i);

            if(Heap->max_min == 1) // MINIMO
            {
                if (priorita_l < priorita_i)
                {
                    printf("\n1 |%d e' piu grande di %d\n",priorita_l,priorita_i);
                    mas = l;
                }
                else
                {
                    printf("\n1 |%d e' piu piccola di %d\n",priorita_l,priorita_i);
                    mas = i;
                }

            } else // MASSIMO
            {
                if (priorita_l > priorita_i)
                {
                    printf("\n1 |%d e' piu grande di %d\n",priorita_l,priorita_i);
                    mas = l;
                }
                else
                {
                    printf("\n1 |%d e' piu piccola di %d\n",priorita_l,priorita_i);
                    mas = i;
                }
            }

        }
    printf("\n1 Ritorno con priorira mas per ora %d\n",mas);
    return mas;
}

int F_SecondCheck_Alebro_MaxMin(StructHeap Heap, int r,int mas)
{
    Albero nodo_r=F_preleva_nodo(Heap,r);
    Albero nodo_mas=F_preleva_nodo(Heap,mas);
    printf("\n2 Preso il nodo di indice r:%d | mas:%d\n",r,mas);
        if(r<Heap->heapsize)
        {
            int priorita_r = nodo_r->coda->priorita;
            int priorita_mas = nodo_mas->coda->priorita;
            printf("\n2 Ho preso le loro due priorira r:%d | mas%d\n",priorita_r,priorita_mas);

            if(Heap->max_min == 1) // MINIMO
            {
                if(priorita_r<priorita_mas)
                {
                    printf("\n2 La priorita %d e' piu grande di %d",priorita_r,priorita_mas);
                    mas=r;
                }
            } else // MASSIMO
            {
                if(priorita_r>priorita_mas)
                {
                    printf("\n2 La priorita %d e' piu grande di %d",priorita_r,priorita_mas);
                    mas=r;
                }
            }

        }
    printf("\n2 Ritorno con priorira mas definitiva %d\n",mas);

    return mas;
}

Albero F_preleva_nodo(StructHeap Heap,int indice)
{
    Albero nodo = Heap->struttura;

    int *bits = F_ottieni_bit(indice+1);

    int j=F_salta_zero_bit(bits);

    for(;j>=0;j--)
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


void F_Scambio_Array(StructHeap Heap,int i,int mas)
{
    puts("\nFatto scambio");
    Array S = Heap->struttura;

    int tpriorita = S[i].coda->priorita;
    void *telem = S[i].coda->elem;

    S[i].coda->priorita = S[mas].coda->priorita;
    S[i].coda->elem = S[mas].coda->elem;
    S[mas].coda->priorita = tpriorita;
    S[mas].coda->elem = telem;

    return;
}

void F_Scambio_Albero(StructHeap Heap,int i,int mas)
{
    Albero nodo_i=F_preleva_nodo(Heap,i);
    Albero nodo_mas=F_preleva_nodo(Heap,mas);

    int priorita_i = nodo_i->coda->priorita;
    void *telem = nodo_i->coda->elem;

    printf("\nInizio lo scambio della priorira i:%d con la prioria mas:%d\n",i,mas);
    printf("\nIn i ho %d. In mas ho %d",nodo_i->coda->priorita,nodo_mas->coda->priorita);

    nodo_i->coda->priorita = nodo_mas->coda->priorita;
    nodo_i->coda->elem = nodo_mas->coda->elem;

    nodo_mas->coda->elem = telem;
    nodo_mas->coda->priorita = priorita_i;

    printf("\nHo terminato lo scambio ora ho in i ho %d. In mas ho %d",nodo_i->coda->priorita,nodo_mas->coda->priorita);

    return;
}
//////////////////// FINE HEAPIFY ////////////////////////



void F_stampa_heap(StructHeap Heap)
{
    Heap->Stampa(Heap);

    return;
}


void F_stampa_array(StructHeap Heap)
{
    int i=0;
    Array S = Heap->struttura;

    puts("Ecco l'array:");
    for(i=0;i<Heap->heapsize;i++)
    {
        F_stampa_priorita(S[i].coda->priorita);
        Heap->StampaElemento(S[i].coda->elem);
    }

    return;
}

void F_stampa_albero(StructHeap Heap)
{
    Albero T = Heap->struttura;
    F_preorder(T,Heap->StampaElemento);

    return;
}

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


void F_stampa_priorita(int elem)
{
    printf("|%d -",elem);

    return;
}


void *F_estrai_minmax_array(StructHeap Heap)
{
    Array new_arr = Heap->struttura;

    if(new_arr!=NULL)
    {
        Coda minmax=new_arr[0].coda;

        printf("\nL'elemento estratto e':\n");
        F_stampa_elem_coda(Heap,minmax);

        // DEALLOCA LA CODA

        puts("");

        new_arr[0].coda=new_arr[Heap->heapsize-1].coda;
        new_arr = (Array) realloc(new_arr, (Heap->heapsize-1) * sizeof(Array));
        Heap->heapsize=Heap->heapsize-1;
        //printf("\n%d - %d\n",new_arr[0].coda->priorita,new_arr[1].coda->priorita);
        Heap->struttura = new_arr;

        F_heapify(Heap,0);
    }
    else
        puts("Error");

    // Stampa l'elemento prima di cancellarlo
    return  new_arr;
}

void F_stampa_elem_coda(StructHeap Heap,Coda minmax)
{
    F_stampa_priorita(minmax->priorita);
    Heap->StampaElemento(minmax->elem);

    return;
}

void *F_estrai_minmax_albero(StructHeap Heap)
{
    Albero new_abr = Heap ->struttura;

    if(new_abr != NULL)
    {
        Coda minmax = new_abr->coda;

        printf("\nL'elmento estratto e':\n");
        F_stampa_elem_coda(Heap,minmax);
        puts("");

        // Scambio i valori della radice con quelli dell'ultima foglia
        F_Scambio_Albero(Heap,0,Heap->heapsize-1);

        // Eliminare la foglia (i padri della foglia hanno sempre il nodo / 2 ?!)
        F_elimina_foglia(Heap);

        F_heapify(Heap,0);

    } else
        puts("Error");

    return new_abr;
}

void F_elimina_foglia(StructHeap Heap)
{
    Albero ultima_foglia = F_preleva_nodo(Heap,Heap->heapsize-1);
    ultima_foglia->coda->priorita = -1; // NON SERVE
    Albero padre_foglia = F_preleva_nodo(Heap,((Heap->heapsize-2)/2));


    F_stampa_elem_coda(Heap,padre_foglia->coda);


    if(padre_foglia->ptrDx != NULL)
    {
        puts("\nHO MESSO DESTRA NULL");
        padre_foglia->ptrDx = NULL;
    }
    else{
      if(padre_foglia->ptrSx != NULL)
      {
          puts("\nHO MESSO SINISTRA NULL");
          padre_foglia->ptrSx = NULL;
      }
    }

    // DEALLOCARE ULTIMA FOGLIA

    Heap->heapsize=Heap->heapsize-1;

    return;
}

void F_decrease_key_array(StructHeap Heap)
{
    Array new_arr = Heap->struttura;

    puts("\nL'array e':");
    F_stampa_array(Heap);
    printf("\nSrivimi il numero di indice (da 1 a N) della priorita' che vuoi cambiare:");
    int elem_selezionato = F_seleziona(3);
    int i = F_seleziona_indice(Heap,elem_selezionato);

    if(i!=-1)
    {
        printf("\nInserisci un valore per la nuova chiave che sia piu' piccolo di (%d):",new_arr[i].coda->priorita);
        int val = F_seleziona(3);

        if(Heap->max_min == 1) // MINIMO
            F_esegui_decrease_key_array_min(Heap,i,val);
        else
            F_esegui_decrease_key_array_max(Heap,i,val);
    }

    return;
}

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

void F_esegui_decrease_key_array_min(StructHeap Heap,int i,int val)
{
    Array arr = Heap->struttura;

    if(val > arr[i].coda->priorita ) puts("\nNuova chiave piu' grande!");
    else
    {
        arr[i].coda->priorita = val;
        printf("\nINDICE PASSATO: %d\n",i);
        printf("\nINDICE DEL PADRE: %d\n",((i+1)/2)-1);
        while(i>0 && arr[i].coda->priorita < arr[(((i+1)/2)-1)].coda->priorita)
        {
            F_Scambio_Array(Heap,i,(((i+1)/2)-1));
            i = (((i+1)/2)-1);
            printf("\nINDICE DEL PADRE CICLO: %d\n",((i+1)/2)-1);
        }
    }

    return;
}

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

void F_decrease_key_albero(StructHeap Heap)
{
    puts("\nL'albero e':");
    F_stampa_albero(Heap);
    printf("\nSrivimi il numero di indice (da 1 a N) della priorita' che vuoi cambiare:");
    int elem_selezionato = F_seleziona(3);
    int i = F_seleziona_indice(Heap,elem_selezionato);

    if(i!=-1)
    {
        Albero cambio_nodo = F_preleva_nodo(Heap,i);
        printf("\nInserisci un valore per la nuova chiave che sia piu' piccolo di (%d):",cambio_nodo->coda->priorita);
        int val = F_seleziona(3);

        if(Heap->max_min == 1) // MINIMO
            F_esegui_decrease_key_albero_min(Heap,i,val);
        else
            F_esegui_decrease_key_albero_max(Heap,i,val);
    }
    return;
}

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

void F_esegui_decrease_key_albero_min(StructHeap Heap,int i, int val)
{
    Albero nodo = F_preleva_nodo(Heap,i);

    if(val > nodo->coda->priorita) puts("\nNuova chiave piu' grande!");
    else
    {
        printf("\n->|%d|<- INDICE PASSATO\n",i);
        nodo->coda->priorita = val;
        Albero nodo_padre = F_preleva_nodo(Heap,((i+1)/2)-1);
        printf("\n->|%d|<- INDICE\n", ((i+1)/2)-1);
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


// INCREASE

void F_increase_key_array(StructHeap Heap)
{
    Array new_arr = Heap->struttura;

    puts("\nL'array e':");
    F_stampa_array(Heap);
    printf("\nSrivimi il numero di indice (da 1 a N) della priorita' che vuoi cambiare:");
    int elem_selezionato = F_seleziona(3);
    int i = F_seleziona_indice(Heap,elem_selezionato);

    if(i!=-1)
    {
        printf("\nInserisci un valore per la nuova chiave che sia piu' grande di (%d):",new_arr[i].coda->priorita);
        int val = F_seleziona(3);

        if(Heap->max_min == 1) // MINIMO
            F_esegui_increase_key_array_min(Heap,i,val);
        else
            F_esegui_increase_key_array_max(Heap,i,val);
    }

    return;
}

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


void F_increase_key_albero(StructHeap Heap)
{
    puts("\nL'albero e':");
    F_stampa_albero(Heap);
    printf("\nSrivimi il numero di indice (da 1 a N) della priorita' che vuoi cambiare:");
    int elem_selezionato = F_seleziona(3);
    int i = F_seleziona_indice(Heap,elem_selezionato);

    if(i!=-1)
    {
        Albero cambio_nodo = F_preleva_nodo(Heap,i);
        printf("\nInserisci un valore per la nuova chiave che sia piu' grande di (%d):",cambio_nodo->coda->priorita);
        int val = F_seleziona(3);

        if(Heap->max_min == 1) // MINIMO
            F_esegui_increase_key_albero_min(Heap,i,val);
        else
            F_esegui_increase_key_albero_max(Heap,i,val);
    }

    return;
}

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

void F_inserisci_elemento_array(StructHeap Heap)
{
    Array new_arr = Heap->struttura;

    puts("\nL'array e':");
    F_stampa_array(Heap);
    Coda elemento_coda = F_genera_elememento_coda_utente(Heap);
    new_arr = (Array) realloc(new_arr, (Heap->heapsize+1) * sizeof(Array));
    Heap->heapsize=Heap->heapsize+1;
    new_arr[Heap->heapsize-1].coda=elemento_coda;
    Heap->struttura = new_arr;
    printf("\n\nELM: %d \n\n",new_arr[Heap->heapsize-1].coda->priorita);
    int i = Heap->heapsize-1;

    if(Heap->max_min==1) // MINIMO
    {
        printf("\n\n%d\n\n",i);
        while(i>0 && new_arr[i].coda->priorita < new_arr[(((i+1)/2)-1)].coda->priorita)
        {
            F_Scambio_Array(Heap,i,(((i+1)/2)-1));
            i = (((i+1)/2)-1);
        }
    }
    else
    {
        printf("\n\n%d\n\n",i);
        while(i>0 && new_arr[i].coda->priorita > new_arr[(((i+1)/2)-1)].coda->priorita)
            {
                F_Scambio_Array(Heap,i,(((i+1)/2)-1));
                i = (((i+1)/2)-1);
            }
    }
    return;
}

void F_inserisci_elemento_albero(StructHeap Heap)
{
   Albero T = Heap->struttura;

    puts("L'albero e':");
    F_stampa_albero(Heap);
    Coda elemento_coda = F_genera_elememento_coda_utente(Heap);
    T = F_inserisci_nodo_albero(T,elemento_coda,Heap->heapsize);
    Heap->heapsize=Heap->heapsize+1;
    Heap->struttura = T;
    int i = Heap->heapsize-1;
    Albero nodo_padre = F_preleva_nodo(Heap,((i+1)/2)-1);
    Albero nodo = F_preleva_nodo(Heap,i);

    if(Heap->max_min==1) // MINIMO
    {
        while(i > 0 && nodo_padre->coda->priorita > nodo->coda->priorita)
        {
            F_Scambio_Albero(Heap,i,((i+1)/2)-1);
            i = ((i+1)/2)-1;
            nodo_padre = F_preleva_nodo(Heap,((i+1)/2)-1);
            nodo = F_preleva_nodo(Heap,i);
        }
    }
    else
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

        if(intero_preso<0) // Superato il liminte viene preso un valore negativo. Si necessita quindi di <0 e non >INT_MAX
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

Coda F_genera_elememento_coda_utente(StructHeap Heap)
{
    Coda nuovo_elem=(struct struttura_elemento_coda *)malloc(sizeof(struct struttura_elemento_coda));

    printf("\nInserisci la priorita' del nuovo elemento:");
    int priorita = F_seleziona(4);
    printf("\nInserisci l'elemento che vuoi sia associato alla priorita' (%d)",priorita);
    void * elem = Heap->PrendiInput();

    nuovo_elem->priorita=priorita;
    nuovo_elem->elem=elem;

    //printf("Priorita inserita: %d - Elem inserito: %d\n",nuovo_elem->priorita,*((int *)nuovo_elem->elem));

    return nuovo_elem;
}

void F_cancella_elemento_array(StructHeap Heap)
{
    Array new_arr = Heap->struttura;

    puts("L'array e':");
    F_stampa_array(Heap);
    printf("\nSeleziona l'elemento da cancellare:");
    int elem_selezionato = F_seleziona(3);
    int i = F_seleziona_indice(Heap,elem_selezionato);

    if(i!=-1)
    {
        new_arr[i].coda->priorita = new_arr[Heap->heapsize-1].coda->priorita;
        new_arr[i].coda->elem = new_arr[Heap->heapsize-1].coda->elem;

        if(new_arr[Heap->heapsize-1].coda->priorita > new_arr[i].coda->priorita)
        {
            puts("SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS");
            if(Heap->max_min==1)
                F_esegui_decrease_key_array_min(Heap,i,new_arr[Heap->heapsize-1].coda->priorita);
            else
                F_esegui_increase_key_array_max(Heap,i,new_arr[Heap->heapsize-1].coda->priorita); // MAS
        } else
        {
            if(Heap->max_min==1)
                F_esegui_increase_key_array_min(Heap,i,new_arr[Heap->heapsize-1].coda->priorita);
            else
                F_esegui_decrease_key_array_max(Heap,i,new_arr[Heap->heapsize-1].coda->priorita); // MAS
        }

        F_distruggi_elem(Heap,Heap->heapsize-1);
        free(new_arr[Heap->heapsize-1].coda);
        new_arr = (Array) realloc(new_arr, (Heap->heapsize-1) * sizeof(Array));
        Heap->struttura = new_arr;
        Heap->heapsize=Heap->heapsize-1;
    }

    return;
}

void F_cancella_elemento_albero(StructHeap Heap)
{
    Albero T = Heap->struttura;
    puts("L'albero e':");
    F_stampa_albero(Heap);
    printf("\nSeleziona l'elemento da cancellare:");
    int elem_selezionato = F_seleziona(3);
    int i = F_seleziona_indice(Heap,elem_selezionato);

    if(i!=-1)
    {
        Albero foglia = F_preleva_nodo(Heap,Heap->heapsize-1);
        Albero nodo = F_preleva_nodo(Heap,i);
        //int priorita_vecchia=nodo->coda->priorita;
        nodo->coda->priorita = foglia->coda->priorita;
        nodo->coda->elem = foglia->coda->elem;

        puts("O11111111K");
        if(foglia->coda->priorita > nodo->coda->priorita)
        {
            if(Heap->max_min==1)
            F_esegui_decrease_key_albero_min(Heap,nodo->coda->priorita,foglia->coda->priorita);
            else
            F_esegui_increase_key_albero_max(Heap,nodo->coda->priorita,foglia->coda->priorita);
        } else
        {
            if(Heap->max_min==1)
                F_esegui_increase_key_albero_min(Heap,nodo->coda->priorita,foglia->coda->priorita);
            else
                F_esegui_decrease_key_albero_max(Heap,nodo->coda->priorita,foglia->coda->priorita);
        }


        Heap->heapsize = Heap->heapsize-1;
        Heap->struttura = T;
    }

    return;
}

void F_distruggi_elem(StructHeap Heap,int indice)
{
    Heap->DistruggiTipoElem(Heap,indice);
    return;
}

void F_distruggi_elem_array_intero(StructHeap Heap,int indice)
{
    Array A = Heap->struttura;
    printf("\nELIMINO %d\n",A[indice].coda->priorita);
    free(((int *)A[indice].coda->elem));
    return;
}