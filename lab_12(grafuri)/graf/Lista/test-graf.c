/*--- test-graf.c ---*/
#include "graf-L.h"

void AfiM(void* g)
{ int i,j,k, n = NrNoduri(g);
  for (i = 1; i <= n; i++)
  { for (j = 1; j <= n; j++)
    { k = CostArc(g,i,j);
      if(k == ArcInex) printf("  - ");
      else printf("%3i ", k);
    }
    printf("\n");
  }
}

int main()
{
  void* g;

  if (CitGraf(&g) <= 0)
  { printf("-=- eroare la citire -=-\n"); return -1;}
  printf(" -=- graf cu %i noduri -=-\n", NrNoduri(g));
  AfiM(g);

  /*-- apel functii definite --*/
  AGL gl = (AGL)g;
  int nod, max, u, v;
  //Exercitiul 1
  printf("\nExercitiul 1:\n");
  printf("nod = "); scanf("%d", &nod);
  printf("Grad iesire = %d\n", grad_iesire(g, nod));
  //Exercitiul 2
  printf("\nExercitiul 2:\n");
  int *vizitat = (int *)calloc(gl->nn + 1, sizeof(int));
  dfs(g, 1, vizitat);
  printf("\n");
  //BONUS
  printf("\nBONUS:\n");
  max = arc_cost_max(g, &u, &v);
  printf("(%d %d) de cost %d\n", u, v, max);
  DistrG(&g);
  free(vizitat);
  return 0;
}
