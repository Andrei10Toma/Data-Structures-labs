#include "TArb.h"
#include <math.h>

#define log2(x) (log(((double)x)) / log(2.0))
#define kMax 100

int insertABC(TArb* a, int x)
/* insereaza x in arborele binar de cautare */
{
  while (*a)
  { if ( x == (*a)->info) return -1;
    if ( x < (*a)->info)
      a = &((*a)->st);
    else
      a = &((*a)->dr);
  }

  /* inserare */
  *a = create_leaf(x);
  if(!*a) return 0; /* intoarce 0 */
  return 1; /* intoarce 1 */
}

TArb create_leaf(int x){
	TArb aux = (TArb)malloc (sizeof(TNod));
	if (!aux) return NULL;
	  aux->info = x;
    aux->st = NULL;
    aux->dr = NULL;

	return aux;
}

TArb create_ABC(int num)
/* generează un arbore cu elemente alese random și fiecare fiu al unui nod este ales random */
{
  // int niv;
    // int lim = ceil(log2(num)) + 1;
  TArb a = NULL;
  int n, x;
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &x);
    insertABC(&a, x);
  }

  /*srand(time(NULL));
  while (num > 0) {
        insertABC(&a, rand() % kMax);
        num--;
  }*/
  return a;
}

void distruge(TArb a)
{
    if(a == NULL)
        return;
    distruge(a->st);
    distruge(a->dr);
    free(a);
}

void distrugeArb(TArb *a)
{
	distruge(*a);
	*a = NULL;
}
