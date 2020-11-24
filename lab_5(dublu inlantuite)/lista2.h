/*-- lista2.h -- Lista generica dublu inalntuita, circulara, cu santinela
              si info = pointer la element --*/
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "tlg.h"

#ifndef _LISTA_DUBLU_INLANTUITA_
#define _LISTA_DUBLU_INLANTUITA_

typedef struct celula2
{
  void *info;              /* adresa element extern */
  struct celula2 *pre, *urm;  /* legaturi spre celulele vecine */
} TCelula2, *TLDI;

typedef struct punct {
	int x;
	int y;
}TPunct;

/* Initializare lista vida; info santinela = NULL */
TLDI InitLDI();

/* Inserare dupa celula cu adresa p -> 1/0. Preconditia: spatiul pentru
   elementul cu adresa x a fost alocat si actualizat la nivelul aplicatiei */
int InsDupa(TLDI p, void* x);

/* elimina celula de la adresa p; rezultat: adresa elementului sau NULL */
void* ExtrLDI(TLDI p);

/*- functii de eliberare spatiu; parametrul fe � functie care elibereaza
    spatiul ocupat de element */
void ResetLDI(TLDI s); /* transforma lista in lista vida */
void DistrLDI(TLDI * as);
     /* elibereaza tot spatiul ocupat de lista, inclusiv santinela */
void AfisareLDI(TLDI s, void (*afiEl)(void *));  /* afisare lista */
#endif
