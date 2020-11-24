#include "lista2.h"

void AfiInt(void * ax)
{
	printf("%d ", *(int*)ax);
}

void AfiPunct(void *ax) {
	printf("(%d %d) ", ((TPunct *)ax)->x, ((TPunct *)ax)->y);
}

int fCresc(void *x, void *y)
{
	int a=*(int *)x;
	int b=*(int *)y;
	if (a>b)
		return 1;
	else
		return 0;
}

int fDescresc(void *x, void *y)
{
	int a=*(int *)x;
	int b=*(int *)y;
	if (a>b)
		return 0;
	else
		return 1;
}

void CitireLDI(TLDI s, int* lg)
{
	int *ax, x;
 	char ch;

  	printf("se citesc valori numerice, terminate cu caracter nenumeric\n");
	for(*lg = 0; scanf("%i", &x) == 1; )
  	{
        ax = (int*)malloc(sizeof(int));
		if(!ax) return;
	 	*ax = x;
		InsDupa(s->pre, ax);
    		(*lg)++;
  	}
  	while((ch=getchar()) != EOF && ch != '\n');
}

void CitireLDIPunct(TLDI s, int* lg)
{
	TPunct *ax; 
	int x, y;
 	char ch;

  	printf("se citesc valori puncte, terminate cu caracter nenumeric\n");
	for(*lg = 0; scanf("%i", &x) == 1 && scanf("%i", &y) == 1; )
  	{
        ax = (TPunct*)malloc(sizeof(TPunct));
		if(!ax) return;
	 	ax->x = x;
	 	ax->y = y;
		InsDupa(s->pre, ax);
    		(*lg)++;
  	}
  	while((ch=getchar()) != EOF && ch != '\n');
}

int Lungimea(TLDI s)
{
	TLDI p;
	int length=0;
	for (p=s->urm;p!=s;p=p->urm)
		length++;
	return length;
}

TLDI Construire(TLDI s)
{
	int length, contor=0;
	length=Lungimea(s);
	TLDI p=s, s1;
	s1=InitLDI();
	printf("%d\n", length);
	while (contor<=length/2)
	{
		p=p->urm;
		contor++;
	}
	printf("%d\n", *(int *)p->info);
	TLDI p_aux=p;
	for (p_aux=p;p_aux!=s;p_aux=p_aux->urm)
	{
		int x=*(int *)p_aux->info;
		if (x%2==1)
			InsDupa(s1->pre, p_aux->info);
	}
	return s1;
}

void EliminaM(TLDI s, int n)
{
	int length, contor=0;
	length=Lungimea(s);
	TLDI p=s, s1;
	while (contor<=length/2)
	{
		p=p->urm;
		contor++;
	}
	for (;p!=s;p=p->urm)
	{
		int x=*(int *)p->info;
		if (x<n)
		{
			TLDI aux=p;
			p->pre->urm=p->urm;
			p->urm->pre=p->pre;
			free(aux->info);
			free(aux);
		}
	}
}

TLDI InserareOrdonata(int (*f)(void *, void *), int n)
{
	TLDI s=NULL, p;
	s=InitLDI();
	int i, x, *xp;
	for (i=0;i<n;i++)
	{
		scanf("%d", &x);
		int *xp=(int *)malloc(sizeof(int));
		*xp=x;
		for (p=s->urm;p!=s;p=p->urm)
			if (f(xp, p->info)==0)
			{
				InsDupa(p->pre, xp);
				break;
			}
		if (s==p)
			InsDupa(s->pre, xp);
	}
	return s;
}

void StergeSecventaComuna(TLDI s1, TLDI s2, int *contor) {
	TLDI p1, p2, aux1, aux2;
	int ok = 1;
	for (p1 = s1->urm; p1 != s1; p1 = p1->urm) {
		for (p2 = s2->urm; p2 != s2; p2 = p2->urm) {
			if (*(int *)p1->info == *(int *)p2->info) {
				while (*(int *)p1->info == *(int  *)p2->info) {
					(*contor)++;
					aux1 = p1;
					p1->pre->urm = p1->urm;
					p1->urm->pre = p1->pre;
					free(aux1);
					aux2 = p2;
					p2->pre->urm = p2->urm;
					p2->urm->pre = p2->pre;
					free(aux2);
					if (p1->urm == s1 || p2->urm == s2) {
						ok = 0;
						break;
					}
					p1 = p1->urm;
					p2 = p2->urm;
				}
				ok = 0;
				break;
			}
		}
		if (ok == 0) {
			break;
		}
	}
}

TLG Aloca_Cel(TLDI s) {
	TLG cel;
	cel = (TLG)malloc(sizeof(TCelulaG));
	cel->urm = NULL;
	cel->info = s->info;
	return cel;
}

