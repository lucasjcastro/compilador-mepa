#ifndef     _FILA__H
#define     _FILA__H

#include <stdio.h>
// estrutura da fila para uso de abstracao DADO_FILA, uso de union para minimizar espaco
struct Token
{
	int tipo;
	int linha, coluna;
	union
	{
		char *nome;
		int valor;
	};
};

#define DADO_FILA struct Token
//estrutura do noh
struct NohFila
{
	DADO_FILA dado;
	struct NohFila *proximo;
};
//estrutura da fila
struct Fila
{
	struct NohFila *inicio;
	struct NohFila *fim;
	unsigned int tamanho;
};

//definicoes de funcoes
extern void inicializarFila(struct Fila**);

extern void enfilera(struct Fila*, DADO_FILA);

extern int desenfilera(struct Fila*, DADO_FILA*);

extern int isEmptyFila(struct Fila*);

extern int destruirFila(struct Fila**);

//inicializa fila
void inicializarFila(struct Fila **fila)
{
	*fila = (struct Fila*) malloc(sizeof(struct Fila));
	(*fila)->inicio = NULL;
	(*fila)->fim = NULL;
	(*fila)->tamanho = 0;
}

//funcoes de uso da fila
void enfilera(struct Fila *fila, DADO_FILA dado)
{
	struct NohFila *novo =
	(struct NohFila*) malloc(sizeof(struct NohFila));

	novo->dado = dado;
	novo->proximo = NULL;

	if (fila->inicio == NULL)
	{
		fila->inicio = fila->fim = novo;
	}
	else
	{
		fila->fim->proximo = novo;
		fila->fim = novo;
	}

	fila->tamanho++;
}

int desenfilera(struct Fila *fila, DADO_FILA *dado)
{
	if (fila->inicio == NULL)
		return 1;

	*dado = fila->inicio->dado;

	struct NohFila *remove = fila->inicio;

	fila->inicio = fila->inicio->proximo;

	free(remove);

	fila->tamanho--;

	return 0;
}

int isEmptyFila(struct Fila *fila)
{
	return (fila->inicio == NULL);
}

int destruirFila(struct Fila **fila)
{
	DADO_FILA x;
	while ((*fila)->inicio != NULL)
		desenfilera(*fila, &x);

	free(*fila);
	*fila = NULL;
	return 0;
}
#endif
