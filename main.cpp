//Douglas Schmidt
//este include ja possui as bibliotecas stdio.h, ctype.h e string.h
#include "lexico.h"
#include "TokenListNode.h"
#include <list>
#include <string>
#include <iterator>
#include <iostream>

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
	
	TokenListNode auxTokenListNode;

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
		auxTokenListNode.setTokenValue("\0");
		auxTokenListNode.setTokenValue(-99199);

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
					
					/* Construcao da Lista de Tokens */
					auxTokenListNode.setTokenType( _NUMERO );
					auxTokenListNode.setTokenValue(proximo.valor);
					auxTokenListNode.setLine(proximo.linha);
					
					break;
				case IDENTIFICADOR:
					printf("%d,%d:\tIdentificador:\t%s\n",
					proximo.linha, proximo.coluna, proximo.nome);
					
					/* Construcao da Lista de Tokens */
					auxTokenListNode.setTokenType( _IDENTIFICADOR );
					auxTokenListNode.setTokenValue(proximo.nome);
					auxTokenListNode.setLine(proximo.linha);
					
					free(proximo.nome);
					break;
				case PAL_RESERVADA:
					printf("%d,%d:\tPal. reservada:\t%s\n",
					proximo.linha, proximo.coluna, reservadas[proximo.valor]);
					
					/* Construcao da Lista de Tokens */
					/* Se for or, and ou not, tipo eh op_logico */
					if ( (strcmp(reservadas[proximo.valor], reservadas[13]) == 0 ) || // or
						 (strcmp(reservadas[proximo.valor], reservadas[14]) == 0 ) || // and
						 (strcmp(reservadas[proximo.valor], reservadas[16]) == 0 ) )  // not
						  	auxTokenListNode.setTokenType( _OP_LOGICO );
						  	/* Se for div eh op_aritmetico */
							else if (strcmp(reservadas[proximo.valor], reservadas[15]) == 0 ) // div
						 			auxTokenListNode.setTokenType( _OP_ARITMETICO );
						 			/* Se for integer ou boolean eh _datatype */
						 			else if ( (strcmp(reservadas[proximo.valor], reservadas[17])  == 0) || // integer
						 					  (strcmp(reservadas[proximo.valor], reservadas[18]) == 0) )  // boolean
						 						auxTokenListNode.setTokenType( _DATATYPE );
						 						else /* qq outra palavra reservada */
						 						  auxTokenListNode.setTokenType( _PAL_RESERVADA );
						 				
					/* Depois de redefinido o tipo do token, grava os dados */	 											
					auxTokenListNode.setTokenValue(reservadas[proximo.valor]);
					auxTokenListNode.setLine(proximo.linha);						 
					
					break;
				case SIMBOLO:
					printf("%d,%d:\tSimbolo:\t%s\n",
					proximo.linha, proximo.coluna, simbolos[proximo.valor]);
					
					/* Construcao da Lista de Tokens */
					if ( (strcmp(simbolos[proximo.valor], simbolos[9])  == 0) || // <
						 (strcmp(simbolos[proximo.valor], simbolos[12]) == 0) )  // >
						 	auxTokenListNode.setTokenType( _OP_RELACIONAL );
						 	else
					 		if ( (strcmp(simbolos[proximo.valor], simbolos[0])  == 0) || // -
					 			 (strcmp(simbolos[proximo.valor], simbolos[13]) == 0) || // +
					 			 (strcmp(simbolos[proximo.valor], simbolos[14]) == 0) )	 // *
					 			 	auxTokenListNode.setTokenType( _OP_ARITMETICO );
					 			 	else
				 			 		if ( (strcmp(simbolos[proximo.valor], simbolos[1]) == 0) || // .
				 			 			 (strcmp(simbolos[proximo.valor], simbolos[2]) == 0) || // ,
				 			 			 (strcmp(simbolos[proximo.valor], simbolos[6]) == 0) || // :
				 			 			 (strcmp(simbolos[proximo.valor], simbolos[3]) == 0) )  // ;
				 			 			 	auxTokenListNode.setTokenType( _PONTUACAO );
				 			 			 	else
						 			 		if ( (strcmp(simbolos[proximo.valor], simbolos[4])  == 0) || // (
						 			 			 (strcmp(simbolos[proximo.valor], simbolos[5])  == 0) )  // )						 			 			 
						 			 			 	auxTokenListNode.setTokenType( _SIMBOLOS );
						 			 			 	
					auxTokenListNode.setTokenValue(simbolos[proximo.valor]);
					auxTokenListNode.setLine(proximo.linha);										 
					
					break;
				case SIMBOLO_COMP:
					printf("%d,%d:\tSim. composto:\t%s\n",
					proximo.linha, proximo.coluna, simbolos[proximo.valor]);
					
					/* Construcao da Lista de Tokens */
					if ( (strcmp(simbolos[proximo.valor], simbolos[8])  == 0) || // <>
						 (strcmp(simbolos[proximo.valor], simbolos[10]) == 0) || // <=			 		 
						 (strcmp(simbolos[proximo.valor], simbolos[11]) == 0) )  // >=
						 	auxTokenListNode.setTokenType( _OP_RELACIONAL );						 	
						 	else
					 		 	auxTokenListNode.setTokenType( _SIMBOLOS ); // soh sobrou o :=
					 			 	
					auxTokenListNode.setTokenValue(simbolos[proximo.valor]);
					auxTokenListNode.setLine(proximo.linha);					 			 	
					
					break;
				case BOLEANO:
					printf("%d,%d:\tBooleano:\t%s\n",
					proximo.linha, proximo.coluna, reservadas[proximo.valor]);
					
					/* Construcao da Lista de Tokens */
					auxTokenListNode.setTokenType( _BOLEANO );
					auxTokenListNode.setTokenValue(reservadas[proximo.valor]);
					auxTokenListNode.setLine(proximo.linha);
					
					break;
				case IGNORA:
					ntokens--;
					break;
			}
			/* insere TokenNode na Lista de Tokens */
			if ( proximo.tipo != IGNORA)
				tokenList.push_back(auxTokenListNode);   // <<<<  SAIDA DO LEXICO
		}
	}
	while (proximo.tipo != TERMINO);

	free(tokens);

	fclose(entrada);

	printf("\n\tN. Tokens:\t%d\n\n", ntokens);
	
	//CHAMAR SINTATICO AQUI
	// Reimprimindo a lista...
	 for (unsigned int d = 0 ; d <= tokenList.size() ; d++)
	 {
	 	auxTokenListNode = tokenList.front();
	 	std::cout << auxTokenListNode.getTokenType();
	 	if (auxTokenListNode.getValueString() != "\0")
	 		std::cout << "\t" << auxTokenListNode.getValueString() << std::endl;
	 	else
	 		std::cout << "\t" << auxTokenListNode.getValueInt() << std::endl;
	 		
	 	tokenList.pop_front();
	 }
	 
	 std::cout << "Tamanho tokenList: " << tokenList.size() << std::endl;
	 
	 std::string letra;
	 

    //system("PAUSE");
	return 0;
}
