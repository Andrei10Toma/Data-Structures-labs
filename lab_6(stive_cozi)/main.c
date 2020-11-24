#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TCoada.h"
#include "TStiva.h"

/* numar maxim elemente coada / stiva */
#define MAX 256 

typedef struct
{ 
	int x, y;
} TPct;

typedef struct 
{
  int id, varsta;
}TPers;

typedef struct 
{
  int id, diametru;
}TDisc;

int GenereazaCoadaPct(void* c, size_t N, int v1, int v2)
{ 
  	int n = 0;
  	TPct p;

  	srand(time(NULL));
  	for(; N > 0; N--)
  	{
    	p.x = rand() % (v2-v1+1) + v1; 
    	p.y = rand() % (v2-v1+1) + v1;
  
		if (!IntrQ(c, &p)) 
			return n;
		n++;
  	}
  	return n;
}

int GenereazaCoadaPers(void* c, size_t N, int v1, int v2)
{ 
    int n = 0;
    TPers p;

    srand(time(NULL));
    for(; N > 0; N--)
    {
      p.id = rand() % (v2-v1+1) + v1; 
      p.varsta = rand() % (v2-v1+1) + v1;
  
    if (!IntrQ(c, &p)) 
      return n;
    n++;
    }
    return n;
}

int GenereazaCoadaDisc(void* c, size_t N, int v1, int v2)
{ 
    int n = 0;
    TDisc p;

    srand(time(NULL));
    for(; N > 0; N--)
    {
      p.id = rand() % (v2-v1+1) + v1; 
      p.diametru = rand() % (v2-v1+1) + v1;
  
    if (!IntrQ(c, &p)) 
      return n;
    n++;
    }
    return n;
}

int peAxa(void *pct)
{
  if (((TPct*)pct)->x * ((TPct*)pct)->y == 0)
    return 1;
  return 0;
}

int varstaPara (void *pers)
{
  if (((TPers*)pers)->varsta % 2==0)
    return 1;
  return 0;
}

int diametruImpar (void *disc)
{
  if (((TDisc *)disc)->diametru % 2==1)
    return 1;
  return 0;
}

int varstaMV(void *pers)
{
  if (((TPers*)pers)->varsta < 25)
    return 1;
  return 0;
}

int diametrumd(void *disc)
{
  if (((TDisc*)disc)->diametru < 50)
    return 1;
  return 0;
}

int GenereazaStivaPct(void* c, size_t N, int v1, int v2)
{ 
	int n = 0;
  	TPct p;

  	srand(time(NULL));
  	for(; N > 0; N--)
  	{
    	p.x = rand() % (v2-v1+1) + v1; 
    	p.y = rand() % (v2-v1+1) + v1;
  
		if (!Push(c, &p)) 
			return n;
		n++;
  	}
  	return n;
}

int GenereazaStivaPers(void* c, size_t N, int v1, int v2)
{ 
  int n = 0;
    TPers p;

    srand(time(NULL));
    for(; N > 0; N--)
    {
      p.id = rand() % (v2-v1+1) + v1; 
      p.varsta = rand() % (v2-v1+1) + v1;
  
    if (!Push(c, &p)) 
      return n;
    n++;
    }
    return n;
}

int GenereazaStivaDisc(void* c, size_t N, int v1, int v2)
{ 
  int n = 0;
    TDisc p;

    srand(time(NULL));
    for(; N > 0; N--)
    {
      p.id = rand() % (v2-v1+1) + v1; 
      p.diametru = rand() % (v2-v1+1) + v1;
  
    if (!Push(c, &p)) 
      return n;
    n++;
    }
    return n;
}

/* afiseaza coada */
void AfiQ(char antet[], TF1 AfiElem, void *a)
{ 
	/* afiseaza antet si apoi aplica functia de afisare AfiElem tuturor elementelor */
	printf ("%s", antet);          	/* afiseaza antetul */
  	if (VidaQ (a))
      printf ("Coada vida!");
  	else
      PrelQ (a, AfiElem);       	/* afiseaza elementele in ordinea introducerii */
  	printf("\n");
}

/* afiseaza stiva */
void AfiS(char antet[], TF1 AfiElem, void *a) 
{
	/* afiseaza antet si apoi aplica functia de afisare AfiElem tuturor elementelor */ 
	printf ("%s", antet);          /* afiseaza antetul */
	if (VidaS (a))
    	printf ("Stiva vida!");
  	else
      	Prel_B_V (a, AfiElem);       /* afiseaza elementele in ordinea introducerii */
  	printf("\n");
}

