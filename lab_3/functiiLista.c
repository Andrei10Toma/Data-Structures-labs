/*-- functiiLista.c --*/
#include <ctype.h>
#include "tlista.h"

/*--- operatii de baza pentru lista simplu inlantuita ---*/

TLista AlocCelula(int e)          /* adresa celulei create sau NULL */
{ TLista aux = (TLista)malloc(sizeof(TCelula));  /* (1) incearca alocare */
  if (aux)                            /* aux contine adresa noii celule */
  { aux->info = e;                   /* (2,3) completeaza noua celula */
    aux->urm = NULL;
  }
  return aux;             /* rezultatul este adresa noii celule sau NULL */
}

void AfisareL(TLista L)
       /* afiseaza valorile elementelor din lista */
{
  printf("Lista: [");                      /* marcheaza inceput lista */
  for (; L != NULL; L = L->urm)       /* pentru fiecare celula */
    printf("%d ", L->info);              /* afiseaza informatie */
  printf("]");
  printf("\n");                               /* marcheaza sfarsit lista */
}

void DistrugeL(TLista* aL)
{
  TLista aux;
  while(*aL)
  {
    aux = *aL;
    *aL = aux->urm;
    free(aux);
  }
}

int Perechi (TLista L)
{
  int nr=0, indice=0;
  TLista p;
  for (p=L;p!=NULL;p=p->urm)
  {
    indice++;
    if (p->urm!=NULL)
      if (p->info%2==0 && p->urm->info%2==0)
      {
        nr++;
        printf("[%d %d] - %d %d\n", p->info, p->urm->info, indice, indice+1);
      }
  }
  return nr;
}

int LungimeL (TLista L)
{
  int lg=0;
  TLista p;
  for (p=L;p!=NULL;p=p->urm)
    lg++;
  return lg;
}

int Identice (TLista L)
{
  TLista p=L, q=L;
  int lg=LungimeL(L), ind=1;
  if (lg%2!=0)
    return 0;
  while (ind<=lg/2)
  {
    q=q->urm;
    ind++;
  }
  for (;q!=NULL;q=q->urm,p=p->urm)
    if (q->info!=p->info)
      return 0;
  return 1;
}

int Secventa (TLista L, int *i, int *s)
{
  TLista p;
  int indice=0;
  for (p=L;p!=NULL;p=p->urm)
  {
    indice++;
    if (p->urm!=NULL)
      if (p->info==p->urm->info)
      {
        int x=p->info;
       *i=indice;
       while (p->info==x)
       {
         *s=indice;
          indice++;
         if (p->urm!=NULL)
           p=p->urm;
         else
           break;
      }
      break;
    }
  }
  printf("%d %d\n", *i, *s);
  return (*s)-(*i)+1;
}

int Insert (TLista *L)
{
  int nr_ins=0;
  TLista p;
  if ((*L)==NULL)
    return 0;
  TLista aux;
  for (p=*L;p!=NULL;p=p->urm)
  {
    if (p->info%2!=0)
    {
      aux=AlocCelula(p->info);
      aux->urm=p->urm;
      p->urm=aux;
      nr_ins++;
      p=p->urm;
    }
  }
  AfisareL(*L);
  return nr_ins;
}