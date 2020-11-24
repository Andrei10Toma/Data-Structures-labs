#include "heap.h"

#define NMAX 25
static char desen[20][81], cri[] = "xxx";   /* caractere reprezentare arbore, info */

THeap AlocaHeap(int nMax, TRel rel)
{
	THeap h = (THeap)malloc(sizeof(struct Heap));
	if(!h)
		return NULL;

	h->v = (int*)malloc(nMax * sizeof(int));
	if (!h->v) {
		free(h);
		return NULL;
	}

	h->nMax = nMax;
	h->ne = 0;
	h->rel = rel;

	return h;
}

void DistrugeHeap(THeap *ah)
{
	free((*ah)->v);
	free(*ah);
	*ah = NULL;
}

/**
 * Functie auxiliara pentru desenarea unui arbore cu radacina in centrul liniei
 * dif - distanta pe orizontala intre radacina si cei doi descendenti
 *	Exemple:  dif = 5	|	 dif = 2	|
 *			    xxx				 xxx
 *		    ___/ \___			  / \
 */
void AfiHeapAux(THeap h, int k, int centru, int linie, int dif)
{
	int s, d;

	desen[linie][0] = ':';

	if (dif <= 1) {	 /* spatiu de afisare insuficient -> ... */
		memset (desen[linie] + centru, '.', 3);
		return;
	}

	desen[linie][centru] = '|';	 /* legatura spre radacina */
	sprintf (cri, "%3i", h->v[k]);  /* converteste valoare info la 3 caractere */
	d = (cri[0] == ' ') ? 2 : 1;	/* decalaj fata de centru */
	memcpy(desen[linie + 1] + centru - d, cri, 3);  /* copiaza cele 3 caractere in desen */
	desen[linie + 1][0] = ':';
	desen[linie + 2][0] = ':';

	if ((s = k * 2 + 1) < h->ne) {
		desen[linie + 2][centru - 1] = '/';
		memset(desen[linie + 2] + centru - dif + 1, '_', dif - 2);
		AfiHeapAux(h, s, centru - dif, linie + 3, (dif + 1) / 2 );
	}

	if (s + 1 < h->ne) {
		desen[linie + 2][centru + 1] = '\\';
		memset (desen[linie + 2] + centru + 2, '_', dif - 2);
		AfiHeapAux(h, s + 1, centru + dif, linie + 3, (dif + 1) / 2);
	}
}

/**
 * Afiseaza arborele r in partea superioara a ecranului
 */
void AfiHeap(THeap h, int linie)
{
	int j;
	for (j = 0; j < 20; ++j)
		memset(desen[j], ' ', 79);

 	if (h->ne == 0) {
		printf("\t\t\t\t-=- Arbore VID -=-\n");
	} else {
		printf("\n");
		AfiHeapAux(h, 0, 40, 0, 19);	/* afiseaza incepand de la mijlocul primei linii de pe ecran */

		for (j = 0; j < 16 && desen[j][0] == ':'; ++j) {
			desen[j][79] = '\0';
			printf("%s\n", desen[j] + 1);
		}
	}

	printf("\n");
}

/**
 * Intoarce 1 daca @valParinte < @valCopil, 0 altfel
 */
int RelMinHeap(int valParinte, int valCopil)
{
	return valParinte < valCopil;
}

/**
 * Intoarce 1 daca @valParinte > @valCopil, 0 altfel
 */
int RelMaxHeap(int valParinte, int valCopil)
{
	return valParinte > valCopil;
}

/**
 * Intoarce indicele parintelui pentru nodul @indCopil sau NodInex daca parintele nu exista
 */
int Parinte(THeap h, int indCopil)
{
	// TODO: tema de casa
	return indCopil > 0 ? (indCopil - 1) / 2 : NodInex;
}

/**
 * Intoarce indicele fiului stanga al nodului @indParinte sau NodInex daca fiul nu exista
 */
int FiuStanga(THeap h, int indParinte)
{
	// TODO: tema de casa
	int st = indParinte * 2 + 1;
	return st < h->ne ? st : NodInex;
}

/**
 * Intoarce indicele fiului dreapta al nodului @indParinte sau NodInex daca fiul nu exista
 */
int FiuDreapta(THeap h, int indParinte)
{
	// TODO: tema de casa
	int dr = indParinte * 2 + 2;
	return dr < h->ne ? dr : NodInex;
}

void PropagaSus (THeap h, int nod)
{
	int parent, aux;
	if (nod != 0)
	{
		parent = Parinte(h, nod);
		if (h->v[parent] > h->v[nod])
		{
			aux = h->v[parent];
			h->v[parent] = h->v[nod];
			h->v[nod] = aux;
			PropagaSus(h, parent);
		}
	}
}

void PushHeap(THeap h, int val)
{
	if (h->nMax == h->ne)
		printf("FULL HEAP\n");
	else
	{
		h->ne++;
		h->v[h->ne - 1] = val;
		PropagaSus (h, h->ne - 1);
	}
}