int AfiPct(void *a)
{ 
	printf("[%d %d] ", (*(TPct*)a).x, (*(TPct*)a).y); 
	return 1;
}

int AfiPers(void *a)
{ 
  printf("[%d %d] ", (*(TPers*)a).id, (*(TPers*)a).varsta); 
  return 1;
}

int AfiDisc(void *a)
{ 
  printf("[%d %d] ", (*(TDisc*)a).id, (*(TDisc*)a).diametru); 
  return 1;
}

void *Copie (void *s)
{
  void *c=InitQ(DimES(s), MAX);
  void *sTemp=InitS(DimES(s), MAX);
  void *el=malloc(DimES(s));
  while (!VidaS(s))
  {
    Pop(s, el);
    IntrQ(c, el);
    Push(sTemp, el);
  }
  Rastoarna(s, sTemp);
  free(el);
  DistrS(&sTemp);
  return c;
}

double FC (void *c, int (*fcond)(void *))
{
  int nrElem=0, nrCond=0;
  void *qTemp = InitQ(DimEQ(c), MAX);
  void *el=malloc(DimEQ(c));
  while (!VidaQ(c))
  {
    ExtrQ(c, el);
    if (fcond(el))
      nrCond++;
    nrElem++;
    IntrQ(qTemp, el);
  }
  ConcatQ(c, qTemp);
  if (nrElem==0)
    return -1;
  return ((double)nrCond)/nrElem*100;
}

float FC1 (void *c, int (*fcond)(void *))
{
  int nrElem=0, nrCond=0;
  void *qTemp = InitQ(DimEQ(c), MAX);
  void *el=malloc(DimEQ(c));
  while (!VidaQ(c))
  {
    ExtrQ(c, el);
    if (fcond(el)==1)
      nrCond++;
    nrElem++;
    IntrQ(qTemp, el);
  }
  ConcatQ(c, qTemp);
  if (nrElem==0)
    return -1;
  return ((double)nrCond)/nrElem*100;
}

float FS1 (void *s, int (*fcond)(void *))
{
  int nrElem=0, nrCond=0;
  void *sTemp=InitS(DimES(s), MAX);
  void *el=malloc(DimES(s));
  while (!VidaS(s))
  {
    Pop(s, el);
    if (fcond(el)==1)
      nrCond++;
    nrElem++;
    Push(sTemp, el);
  }
  Rastoarna(s, sTemp);
  if (nrElem==0)
    return -1;
  return ((double)nrCond)/nrElem*100;
}

void FC2 (void *c, int (*f)(void *))
{
  void *qTemp1 = InitQ(DimEQ(c), MAX);
  void *qTemp2 = InitQ(DimEQ(c), MAX);
  void *el=malloc(DimEQ(c));
  while (!VidaQ(c))
  {
    ExtrQ(c, el);
    if (f(el)==1)
      IntrQ(qTemp1, el);
    else
      IntrQ(qTemp2, el);
  }
  if (VidaQ(qTemp1))
  {
    ConcatQ(c, qTemp2);
    DistrQ(&qTemp1);
    DistrQ(&qTemp2);
  }
  else
  {
    ConcatQ(c, qTemp2);
    DistrQ(&qTemp1);
    DistrQ(&qTemp2);
  }
}

void FS2 (void *s, int (*f)(void *))
{
  void *sTemp1 = InitS(DimES(s), MAX), *sTemp2 = InitS(DimES(s), MAX);
  void *el=malloc(DimES(s));
  while (!VidaS(s))
  {
    Pop(s, el);
    if (f(el)==1)
      Push(sTemp1, el);
    else
      Push(sTemp2, el);
  }
  if (VidaS(sTemp1))
  {
    Rastoarna(s, sTemp2);
    DistrS(&sTemp1);
    DistrS(&sTemp2);
  }
  else
  {
    Rastoarna(s, sTemp2);
    DistrS(&sTemp1);
    DistrS(&sTemp2);
  }
}

void FC3(void *c, void **c1, void **c2, int (*f)(void *))
{
  void *qTemp1=InitQ(DimEQ(c), MAX);
  void *el=malloc(DimEQ(c));
  while (!VidaQ(c))
  {
    ExtrQ(c, el);
    if (f(el)==1)
      IntrQ(*c1, el);
    else
      IntrQ(*c2, el);
    IntrQ(qTemp1, el);
  }
  ConcatQ(c, qTemp1);
  DistrQ(&qTemp1);
}

