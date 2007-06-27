//Douglas Schmidt
//este include ja possui as bibliotecas stdio.h, ctype.h e string.h
#include "lexico.h"
#include "TokenListNode.h"
#include <list>
#include <string>

int main(int argc, char **argv)
{
	if (argc <= 1)
	{
		printf("Erro: Especifique uma entrada.\n");
		//system("PAUSE");
		return 1;
	}

	FILE *entrada;

	if ((entrada = fopen(argv[1], "r")) == NULL)
	{
		printf("Erro: Arquivo %s nao pode ser aberto.\n", argv[1]);
		//system("PAUSE");
		return 2;
	}

	//fila de tokens
	struct Fila *tokens;	
	inicializarFila(&tokens);
	int ntokens = 0;
	
	//lista de tokens
	std::list< TokenListNode >
	tokenList;
	
	TokenListNode tmpTokenListNode;

	//analise lexica
	if (analiseLexica(entrada, tokens) == ERRO)
	{
        printf("Erro: Analise mal sucedida.\n");
        //system("PAUSE");
        //return 1;
    }

	//esvazia fila de tokens e imprime cada um
	struct Token proximo;
	do
	{
		desenfilera(tokens, &proximo);

		if (proximo.tipo == ERRO)
		{
			printf("Erro lexico: %d,%d em %s: \n", proximo.linha, proximo.coluna, argv[1]);

			//printf("%d\n", proximo.valor);
			switch (proximo.valor)
			{
				case ERRO_ID_INVALIDO:
				    printf("Identificador invalido.\n");
					break;
				case ERRO_SIMBOLO_INV:
					printf("Simbolo invalido.\n");
			}
			fclose(entrada);
			return 3;
		}
		else
		{
			ntokens++;

			switch (proximo.tipo)
			{

                /**
                    #define INTEIRO			0
                    #define IDENTIFICADOR	1
                    #define PAL_RESERVADA	2
                    #define SIMBOLO			3
                    #define SIMBOLO_COMP	4
                    #define BOLEANO			5
                    #define ERRO			6
                    #define TERMINO			7
                */
                case INTEIRO:
					printf("%d,%d:\tInteiro:\t%d\n",
					proximo.linha, proximo.coluna, proximo.valor);
					
					tmpTokenListNode.setTokenType("numero");
					tmpTokenListNode.setTokenValue(proximo.valor);
					
					break;
				case IDENTIFICADOR:
					printf("%d,%d:\tIdentificador:\t%s\n",
					proximo.linha, proximo.coluna, proximo.nome);
					free(proximo.nome);
					break;
				case PAL_RESERVADA:
					printf("%d,%d:\tPal. reservada:\t%s\n",
					proximo.linha, proximo.coluna, reservadas[proximo.valor]);
					break;
				case SIMBOLO:
					printf("%d,%d:\tSimbolo:\t%s\n",
					proximo.linha, proximo.coluna, simbolos[proximo.valor]);
					break;
				case SIMBOLO_COMP:
					printf("%d,%d:\tSim. composto:\t%s\n",
					proximo.linha, proximo.coluna, simbolos[proximo.valor]);
					break;
				case BOLEANO:
					printf("%d,%d:\tBooleano:\t%s\n",
					proximo.linha, proximo.coluna, reservadas[proximo.valor]);
					break;
				case IGNORA:
					ntokens--;
					break;
			}
		}
	}
	while (proximo.tipo != TERMINO);

	free(tokens);

	fclose(entrada);

	printf("\n\tN. Tokens:\t%d\n\n", ntokens);

    //system("PAUSE");
	return 0;
}
