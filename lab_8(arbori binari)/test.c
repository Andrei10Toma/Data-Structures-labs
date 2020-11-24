#include "TArb.h"

static char desen[18][81], cri[] = "xxx";  /* zona reprezentare arbore, info */
static int limita = 17;                    /* linia limita de desenare */

void Repr(TArb r, int centru, int linie, int dif)
		 /*- functie auxiliara - pregateste desen arbore, cu radacina in centru linie+1
	 dif - distanta pe orizontala intre r si fiecare dintre cei doi descendenti
	 Exemple:  dif = 5    |        dif = 2    |
					 xxx                 xxx
				___/ \___              / \
			 |         |            |   |                               -*/
{
	int k;

	if (linie > limita) return;
	if (dif <= 1) {      /* spatiu de afisare insuficient -> ... */
		memset(desen[linie]+centru, '.', 3);
		return;
	}
	desen[linie][centru] = '|';      /* legatura spre nod */
	desen[linie][0] = ':';
	if (linie+1 > limita) return;
	sprintf(cri, "%3i", r->info);   /* converteste valoare info la 3 caractere */
	k = (cri[0] == ' ') ? 2 : 1;    /* decalaj fata de centru */
	memcpy(desen[linie+1] + centru - k, cri, 3); /* copiaza cele 3 caractere in desen */
	desen[linie+1][0] = ':';
	if (linie+2 > limita) return;
	if (r->st) {
		desen[linie+2][centru-1] = '/';                     /* reprezinta ramura  ____/  */
		desen[linie+2][0] = ':'; desen[linie+3][0] = ':';
		memset(desen[linie+2] + centru - dif + 1, '_', dif-2);
		Repr(r->st, centru - dif, linie + 3, (dif+1)/2 );   /* si subarborele stang */
	}
	if (r->dr) {
		desen[linie + 2][centru+1] = '\\';                  /* reprezinta ramura  \____  */
		desen[linie+2][0] = ':'; desen[linie+3][0] = ':';
		memset (desen[linie+2] + centru + 2, '_', dif-2);
		Repr(r->dr, centru + dif, linie + 3, (dif+1)/2 );   /* si subarborele drept */
	}
}

void AfisareArb(TArb r) /*- afiseaza arborele r -*/
{
	int j;

	for (j = 0; j <= limita; j++)
		memset (desen[j], ' ', 79);
	if (!r)
		printf ("%49s", "-=- Arbore VID -=-");
	else {
		Repr(r,40,0,19); /* preg reprezentare cu centrul in coloana 39 a primei linii */
		for (j = 0; j <= limita && desen[j][0] == ':'; j++) {
			desen[j][79] = '\0'; printf("%s\n", desen[j]+1);
		}
	}
	printf ("\n");
}

int depth(TArb root)
{
	if (!root) return 0;
	int maxDepthL=depth(root->st);
	int maxDepthR=depth(root->dr);
	if (maxDepthL>maxDepthR)
		return maxDepthL+1;
	else
		return maxDepthR+1;
}

void aux(TArb root, int *nr_frunze)
{
	if (!root) return;
	if (!root->st && !root->dr)
		(*nr_frunze)++;
	aux(root->st, nr_frunze);
	aux(root->dr, nr_frunze);
}

int nod_impar(int nod)
{
	if (nod % 2==1)
		return 1;
	return 0;
}

int num_of_leafs(TArb root)
{
	int leafs=0;
	if (!root) return 0;
	aux(root, &leafs);
	return leafs;
}

void aux1(TArb a, TF f, int *nr_noduri_imp)
{
	if (!a) return;
	if (f(a->info))
		(*nr_noduri_imp)++;
	aux1(a->st, f, nr_noduri_imp);
	aux1(a->dr, f, nr_noduri_imp);
}

int F1(TArb a, TF f)
{
	int nr_noduri_imp=0;
	if (!a) return 0;
	aux1(a, f, &nr_noduri_imp);
	return nr_noduri_imp;
}

void aux3(TArb a, int k, int nivcrt)
{
	if (!a) return;
	if (nivcrt==k)
		printf("%d ", a->info);
	aux3(a->st, k, nivcrt+1);
	aux3(a->dr, k, nivcrt+1);
}

void afisareNivel(TArb a, int k)
{
	int nivcrt=0;
	printf("Nivel %d: ", k);
	aux3(a, k, nivcrt);
	printf("\n");
}

void aux4(TArb a, int niv_min, int niv_max, int nivcrt, void *s) {
	if (!a) {
		return;
	}
	aux4(a->st, niv_min, niv_max, nivcrt + 1, s);
	aux4(a->dr, niv_min, niv_max, nivcrt + 1, s);
	if (nivcrt >= niv_min && nivcrt <= niv_max) {
	TPunct *p = (TPunct *)calloc(sizeof(TPunct), 1);
		if (a->st && a->dr) {
			p->x = a->st->info;
			p->y = a->dr->info;
			Push(s, p);
		}
		else if (!a->st && a->dr) {
			p->x = 0;
			p->y = a->dr->info;
			Push(s, p);
		}
		else if (a->st && !a->dr) {
			p->x = a->st->info;
			p->y = 0;
			Push(s, p);
		}
	}
}

