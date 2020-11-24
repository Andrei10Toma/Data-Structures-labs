/*--- graf.h --- Graf --*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef GRAF__
#define GRAF__


#define NodInex 0
#define ArcInex 0

void* AlocG(int); /* aloca memorie pt.reprezentare graf cu nr.noduri dat */
void DistrG(void**);  /* elibereaza tot spatiul ocupat de graf */

int CostArc(void*, int, int);
int NrNoduri(void* g);

int CitGraf(void**);  /* citeste descriere graf */
void AfiGrafM(void*); /* afisare ca matrice */
void AfiGrafL(void*); /* afisare liste de adiacente */

int grad_iesire(void *g, int nod); /*determina gradul de iesire al nodului nod*/
void dfs(void *g, int nod, int *vizitat);/*parcurge in adancime graful de la nodul nod*/
int arc_cost_max(void *g, int *u, int *v);/*arcul cu cost maxim*/

#endif
