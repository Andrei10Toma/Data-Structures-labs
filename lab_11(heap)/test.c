#include "TArb.h"

static char desen[30][81], cri[] = "xxx";  /* zona reprezentare arbore, info */
static int limita = 30;                    /* linia limita de desenare */

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

void aux(TArb a, int x, int y, int *prod)
{
	if (!a) return;
	if (a->info>=x && a->info<=y)
		(*prod)=(*prod)*a->info;
	aux(a->st, x, y, prod);
	aux(a->dr, x, y, prod);
}

int ProdArb(TArb a, int x, int y)
{
	int prod=1;
	if (!a) return 1;
	aux(a, x, y, &prod);
	return prod;
}

TArb *CautaArb(TArb *a, int val)
{
	while (*a)
	{
		if ((*a)->info==val)
			return a;
		if (val < (*a)->info)
			a=&((*a)->st);
		else
			a=&((*a)->dr);
	}
	return NULL;
}

int checkLevelAux (TArb a, int niv, int *niv_found)
{
	if (!a) return 1;
	if (a->info%2==1)
	{
		if ((*niv_found)==-1)
			*niv_found=niv;
		else if ((*niv_found)!=niv)
			return 0;
	}
	return checkLevelAux(a->st, niv+1, niv_found) &&
			checkLevelAux(a->dr, niv+1, niv_found);
}

int checkLevel(TArb a)
{
	int niv=0, niv_found=-1;
	return checkLevelAux(a, niv, &niv_found);
}

int insertABC_me(TArb* a, int x)
{
	while (*a)
	{ 
		if ( x <= (*a)->info)
			a = &((*a)->st);
		else
			a = &((*a)->dr);
	}
	*a = create_leaf(x);
	if(!*a) return 0;
	return 1;
}

TArb constructBalancedABC(int *v, int n)
{
	TArb rezultat;
	int mid_v=v[n/2], i;
	TArb rad=create_leaf(mid_v);
	rezultat=rad;
	for (i=0;i<n;i++)
	{
		if (i!=n/2)
			insertABC_me(&rezultat, v[i]);
	}
	return rezultat;
}