int Adauga_Lista_Gen(TLG *l, TLDI s) {
	TLG p, ultim;
	TLG cel = Aloca_Cel(s);
	for (p = *l, ultim = NULL; p != NULL; ultim = p, p = p->urm) {
		if (((TPunct *)p->info)->x > ((TPunct *)cel->info)->x)
			break;
	}
	if (p)
	printf("celula: %d\n", ((TPunct *)p->info)->x);
	if (ultim == NULL && *l == NULL) {
		*l = cel;
	}
	else if (p == NULL) {
		ultim->urm = cel;
	}
	else {
		cel->urm = *l;
		*l = cel;
	}
	return 1;
}

TLG Copie_Lista_2015(TLDI s) {
	TLDI p;
	TLG rezultat = NULL;
	for (p = s->urm; p != s; p = p->urm) {
		if (p->urm != s && p->pre != s) {
			if (((TPunct*)p->info)->x * ((TPunct*)p->urm->info)->x >= 0 && ((TPunct*)p->info)->y * ((TPunct*)p->urm->info)->y >= 0 
				|| ((TPunct*)p->info)->x * ((TPunct*)p->pre->info)->x >= 0 && ((TPunct*)p->info)->y * ((TPunct*)p->pre->info)->y >= 0) {
				Adauga_Lista_Gen(&rezultat, p);
			}
		}
		if (p->urm == s && p->pre != s) {
			if (((TPunct*)p->info)->x * ((TPunct*)p->pre->info)->x >= 0 && ((TPunct*)p->info)->y * ((TPunct*)p->pre->info)->y >= 0) {
				Adauga_Lista_Gen(&rezultat, p);
			}
		}
		if (p->urm != s && p->pre == s) {
			if (((TPunct*)p->info)->x * ((TPunct*)p->urm->info)->x >= 0 && ((TPunct*)p->info)->y * ((TPunct*)p->urm->info)->y >= 0) {
				Adauga_Lista_Gen(&rezultat, p);
			}
		}
	}
	return rezultat;
}

int CmpPar(void *x) {
	if (*(int *)x % 2 == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

TLG AlocaCel(TLDI s) {
	TLG cel;
	cel = (TLG)malloc(sizeof(TCelulaG));
	cel->urm = NULL;
	cel->info = s;
}

int Adaugare(TLG *l, TLDI s) {
	TLG p, ultim;
	TLG cel = AlocaCel(s);
	for (p = *l, ultim = NULL; p != NULL; ultim = p, p = p->urm);
	if (ultim == NULL) {
		*l = cel;
	}
	else {
		ultim->urm = cel;
	}
}

TLG Mutare(TLDI s, int (*f)(void *)) {
	TLG rezultat = NULL, ultim, pg;
	TLDI p, aux;
	for (p = s->urm; p != s; p = p->urm) {
		if (f(p->info) == 1) {
			p->pre->urm = p->urm;
			p->urm->pre = p->pre;
			Adaugare(&rezultat, p);
		}
	}
	return rezultat;
}

void AfiEl(void *x) {
	TLDI a = x;
	printf("%d ", *(int *)a->info);
}

TLG Construire_Lista_Generica(TLDI s) {
	TLG rezultat = NULL;
	TLDI pa = s->urm, pb = pa->urm, aux;
	while (pa != s && pb != s) {
		if (*(int *)pa->info < *(int *)pb->info) {
			pa->pre->urm = pb;
			pb->pre = pa->pre;
			pa->pre = pb;
			pa->urm = pb->urm;
			pb->urm->pre = pa;
			pb->urm = pa;
		}
		pa = pa->urm;
		pb = pa->urm;
	}
	return rezultat;
}

int main()
{
	TLDI s, s1=InitLDI(), s2;
	int lg, n;
	TLG rezultat = NULL;

	for(; ; )
	{
		s = InitLDI();
		s2 = InitLDI();
		CitireLDI(s, &lg);
		//CitireLDI(s2, &lg);
		//AfisareLDI(s, AfiPunct);
		//rezultat = Copie_Lista_2015(s);
		//AfisareLDI(s, AfiPunct);
		//Afisare(&rezultat, AfiPunct);
		//rezultat = Mutare(s, CmpPar);
		AfisareLDI(s, AfiInt);
		rezultat = Construire_Lista_Generica(s);
		AfisareLDI(s, AfiInt);
		//Afisare(&rezultat, AfiEl);
		//AfisareLDI(s2, AfiInt);
		//StergeSecventaComuna(s, s2, &n);
		//printf("%d\n", n);
		//AfisareLDI(s, AfiInt);
		//AfisareLDI(s2, AfiInt);
		/* apeluri functii */
		//s1=Construire(s);
		//AfisareLDI(s1, AfiInt);
		//AfisareLDI(s, AfiInt);
		//scanf("%d", &n);
		//EliminaM(s, n);
		//AfisareLDI(s, AfiInt);
		//TLDI s2=InserareOrdonata(fDescresc, 10);
		//AfisareLDI(s2, AfiInt);
		DistrLDI(&s);
		printf ("\n  Inca un test ? [d/n]");
		if (getchar() == 'n') break;
	}
    return 0;
}
