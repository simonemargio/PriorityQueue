#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <math.h>
#include "L_Heap.h"
#define DIMARRMASK 32
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

            case 3:
                F_stampa_minmax(Heap);
            break;

            case 4:
                if(Heap->heapsize != 1)
                    F_estrai_minmax(Heap);
                else
                    puts("Presente solo la radice!\n");
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

    //    S[i].elemArray=Heap->tipo_elem();
    //    printf("\n->ELM %d\n",*((int *)S[i].elemArray));
    //    S[i].priorita=F_genera_priorita();
    //    printf("\n->PRI %d\n",S[i].priorita);
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

      //  elemento=Heap->tipo_elem();
      //  priorita=F_genera_priorita();
      //  printf("Priorita: %d - Elemento: %d\n",priorita,*((int *)elemento));

        //T=F_inserisci_nodo_albero(T,elemento,priorita,i);

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
        /* Attenzione: uso l'indice + 1
         * Se uso indice so esattamente in che posto mettere il nodo. All'inizio è 0+1=1 però sti cazzi essendo T null
         * viene creato la rafice. Poi l'indice diventa 1+1=2, e uno in binario è 00000000010, come detto il pof
         * si eliminano tutti gli zero e il primo 1 che si trova, in questo caso ottengo 0 che e quindi mi sposto a sinistra
         * dove è proprio che devo andare.
         * Poi l'indice diventa 3, in binario 00000011, elimino tutti gli zero e il primo 1 e ottengo 1, mi sposto a destra.
         * Poi 4, 000000100, ottengo 00, mi sposto due volte a sinistra e così via...
         *
         * Quindi trovare un modo per portare un intero a binario, conto passo passo tutti gli zero fino al primo 1, tutti
         * i numeri successivi mi dicono dove mi devo spostare
         */
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

/*Albero F_inserisci_nodo_albero(Albero T,Coda nuovo_elem,int indice)
{
    if(indice==0)
    {
        T=F_alloca_nodo_albero(nuovo_elem);
    }
    else
    {
        int i=0,j=0,maschera=0,heapsize=indice+1,prim_elem=0;
        Albero tmp = T;

        maschera = (int) pow(2, (int)log2(heapsize));
        while(j<log2((double)(maschera))+1)
        {
            i=(maschera>>j)&(heapsize);

            if(i>0)
            {
                if(prim_elem == 0)
                {
                    prim_elem = 1;
                }
                else
                {
                    puts("Destra");
                    if(tmp->ptrDx == NULL)
                    {
                        tmp->ptrDx = F_inserisci_nodo_albero(tmp,nuovo_elem,0);
                       // break;
                    }
                    else
                    {
                        tmp = tmp->ptrDx;
                    }
                }
            }
            else
            {
                puts("Sinistra");
                if(tmp->ptrSx == NULL)
                {
                    tmp->ptrSx = F_inserisci_nodo_albero(tmp,nuovo_elem,0);
                   // break;
                }
                else
                {
                    tmp = tmp->ptrSx;
                }
            }
          j++;
        }
    }

    return T;
}*/

Albero F_alloca_nodo_albero(Coda nuovo_elem)
{
    Albero nuovo_nodo=(struct struttura_nodo_albero *)malloc(sizeof(struct struttura_nodo_albero));
    //nuovo_nodo->elem=elemento;
    //nuovo_nodo->priorita=priorita;
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
            puts("Albero");
            Heap->tipo_struttura = F_crea_albero;
            Heap->Scambio=F_Scambio_Albero;
            Heap->Stampa = F_stampa_albero;
            Heap->EstraiMinMax = F_estrai_minmax_albero;

            Heap->FirstCheck = F_FirstCheck_Albero_MaxMin;
            Heap->SecondCheck = F_SecondCheck_Alebro_MaxMin;
        break;

        case 2: // Array
           Heap->tipo_struttura = F_crea_array;
           Heap->Scambio = F_Scambio_Array;
           Heap->Stampa = F_stampa_array;
           Heap->EstraiMinMax = F_estrai_minmax_array;

           Heap->FirstCheck = F_FirstCheck_Array_MaxMin;
           Heap->SecondCheck = F_SecondCheck_Array_MaxMin;
        break;
        default:
            puts("Error");
            break;
    }

   /* switch(max_min)
    {
        case 1: // Minimo
      //  Heap->tipo_min_max = F_crea_minimo;
            if(abr_arr == 1)
            {
                    puts("");
            }
            else
            {
           //     Heap->FirstCheck = F_FirstCheck_Array_Min;
             //   Heap->SecondCheck = F_SecondCheck_Array_Min;
            }
        break;

        case 2: // MAssimo
      //      Heap->tipo_min_max = F_crea_massimo;
            if(abr_arr == 1)
            {
                puts("Albero MAX");
                //Heap->FirstCheck= F_FirstCheck_Albero_Max;
            //    Heap->FirstCheck = F_FirstCheck_Albero_MaxMin;
                //Heap->SecondCheck= F_SecondCheck_Alebro_Max;
              //  Heap->SecondCheck = F_SecondCheck_Alebro_MaxMin;
            }
            else
            {
             //   Heap->FirstCheck = F_FirstCheck_Array_Max;
//               Heap->SecondCheck = F_SecondCheck_Array_Max;
             //  Heap->FirstCheck = F_FirstCheck_Albero_MaxMin;
               // Heap->SecondCheck = F_SecondCheck_Alebro_MaxMin;
            }
        break;
        default:
            puts("Error");
            break;
    }*/

    switch(tipo_heap)
    {
        case 1: // Interi
            puts("Ineri");
            Heap->tipo_elem = F_crea_intero;
            Heap->StampaElemento = F_stampa_intero;
        break;

        case 2: // Float
      //      Heap->tipo_elem = F_crea_float;
        break;

        case 3: // caratteri
     //       Heap->tipo_elem = F_crea_carattere;
        break;

        case 4: // Stringhe
      //      Heap->tipo_elem = F_crea_stringa;
        break;

        default:
            puts("Error");
            break;

    }

}


