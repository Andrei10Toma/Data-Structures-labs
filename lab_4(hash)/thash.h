#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "tlg.h"

#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*);     /* functie afisare/eliberare un element */
typedef int (*TFHash)(void*);

typedef struct
{
    size_t M;
    TFHash fh;
    TLG *v;
} TH;

/* functii tabela hash */
TH* IniTH(size_t M, TFHash fh);
void DistrTH(TH**aa, TF fe);
void AfiTH(TH*a, TF afiEl);
void *ExistaTH(TH*a, void*ae, TFCmp f);
int InsTH(TH*a, void*ae, TFCmp f);
int ExtrTH(TH*a, void*ae, TFCmp f);
void afisareAutor (TH *ah, char nume[30]);/*afiseaza titlul cartilor scrise
de autorul cu numele nume*/
int stergere (TH *ah, char titluCarte[50]);/*sterge cartea cu titlul carte*/

#endif
