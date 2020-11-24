/*--- test-graf.c ---*/
#include "graf-M.h"

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
  int nod, u, v, max, nM, gM, s, d, n;
  // Exercitiul 1
  // printf("\nExercitiul 1:\n");
  // printf("nod = "); scanf("%d", &nod);
  // printf("Grad iesire = %d\n", grad_iesire(g, nod));
  // // Exercitiul 2
  // printf("\nExercitiul 2:\n");
  // AGM gm = (AGM)g;
  // int *vizitat = (int *)calloc(gm->nn + 1, sizeof(int));
  // dfs(g, 1, vizitat);
  // printf("\n");
  // // BONUS
  // printf("\nBONUS:\n");
  // max = arc_cost_max(g, &u, &v);
  // printf("(%d %d) de cost %d\n", u, v, max);


  //lab_13
  //Exercitiul 1
  printf("\nExercitiul 1:\n");
  nodGradIntrareMaxim(g, &nM, &gM);
  printf("Nod grad intrare max = %d grad intrare max = %d\n", nM, gM);

  //Exercitiul 2
  printf("\nExercitiul 2:\n");
  sortareNoduri(g);

  //Exercitiul 3
  printf("\nExercitiul3:\n");
  printf("Nod1 = ");scanf("%d", &s);
  printf("Nod2 = ");scanf("%d", &d);
  if (existaDrum(g, s, d)) {
    printf("\nExista drum\n");
  }
  else {
    printf("\nNu exista drum\n");
  }

  //BONUS
  printf("\nBONUS:\n");
  printf("Nod n = ");scanf("%d", &n);
  printf("Nod u = ");scanf("%d", &u);
  printf("Nodul %d este urmatorul nod adiacent al nodului %d dupa nodul %d\n",
  urmAdiacent(g, n, u), n, u);
  DistrG(&g);
  //free(vizitat);
  return 0;
}