void AfiPct(void *a) {
	printf("%d %d\n", ((TPunct *)a)->x, ((TPunct *)a)->y);
}

void *afisareNivele2018(TArb a, int niv_min, int niv_max) {
	void *s = InitS(sizeof(TPunct));
	int nivcrt = 0;
	aux4(a, niv_min, niv_max, nivcrt, s);
	return s; 
}

void F2(TArb a)
{
	int i, inaltime=depth(a);
	for (i=0;i<inaltime;i++)
	{
		if (i%2==1)
		{
			afisareNivel(a, i);
		}
	}
}

int nod_div_3(int n)
{
	if (n%3==0)
		return 1;
	return 0;
}

TArb F3(TArb a, TF f)
{
	if (!a) return NULL;
	if (!a->st && !a->dr && f(a->info))
	{
		free(a);
		return NULL;
	}
	a->st=F3(a->st, f);
	a->dr=F3(a->dr, f);
	return a;
}

void F4(TArb a)
{
	if (!a) return;
	F4(a->st);
	F4(a->dr);
	TArb aux;
	aux=a->st;
	a->st=a->dr;
	a->dr=aux;
}

int Max(TArb a)
{
	int m, t1, t2;
	if (!a->st && !a->dr)
		return a->info;
	if (a->st)
	{
		m=Max(a->st);
	}
	if (a->dr)
	{
		if (a->st)
		{
			t2=Max(a->dr);
			if (t2>m)
				m=t2;
		}
		else
			m=Max(a->dr);
	}
	return m;
}

int AxaOx(void *s) {
	int contor = 0;
	void *s_aux = InitS(DIMES(s));
	TPunct *p = (TPunct *)malloc(sizeof(TPunct));
	while (!VIDAS(s)) {
		Pop(s, p);
		if (p->y == 0) { 
			contor++;
		}
		Push(s_aux, p);
	}
	Rastoarna(s, s_aux);
	DistrS(&s_aux, free);
	free(p);
	return contor;
}

void aux2017(TArb a, int *sum, int nivcrt, int *inaltime) {
	if(!a) return;
	sum[nivcrt] += a->info;
	if (nivcrt > *inaltime) {
		*inaltime = nivcrt;
	}
	aux2017(a->st, sum, nivcrt + 1, inaltime);
	aux2017(a->dr, sum, nivcrt + 1, inaltime);
}

int SumaMaximaNivel2017(TArb a, int *sum) {
	int *sums = (int *)calloc(sizeof(int), 100);
	int nivcrt = 0, inaltime = 0, max = -1, nivel;
	aux2017(a, sums, nivcrt, &inaltime);
	for (int i = 0; i <= inaltime; i++) {
		if (sums[i] > max) {
			max = sums[i];
			nivel = i;
			*sum = sums[i];
		}
	}
	printf("%d %d\n", *sum, nivel);
	return nivel;
}

int main ()
{
	 TArb arb, arb_aux;

	  randomize();

    arb = create_ordered_tree(6);
	  printf("____Functia 1________\n");
    AfisareArb(arb);
    printf("Inaltimea arborelui este %d.\n", depth(arb)-1);
    printf("Numarul de frunze este %d.\n", num_of_leafs(arb));
    printf("Numarul de noduri impare = %d.\n", F1(arb, nod_impar));
    printf("%d\n", Max(arb));
    F2(arb);
    arb_aux=F3(arb, nod_div_3);
    AfisareArb(arb_aux);
    AfisareArb(arb);
    F4(arb);
    AfisareArb(arb);
    /* apelati functia de la exercitiul 1 */
    distrugeArb(&arb);

    arb = create_random_tree(8);
		printf("____Functia 2________\n");
    AfisareArb(arb);
    printf("Inaltimea arborelui este %d.\n", depth(arb)-1);
    printf("Numarul de frunze este %d.\n", num_of_leafs(arb));
    printf("Numarul de noduri impare = %d.\n", F1(arb, nod_impar));
    printf("%d\n", Max(arb));
    F2(arb);
    arb_aux=F3(arb, nod_div_3);
    AfisareArb(arb_aux);
    AfisareArb(arb);
    F4(arb);
    AfisareArb(arb);
    /* apelati functia de la exercitiul 2 */
    distrugeArb(&arb);

    arb = create_ordered_tree(18);
		printf("____Functia 3________\n");
    AfisareArb(arb);
    printf("nodurile intre cele 2 nivele:\n");
    void *s = afisareNivele2018(arb, 1, 4);
    AfiS(s, AfiPct, free);
    printf("Puncte pe ox: %d\n", AxaOx(s));
    int sum = 0;
    SumaMaximaNivel2017(arb, &sum);
    printf("Inaltimea arborelui este %d.\n", depth(arb)-1);
    printf("Numarul de frunze este %d.\n", num_of_leafs(arb));
    printf("Numarul de noduri impare = %d.\n", F1(arb, nod_impar));
    F2(arb);
    arb_aux=F3(arb, nod_div_3);
    AfisareArb(arb_aux);
    AfisareArb(arb);
    F4(arb);
    AfisareArb(arb);
    /* apelati functia de la exercitiul 3 */
    distrugeArb(&arb);

	return 0;
}
