#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#ifndef ARBORE_BINAR
#define ARBORE_BINAR

typedef int (*TF)(int);

typedef struct node{
    int info;
    struct node *st;
    struct node *dr;
}TNod, *TArb;

int insertABC(TArb* a, int num);
TArb create_ABC(int num);
TArb create_leaf(int x);
void distruge(TArb r);
void distrugeArb(TArb *a);

#ifndef _random_
#define _random_
#define random(n) (rand() % (n))
#define randomize() (srand((unsigned int)time(NULL)))
#endif
#endif
