#include "TStiva.h"

void afisInt(void* a) {
	printf("%d", *(int*)a);
}

int cmpInt(void *a, void *b) {
	return *(int*)a - *(int*)b;
}

/* returneaza prioritatea simbolului */
int getPriority(char symbol) {

	switch (symbol) {
		case '/':
		case '*':
			return 2;

		case '+':
		case '-':
			return 1;

		default:
			return 0;
	}
}

/*
	returneaza stringul "<operand1> <op> <operand2>"
	ajuta la generarea unei forme infixate
 */
char *SmartConcatInfix(char *operand1, char *op, char *operand2) {
	char *result = (char *)calloc(strlen(operand1) +
					  	strlen(operand2) + strlen(op) + 4,
				      	sizeof(char));
	
	strcat(result, operand1);
	strcat(result, " ");
	strcat(result, op);
	strcat(result, " ");
	strcat(result, operand2);
/*
	free(operand1);
	free(operand2);
	free(op);*/

	return result;
}

/*
	returneaza stringul "<equation> <op>"
	ajuta la generarea unei forme postfixate
 */
void SmartConcatPostfix(char *equation, char *op) {
	strcat(equation, op);
	strcat(equation, " ");
	free(op);
}

char *PostfixToInfix (char *equation)
{
	TStiva s=InitS();
	char *result=(char *)malloc(30);
	for (int i=0;i<strlen(equation);i+=2)
	{
		if (equation[i]>='a' && equation[i]<='z')
		{
			char *x=malloc(sizeof(char));
			*x=equation[i];
			Push(s, x);
		}
		else if (getPriority(equation[i])==1 || getPriority(equation[i])==2)
		{
			void *x1=NULL;
			void *x2=NULL;
			x1=Pop(s);
			x2=Pop(s);
			char *rel=(char *)malloc(2*sizeof(char));
			memset(rel, 0, 2);
			*rel=equation[i];
			Push(s, SmartConcatInfix((char *)x2, rel, (char *)x1));
		}
	}
	result=Pop(s);
	return result;
}

/* TODO EX 1 */

int main() {
	char postfix[30] = "6 3 2 4 + – *";
	char infix[30] = "a * b + c / d - e * f * g - h";
	char prefix[30] = "+ * a b - / c d - * * e f g h";
	char *Infix=(char *)malloc(30);

	/* Exemplu de apeluri functii pe stiva */
	TStiva s = InitS();
	int vec[5] = {2,3,1,5,4};
	int *x;

	for (int i = 0; i < 5; i++) {
		/* elementele puse pe stiva trebuie alocate pe heap */
		x = malloc(sizeof(int));
		*x = vec[i];
		Push(s, x);
	}
	Infix=PostfixToInfix(postfix);
	printf("%s\n", Infix);
	AfisareS(s, afisInt);

	afisInt(Top(s));		// print 4
	printf(" TOP\n");
	afisInt(Pop(s));		// print 4
	printf(" POP\n");
	afisInt(Top(s));		// print 5 (noul varf)
	printf(" NEW TOP\n");

	SortareS(s, cmpInt);	// merge doar daca a fost implementata
	AfisareS(s, afisInt);
	DistrS(s);

	/* apeluri functii conversie */

    return 1;
}
