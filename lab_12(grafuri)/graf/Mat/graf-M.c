/*--- graf-M.c --- Graf implementat cu Matrice de adiacente --*/
#include "graf-M.h"
#include <string.h>

void* AlocG(int nr)
{ int i;
  AGM g = (AGM)malloc (sizeof(TGM));              /* spatiu descriptor */
  if (!g) return NULL;
  g->x = (int*)malloc(nr * nr * sizeof(int)); /* matrice liniarizata */
  if (!g->x) { free(g); return NULL; }
  for (i = 0; i < nr * nr; i++)
    g->x[i] = ArcInex;
  g->nn = nr;
  return (void*)g;
}


void DistrG(void** ag)
{ free (((AGM)(*ag))->x);
  free(*ag);
  * ag = NULL;
}


int CostArc(void* g, int s, int d)
{
  /* functia intoarce costul arcului (s, d); daca arcul nu exista intoarce ArcInex */
  AGM gm = (AGM)g;
  int cost = gm->x[(s - 1) * gm->nn + d - 1];
  if(cost) return cost;
  return ArcInex;
}

int NrNoduri(void* g)
{
    return ((AGM)g)->nn;
}

int CitGraf(void** ag)
{ FILE * f;
  char numefis[21];
  int i, j, n;
  int x;
  AGM g;

  printf("Numele fisierului de descriere a grafului = ");
  if (!scanf("%s", numefis)) return -1;
  f = fopen(numefis, "rt");
  if (!f) return -2;
  if (!fscanf(f, "%i", &n) || n <= 0) return -3;
  *ag = g = (AGM)AlocG(n);
  if (!g) return 0;
  while (fscanf(f, "%i%i%i", &i, &j, &x) == 3)
  { if (i < 1 || i > n || j < 1 || j > n)
    { fclose(f); return -4;}
      ((AGM)g)->x[(i-1)*((AGM)g)->nn + j-1] = x;
  }
  fclose(f);
  return 1;
}

int grad_iesire(void *g, int nod) {
  AGM gm = (AGM)g;
  int i, contor = 0;
  if (nod > gm->nn) {
    return ArcInex;
  }
  for (i = 1; i <= gm->nn; i++) {
    if (CostArc(gm, nod, i)) {
      contor++;
    }
  }
  return contor;
}

void dfs(void *g, int nod, int *vizitat) {
  AGM gm = (AGM)g;
  int i;
  vizitat[nod] = 1;
  printf("%d ", nod);
  for (i = 1; i <= gm->nn; i++) {
    if (CostArc(gm, nod, i) && vizitat[i] == 0) {
      dfs(g, i, vizitat); 
    }
  }
}

int arc_cost_max(void *g, int *u, int *v) {
  int max = -1, i;
  AGM gm = (AGM)g;
  int *inc, *sf, *p;
  for (i = 1; i <= gm->nn; i++) {
    inc = gm->x + (i - 1) * gm->nn;
    sf = inc + gm->nn;
    for (p = inc; p != sf; p++) {
      if ((*p) >= max) {
        *u = i;
        *v = p - inc + 1;
        max = *p;
      }
    }
  }
  return max;
}