/*--- testLista.c ---*/
#include <ctype.h>
#include <stdio.h>
#include "tlista.h"

TLista CitireL(int *lg)     /* construieste lista cu elemente citite */
{ TLista L = NULL, u, aux;
  int x;
  char ch;
  for(*lg = 0; scanf("%i", &x) == 1; )
  {
    aux = AlocCelula(x);           /* incearca inserarea valorii citite */
    if(!aux) return L;              /* alocare esuata => sfarsit citire */
    if(L == NULL) L = aux;
    else u->urm = aux;
    u = aux;
    (*lg)++;
  }

  while((ch=getchar()) != EOF && ch != '\n');
  return L;                     /* intoarce lista rezultat */
}

int main ()
{ TLista x = NULL, r=NULL;     /* Lista prelucrata */
  int lx, y, aux, a, b;           /* lungime lista */
  for (;;)
  {
    /* citeste si afiseaza lista */
    printf("\nIntroduceti valori elemente terminate cu valoare nenumerica:\n");
    x = CitireL(&lx);
    AfisareL(x);
    if(!x) continue;

    /* apeluri functii implementate */
    int i=-1, s=-1;
    printf("%d\n", Perechi(x));
    printf("%d\n", Identice(x));
    printf("%d\n", Secventa(x,&i,&s));
    printf("%d\n", Insert(&x));
    scanf("%d", &y);
    printf("%d\n", Elimina(&x, y));
    scanf("%d%d", &a, &b);
    printf("%d\n", EliminaAB(&x, a, b));
    r=Copiere(x, &i);
    r=Mutare (&x, &i);
    AfisareL(r);
    AfisareL(x);
    r=createOrd(&y);
    AfisareL(r);
    DistrugeL(&x);
    printf ("\n  Inca un test ? [d/n]");
    if (getchar() == 'n') break;
  }
}
