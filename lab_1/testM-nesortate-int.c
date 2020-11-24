/*-- testM-nesortate-int.c --*/
#include "multimeV.h"

/*-- functie de afisare multime intregi --*/
void AfisareMultime_int(TMultime *m)
{ int *x = (int*)(m->p), n = Cardinal(m), i = 0;
  printf("[");
  for( ; i < n; i++) 
	if(i != n-1) printf(" %i,", x[i]);
	else printf(" %i ]", x[i]);
}

int compI(const void *a, const void *b) /*-- functie de comparare --*/
{ return *(int*)a - *(int*)b; }

int main()
{ int va[20] = {-1, 23, 4, 6, -9, 4, 10}, nva = 7,
      vb[10] = {2, 4, -9, 12, 10, 1, 11}, nvb = 7; 
  TMultime *a, *b, *r, *s;
  int i, rez;
  
  /* constructie multime a */
  a = InitD(7, sizeof(int), compI);
  if(!a) {printf("eroare initializare\n"); return 1;}
  printf("\nConstructie multime a, cu elementele: ");
  for(i = 0; i < nva; i++) printf("%i ", va[i]);
  printf("\n");
  for(i = 0; i < nva; i++) 
  { 
    rez = Adauga((void*)(va+i), a);
    printf("%i %s\n", va[i], rez? "adaugat" : "exista deja");
  }
  printf("Cardinal(a) = %d,  ", Cardinal(a)); 
  printf("a: "); AfisareMultime_int(a);

  
  /* constructie multime b */
  b=InitD(10, sizeof(int), compI); 
  printf("\nConstructie multime b, cu elementele: ");
  for(i = 0; i < nvb; i++) printf("%i ", vb[i]);
  printf("\n");
  for(i = 0; i < nvb; i++) 
  { 
    rez = Adauga((void*)(vb+i), b);
    printf("%i %s\n", vb[i], rez? "adaugat" : "exista deja");
  }
  printf("Cardinal(b) = %d, ", Cardinal(b)); 
  printf("b: "); AfisareMultime_int(b);
  printf("\n");
  /* apeluri functii implementate */
  r=InitD(Minim(Cardinal(a),Cardinal(b)), sizeof(int), compI);
  printf("%d\n", Intersectie(a, b, r));
  AfisareMultime_int(r);
  printf("\n");
  s=InitD(Maxim(Cardinal(a),Cardinal(b)),sizeof(int), compI);
  Diferenta(a,b,s);
  printf("%d\n", Diferenta(a,b,s));
  AfisareMultime_int(s);
  printf("\n");
/*  TMultime *aux=realloc(a, (Cardinal(a)+Cardinal(b))*a->d);
  a=aux;*/
  Reuniune(a,b);
  AfisareMultime_int(a);
  printf("\n");
  DistrugeM(&a);
  DistrugeM(&b);
  DistrugeM(&r);
  DistrugeM(&s);
  return 0;
}

