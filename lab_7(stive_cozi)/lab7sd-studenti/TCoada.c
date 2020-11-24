#include "TCoada.h"
#include "TStiva.h"

/* FUNCTII COADA */


/* initiaza coada goala -> coada goala */
TCoada InitQ() {
	TCoada new = (TCoada)malloc(sizeof(TElem));
	if (!new) return NULL;
	*new = NULL;

	return new;
}

/* adauga elemtul x la sfarsitul cozii */
void Enqueue(TCoada q, void *x) {
	TElem new = (TElem)malloc(sizeof(TCelula));
	if (!new) return;
	new->info = x;
	new->urm = NULL;

	if(Vida(q)) {
		*q = new;
		return;
	}

	TElem aux = *q;

	while(aux->urm != NULL)
		aux = aux->urm;

	aux->urm = new;
}

/* scoate un element din varful cozii -> referinta catre continutul elementului eliminat */
void *Dequeue(TCoada q) {
	if(Vida(q))
		return NULL;
	
	void *result = (*q)->info;
	TElem aux = *q;
	*q = (*q)->urm;
	free(aux);

	return result;
}

/* -> referinta catre continutul elementului din varful cozii */
void *Peek(TCoada q) {
	if (Vida(q))
		return NULL;
	
	return (*q)->info;
}

/* muta din source in dest un element */
void MutaQ(TCoada dest, TCoada source) {
	Enqueue(dest, Dequeue(source));
}

/* -> numarul de elemente din stiva */
int NrEQ(TCoada q) {
	TCoada aux = InitQ();
	int count = 0;

	while (!Vida(q)) {
		MutaQ(aux, q);
		count++;
	}

	while(!Vida(aux))
		MutaQ(q, aux);

	return count;	
}

void ConcatQ(TCoada dest, TCoada source) {
	while(!Vida(source))
		MutaQ(dest, source);
}

/* afiseaza elementele stivei fara a itera prin structura */
void AfisareQ(TCoada q, void (*afiEl)(void *)) {
	TCoada aux = InitQ();

	printf("[");
	while (!Vida(q)) {
		void *elm = Dequeue(q);
		afiEl(elm);
		if (!Vida(q))
			printf(", ");
		Enqueue(aux, elm);
	}
	printf("]\n");

	while(!Vida(aux)) {
		Enqueue(q, Dequeue(aux));
	}

	DistrQ(aux);
}

void DistrQ(TCoada q) {
	while (!Vida(q))
		free(Dequeue(q));

	free(q);
	q = NULL;
}

//Tema de casa
void InverseazaQ(TCoada q) {}

/* TODO BONUS -> sortare coada*/
void SortareQ(TCoada q, TFCmp cmp) {}