void PropagaJos(THeap h, int nod)
{
	int FiuL, FiuR, FiuMin, aux;
	FiuL=FiuStanga(h, nod);
	FiuR=FiuDreapta(h, nod);
	if (FiuL == -1 && FiuR == -1)
		return;
	if (FiuL == -1 && FiuR != -1)
	{
		if (!h->rel(h->v[nod], h->v[FiuR]))
		{
			aux=h->v[nod];
			h->v[nod]=h->v[FiuR];
			h->v[FiuR]=aux;
		}
		return;
	}
	if (FiuL != -1 && FiuR == -1)
	{
		if (!h->rel(h->v[nod], h->v[FiuL]))
		{
			aux = h->v[nod];
			h->v[nod] = h->v[FiuL];
			h->v[FiuL] = aux;
		}
		return;
	}
	if (FiuL != -1 && FiuR != -1)
	{
		if (h->v[FiuL] >= h->v[FiuR])
			FiuMin = FiuR;
		else
			FiuMin = FiuL;
		if (h->v[FiuMin] < h->v[nod])	
		{
			aux = h->v[nod];
			h->v[nod] = h->v[FiuMin];
			h->v[FiuMin] = aux;
			PropagaJos(h, FiuMin);
		}
		else
			return;
	}
}

int PopHeap (THeap h)
{
	if (h->ne == 0)
		return -1;
	int ex = h->v[0];
	h->v[0]=h->v[h->ne-1];
	h->ne=h->ne-1;
	if (h->ne > 0)
		PropagaJos(h, 0);
	return ex;
}

void MakeHeap(THeap h)
{
	int middle = h->ne / 2, nod;
	for (nod = middle; nod >= 0; nod--)
		PropagaJos(h, nod);
}

void HeapSort(int *v, int nv, TRel rel)
{
	int i;
	THeap h = AlocaHeap(nv, rel);
	for (i = 0; i < nv; i++)
		PushHeap(h, v[i]);
	for (i = 0; i < nv; i++)
		v[i] = PopHeap(h);
	DistrugeHeap(&h);
}

int countNodes(TArb a)
{
	if (!a)
		return 0;
	return (1 + countNodes(a->st) + countNodes(a->dr));
}

int isComplete(TArb a, int ind, int nodes)
{
	if (!a)
		return 1;
	if (ind >= nodes)
		return 0;
	return(isComplete(a->st, 2 * ind + 1, nodes) && isComplete(a->dr,
		2 * ind + 2, nodes));
}

int isHeap(TArb a)
{
	if (a->st == NULL && a->dr == NULL)
		return 1;
	if (a->dr == NULL)
		return (a->info >= a->st->info);
	else
	{
		if (a->info >= a->st->info && a->info >= a->dr->info)
			return (isHeap(a->st) && isHeap(a->dr));
		else
			return 0;
	}
}

int main()
{
	THeap h;
	int testv[] = {8, 7, 9, 10, 6, 5, 11, 4, 12, 3, 13, 14, 2, 1, 15},
		nv = sizeof(testv) / sizeof(testv[0]), i;

	h = AlocaHeap(NMAX, RelMinHeap);
	if (!h)
		return 1;

    // Demo structura min-heap
	int heapv[] = {2, 5, 3, 11, 9, 13, 8},
		nh = sizeof(heapv) / sizeof(heapv[0]);
	printf("Demo structura de tip min-heap:\n");
	for (i = 0; i < nh; ++i)
		h->v[h->ne++] = heapv[i];
	AfiHeap(h, 13);
	h->ne = 0;

	// Testeaza PushHeap
	for (i = 0; i < nv; i++)
		PushHeap(h, testv[i]);
	printf("Heap dupa crearea folosind PushHeap:\n");
	AfiHeap(h, 13);

	// Testeaza PopHeap
	printf("Elementele extrase cu PopHeap sunt: \n");
	for (i = 0; i < nv; i++)
		printf("%d ", PopHeap(h));
	printf("\n");
	printf("Heap vid dupa eliminarea folosind PopHeap\n");
	AfiHeap(h, 13);

	// Testeaza MakeHeap
	for (i = 0; i < nv; i++)
		h->v[h->ne++] = testv[i];
	MakeHeap(h);
	printf("Head dupa operatia de MakeHeap:\n");
	AfiHeap(h, 13);

	// Testeaza HeapSort
	HeapSort(testv, nv, RelMinHeap);
	printf("Vector sortat crescator folosind HeapSort: \n");
	for (i = 0; i < nv; i++)
		printf("%d ", testv[i]);
	printf("\n");

	// Testare Bonus
	TArb arb;
	randomize();
	arb = create_ABC(8);
	AfisareArb(arb);
	if (isHeap(arb) && isComplete(arb, 0, countNodes(arb)))
		printf("Arborele este heap.\n");
	else
		printf("Arborele nu este heap.\n");
	DistrugeHeap(&h);
	distrugeArb(&arb);
	return 0;
}