void FS3(void *s, void **s1, void **s2, int (*f)(void *))
{
  void *sTemp1=InitS(DimES(s), MAX);
  void *el=malloc(DimES(s));
  while (!VidaS(s))
  {
    Pop(s, el);
    if (f(el)==1)
      Push(*s1, el);
    else
      Push(*s2, el);
    Push(sTemp1, el);
  }
  InvS(*s1);
  InvS(*s2);
  Rastoarna(s, sTemp1);
  DistrS(&sTemp1);
}

int main()
{ 
	void *c, *s, *cs, *cc, *ss;
  	int lgc, lgs;

  	c = InitQ(sizeof(TPct),MAX);
	if (!c) 
		return 1;

  	s = InitS(sizeof(TPct),MAX);
	if (!s) 
	{
		DistrQ(&c); 
		return 1;
	}

  	lgc = GenereazaCoadaPct(c, 8, -5, 5);
  	lgs = GenereazaStivaPct(s, 6, 8, 14);
	printf("\nCoada cu %d elemente\n", lgc);
  	AfiQ("Elemente coada:\n", AfiPct, c);
  	printf("\n\nStiva cu %d elemente\n", lgs);
   	AfiS("Elemente stiva (baza -> varf):\n", AfiPct, s);
 	/* apeluri functii */
    cs=Copie(s);
    AfiQ("\ncoada copiata:\n", AfiPct, cs);
    AfiS("Stiva originala\n", AfiPct, s);
    TPct x;
    ExtrQ(cs, &x);
    AfiPct(&x);

    double procent = FC(c, peAxa);
    printf("procentul calculat este %lf\n", procent);
    AfiQ("coada: \n", AfiPct, c);
    printf("\n");
    cc=InitQ(sizeof(TPers), MAX);
    GenereazaCoadaPers(cc, 5, 0, 100);
    AfiQ("\nEx.1:", AfiPers, cc);
    printf("FC1: %.2f\n", FC1(cc, varstaPara));
    AfiQ("\nCoada originala: ", AfiPers, cc);
    DistrQ(&cc);

    printf("\n");
    ss=InitS(sizeof(TDisc), MAX);
    GenereazaStivaDisc(ss, 5, 0, 100);
    AfiS("\nEx.1:", AfiDisc, ss);
    printf("FS1: %.2f\n", FS1(ss, diametruImpar));
    AfiS("\nStiva originala: ", AfiDisc, ss);
    DistrS(&ss);

    printf("\n");
    cc=InitQ(sizeof(TPers), MAX);
    GenereazaCoadaPers(cc, 5, 0, 100);
    AfiQ("\nEx.2:", AfiPers, cc);
    FC2(cc, varstaMV);
    AfiQ("\nEx.2:", AfiPers, cc);
    DistrQ(&cc);

    printf("\n");
    ss=InitS(sizeof(TDisc), MAX);
    GenereazaStivaDisc(ss, 5, 0, 100);
    AfiS("\nEx.2:", AfiDisc, ss);
    FS2(ss, diametrumd);
    AfiS("\nEx.2:", AfiDisc, ss);
    DistrS(&ss);

    printf("\n");
    void *c1=InitQ(sizeof(TPers), MAX), *c2=InitQ(sizeof(TPers), MAX);
    cc=InitQ(sizeof(TPers), MAX);
    GenereazaCoadaPers(cc, 5, 0, 100);
    AfiQ("\nEx.3:", AfiPers, cc);
    FC3(cc, &c1, &c2,varstaPara);
    AfiQ("\nc1:", AfiPers, c1);
    AfiQ("\nc2:", AfiPers, c2);
    AfiQ("\nCoada originala:", AfiPers, cc);
    DistrQ(&cc);
    DistrQ(&c1);
    DistrQ(&c2);

    printf("\n");
    void *s1=InitS(sizeof(TDisc), MAX), *s2=InitS(sizeof(TDisc), MAX);
    ss=InitS(sizeof(TDisc), MAX);
    GenereazaStivaDisc(ss, 5, 0, 100);
    AfiS("\nEx.3:", AfiDisc, ss);
    FS3(ss, &s1, &s2, diametruImpar);
    AfiS("\ns1:", AfiDisc, s1);
    AfiS("\ns2:", AfiDisc, s2);
    AfiS("\nStiva originala:", AfiDisc, ss);
    DistrS(&ss);
    DistrS(&s1);
    DistrS(&s2);

    DistrS(&s);
  	DistrQ(&c);
  	return 0;
}