void *F_crea_intero()
{
    void *elemento=malloc(sizeof(int));
    int i=rand();
    memcpy(elemento,&i,sizeof(int));
 //  printf("\n->->----------------------Elem creato:%d\n",*(int *)elemento);
    return elemento;
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

         //   int priorita_l = nodo_l->priorita;
          //  int priorita_i = nodo_i->priorita;
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
           // int priorita_r=nodo_r->priorita;
           // int priorita_mas=nodo_mas->priorita;

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

/*
Albero F_preleva_nodo(StructHeap Heap,int indice) {
    int i = 0, j = 0, maschera = 0, heapsize = indice + 1, prim_elem = 0;
    Albero nodo = Heap->struttura;


    if (heapsize > 1)
    {
        maschera = (int) pow(2, (int) log2(heapsize));

        while (nodo != NULL && j < log2((double) (maschera))+1)
        {
            printf("\nJ:%d\n",j);
            i=(maschera>>j)&(heapsize);

            if (i > 0)
            {
                if (prim_elem == 0)
                {
                    prim_elem = 1;
                } else
                {
                    puts("Destra 1");
                    nodo = nodo->ptrDx;
                }
            }
            else
            {
                puts("Sinistra 1");
                nodo = nodo->ptrSx;
            }
            j++;
        }

    }

    return nodo;
}*/

/*int F_FirstCheck_Array_Min(StructHeap Heap,int l,int i)
{

    int mas=0;
    Array S = Heap->struttura;



    if((l<Heap->heapsize) && (S[l].coda->priorita<S[i].coda->priorita))
    {
        mas=l;
      //  printf("\nConfronto priorita %d - %d\n",S[l].priorita,S[i].priorita);
    }
    else
        mas=i;
    return mas;
}*/

/*int F_SecondCheck_Array_Min(StructHeap Heap,int r,int mas)
{
    Array S = Heap->struttura;
    if((r<Heap->heapsize) &&(S[r].coda->priorita<S[mas].coda->priorita))
        mas=r;


    return mas;
}*/



void F_Scambio_Array(StructHeap Heap,int i,int mas)
{
    puts("\nFatto scambio");
    Array S = Heap->struttura;

    int tpriorita = S[i].coda->priorita;
    void *telem = S[i].coda->elem;

    S[i].coda->priorita = S[mas].coda->priorita;
    S[i].coda->elem = S[mas].coda->elem;

    //S[i].priorita=S[mas].priorita;
    //S[i].elemArray=S[mas].elemArray;

    S[mas].coda->priorita = tpriorita;
    S[mas].coda->elem = telem;

    //S[mas].priorita = tpriorita;
    //S[mas].elemArray = telem;
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
}
//////////////////// FINE HEAPIFY ////////////////////////



void F_stampa_heap(StructHeap Heap)
{
    Heap->Stampa(Heap);
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

}

void F_stampa_albero(StructHeap Heap)
{
    Albero T = Heap->struttura;
    F_preorder(T,Heap->StampaElemento);
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
}

void F_stampa_intero(void *elem)
{
    printf(" %d|",*((int *)elem));
}

void F_stampa_priorita(int elem)
{
     printf("|%d -",elem);
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

     //   F_heapify(Heap,0);
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
    ultima_foglia->coda->priorita = -1;
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









