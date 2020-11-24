/*--- graf-L.c --- Graf implementat cu liste --*/
#include "graf-L.h"

void* AlocG(int nr) /* aloca spatiu pentru descriptor graf si
	                      vector de (n+1) adrese liste arce */
{
  AGL g = (AGL)malloc(sizeof(TGL));    /* spatiu descriptor */
  if (!g) return NULL;
  g->x = (AArc*)calloc((nr+1), sizeof(AArc)); /* spatiu vector adr.liste arce */
  if(!g->x) { free(g); return NULL; }
  g->nn = nr;
  return (void*)g;
}

void DistrG(void** ag)
{ int i;
  AArc p, aux;
  for(i = 1; i < NrNoduri(*ag); i++)
  { p = ((AGL)(*ag))->x[i];
    while(p)
    { aux = p; p = p->urm;
      free(aux);
    }
  }
  free(((AGL)(*ag))->x);
  free(*ag);
  *ag = NULL;
}


int CostArc(void* g, int s, int d)
{   /* intoarce costul arcului (s, d); daca arcul nu exista intoarce ArcInex */
    AGL gl = (AGL)g;
    AArc list_ad = gl->x[s];
    for(; list_ad; list_ad = list_ad->urm)
      if(list_ad->d == d) return list_ad->c;
    return ArcInex;
}

int NrNoduri(void* g)
{ return ((AGL)(g))->nn; }



int CitGraf(void** ag)
{ FILE * f;
  char numefis[21];
  AGL g;
  int s, d;
  int x;
  AArc *p, aux;
  int n;

  printf("Numele fisierului de descriere a grafului = ");
  if (!scanf("%s", numefis)) return -1;
  f = fopen (numefis, "rt");
  if (!f) return -2;
  if (!fscanf (f, "%i", &n) || n <= 0) return -3;
  *ag = AlocG(n);
  g = *(AGL*)ag;
  if (!g) return 0;
  while (fscanf(f, "%i%i%i", &s, &d, &x) == 3)
  { if (s < 1 || s > n || d < 1 || d > n)
    { fclose(f); return -4;}
    p = g->x + s;
    while (*p && (*p)->d < d) p = &(*p)->urm;
    aux = (TCelArc*)calloc(sizeof(TCelArc),1);
    if (!aux) return -2;                     /* criza spatiu */
    aux->urm = *p; *p = aux;
    aux->d = d; aux->c = x;
  }
  fclose(f);
  return 1;
}

int grad_iesire(void *g, int nod) {
  AGL gl = (AGL)g;
  if (nod > gl->nn) {
    return -1;
  }
  int contor = 0;
  AArc p = gl->x[nod];
  for (;p != NULL; p = p->urm) {
    if (p->c) {
      contor ++;
    }
  }
  return contor;
}

void dfs(void *g, int nod, int *vizitat) {
  AGL gl = (AGL)g;
  AArc p = gl->x[nod];
  vizitat[nod] = 1;
  printf("%d ", nod);
  for (; p != NULL; p = p->urm) {
    if (vizitat[p->d] == 0) {
      dfs(g, p->d, vizitat);
    }
  }
}

int arc_cost_max(void *g, int *u, int *v) {
  AGL gl = (AGL) g;
  AArc p; int i, max = -1;
  for (i = 1; i <= gl->nn; i++) {
    for (p = gl->x[i]; p != NULL; p = p->urm) {
      if (p->c >= max) {
        *u = i;
        *v = p->d;
        max = p->c;
      }
    }
  }
  return max;
}

int gradIntrare(void *g, int nod) {
  AGL gl = (AGL)g;
  AArc p;
  int i, contor = 0;
  for (i = 1; i <= gl->nn; i++) {
    for (p = gl->x[i]; p != NULL; p = p->urm) {
      if (p->d == nod) {
        contor++;
      }
    }
  }
  return contor;
}

void nodGradIntrareMaxim(void *g, int *nM, int *gM) {
  AGL gl = (AGL)g;
  int i;
  *gM = -1;
  *nM = -1;
  for (i = 1; i <= gl->nn; i++) {
    if (gradIntrare(gl, i) > *gM) {
      *gM = gradIntrare(gl, i);
      *nM = i;
    }
  }
}

void sortareNoduri_aux(void *g, int *vizitat, int *gM, int *nM) {
  AGL gl = (AGL)g;
  int i;
  *gM = -1;
  *nM = -1;
  for (i = 1; i <= gl->nn; i++) {
    if (vizitat[i] == 0){
      if (gradIntrare(gl, i) >= *gM) {
        *gM = gradIntrare(gl, i);
        *nM = i;
      }
    }
  }
  vizitat[*nM] = 1;
}

void sortareNoduri(void *g) {
  AGL gl = (AGL)g;
  int gM, nM;
  int *vizitat = (int *)calloc(sizeof(int), gl->nn + 1), i;
  for (i = 1; i <= gl->nn; i++) {
    sortareNoduri_aux(gl, vizitat, &gM, &nM);
    printf("%d ", nM);
  }
  printf("\n");
}

int existaDrum(void *g, int s, int d) {
  AGL gl = (AGL)g;
  if (CostArc(gl, s, d)) {
    return 1;
  }
  AArc p, p1;
  for (p = gl->x[s]; p != NULL; p = p->urm) {
    for (p1 = gl->x[p->d]; p1 != NULL; p1 = p1->urm) {
      if (p1->d == d) {
        return 1;
      }
    }
  }
  return 0;
}

int urmAdiacent(void *g, int n, int u) {
  AGL gl = (AGL)g;
  AArc p;
  for (p = gl->x[n]; p != NULL; p = p->urm) {
    if (p->d == u) {
      break;
    }
  }
  if (p->urm != NULL)
    return p->urm->d;
  else
    return 0;
}