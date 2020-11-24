/*-- tlista.h --- LISTA SIMPLU INLANTUITA cu elemente de tip intreg ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#ifndef _LISTA_SIMPLU_INLANTUITA_
#define _LISTA_SIMPLU_INLANTUITA_

typedef struct celula
{ int info;
  struct celula * urm;
} TCelula, *TLista; /* tipurile Celula, Lista */

#define VidaL(L) ((L) == NULL)

/*-- operatii elementare --*/

TLista AlocCelula(int);          /* adresa celulei create sau NULL */
void   DistrugeL (TLista*);       /* elimina toate celulele din lista */

void AfisareL (TLista L);

int Perechi (TLista L);			/*functia afiseaza perechiile de elemente pare
consecutive si indicii pe care se gasesc acestia;indicii incep de la 1; functia
returneaza numarul de perechi gasire*/

int Identice (TLista L); /*functia returneaza 0 sau 1 daca functia este sau nu
alcatuita din 2 jumatati identice*/

int LungimeL (TLista L); /*returneaza lungimea listei*/

int Secventa (TLista L, int *i, int *s); /*returneaza lungimea secventei
daca nu este gasita nicio secventa indicii de inceput si final vor fi -1*/

int Insert (TLista *L); /*functia insereaza dupa fiecare element impar si
returneaza numarul de inserari facute*/

int Elimina (TLista *L, int x); /*elimina toate elementele cu valoarea x
si returneaza cate elemente de acest tip au fost eliminate*/

int EliminaAB (TLista *L, int a, int b);/*elimina elementele dintre a
si b*/

TLista Copiere (TLista L, int *nr); /**/

TLista Mutare (TLista *L, int *nr);

TLista createOrd (int *nr); /*ordoneaza o lista pe masura ce elementele
sunt citite de la tastatura*/

#endif
