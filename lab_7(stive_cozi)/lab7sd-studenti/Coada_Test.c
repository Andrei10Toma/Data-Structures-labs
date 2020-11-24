#include "TCoada.h"
#include "utils.h"


void afisInt(void* a) {
	printf("%d", *(int*)a);
}

int cmpInt(void *a, void *b) {
	return *(int*)a - *(int*)b;
}

/* TODO EX 2 A */
void MarkIsland(Coordinate pos, int value) {
	
}

/* parcurge harta si in cazul in care intalneste o insula o marcheaza */
void NumberOfIslands() {
	int i, j;
	int count = 0;
	Coordinate pos;

	printf("Searching for islands...\n\n");

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if(map[i][j] == P) {
				count++;
				pos.x = i;
				pos.y = j;
				MarkIsland(pos, count);
			}
		}
	}

	printf("Found %d islands\n\n", count);
}

int InMatrix(int x, int y) {
    if(x < 0) 
        return 0;
    if(y < 0)
        return 0;
    if(x >= N)
        return 0;
    if(y >= N)
        return 0;
    return 1;
}

/* TODO EX 2 B */
void FloodFill(Coordinate pos, int new_color) 
{
	TCoada c=InitQ();
	if (map[pos.x][pos.y]==P)
		printf("NU SE POATE\n");
	else
	{
		Coordinate *position=(Coordinate *)malloc(sizeof(Coordinate));
		*position=pos;
		map[pos.x][pos.y]=new_color;
		Enqueue(c, position);
		while (!Vida(c))
		{
			void *m;
			m=Dequeue(c);
			int x_poz=((Coordinate*) m)->x;
			int y_poz=((Coordinate*) m)->y;
			map[x_poz][y_poz]=new_color;
			/*printf("%d %d\n", x_poz, y_poz);*/
			for (int i=0;i<3;i++)
			{
				for (int j=0;j<3;j++)
				{
					if (InMatrix(x_poz+dirX[i], y_poz+dirY[j]) && 
						map[x_poz+dirX[i]][y_poz+dirY[j]]==0)
					{
						Coordinate *p=(Coordinate *)malloc(sizeof(Coordinate));
						p->x=x_poz+dirX[i];
						p->y=y_poz+dirY[j];
						map[p->x][p->y]=new_color;
						Enqueue(c, p);
					}
				}
			}
		}
	}
}

/*
	apeleaza FloodFill pornind de la un punct aleator si
	folosind o culoare aleatoare
*/
void RandomFloodFill() {
	Coordinate pos;
	pos.x = rand() % N;
	pos.y = rand() % N;
	int value = rand() % 9 + 1;

	printf("Coloring from point (%d,%d) with color %d\n\n", pos.x, pos.y, value);
	FloodFill(pos, value);
}

/* TODO EX 2 C */
void SolveLabyrinth(Coordinate start, Coordinate finish) {
	
}

/* apeleaza SolveLabyrinth cu coordonate aleatoare */
void RandomLabyrinth() {
	Coordinate start;
	start.x = rand() % N;
	start.y = rand() % N;

	while(map[start.x][start.y] != 0) {
		start.x = rand() % N;
		start.y = rand() % N;
	}
	
	Coordinate finish;
	finish.x = rand() % N;
	finish.y = rand() % N;

	while(map[finish.x][finish.y] != 0) {
		finish.x = rand() % N;
		finish.y = rand() % N;
	}

	printf("Searching a way from point (%d,%d) to point (%d,%d)\n\n", start.x, start.y, finish.x, finish.y);
	SolveLabyrinth(start, finish);
}

int main() {
	/* exemplu utilizare functii pe coada */
	TCoada q = InitQ();
	int vec[5] = {2,3,1,5,4};
	int *x;

	for (int i = 0; i < 5; i++) {
		/* elementele puse in coada trebuie alocate pe heap */
		x = malloc(sizeof(int));
		*x = vec[i];
		Enqueue(q, x);
	}

	AfisareQ(q, afisInt);
		
	afisInt(Peek(q));		// print 2
	printf(" PEEK\n");
	afisInt(Dequeue(q));	// print 2
	printf(" DEQUEUE\n");
	afisInt(Peek(q));		// print 3 (noul varf)
	printf(" NEW PEEK\n");

	SortareQ(q, cmpInt);	// merge doar daca a fost implementata
	AfisareQ(q, afisInt);
	DistrQ(q);

	srand(time(NULL));
	printf("Initial map:\n\n");
	PrintMap();

	/* apeluri functii de prelucrare harta */

	ResetMap();
	RandomFloodFill();
	PrintMap();

	return 1;
}