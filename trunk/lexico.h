#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#include "fila.h"

//Tipos de Tokens
#define INTEIRO			0
#define IDENTIFICADOR	1
#define PAL_RESERVADA	2
#define SIMBOLO			3
#define SIMBOLO_COMP	4
#define BOLEANO			5
#define ERRO			6
#define TERMINO			7
#define IGNORA			8

//booleanos
#define TRUE			1
#define FALSE			0

//representa simbolo negativo
#define MENOS			0

//Tipos de erros validos
#define ERRO_ID_INVALIDO	1
#define ERRO_SIMBOLO_INV	2

//quantidade de simbolos
#define N_SIMBOLOS		18

//quantidade de palavras reservadas
#define N_RESERVADAS	25

//constante para o tamanho maximo de uma palavra a ser lida
#define MAX_CHAR    	32

//buffer para resolver o problema de palavras lidas que nao sao validas
char buffer[MAX_CHAR];
int posBuf = 0;

//referencia ao arquivo
FILE *arquivo;
int linha, coluna;

//Simbolos
const char *simbolos[] = {"-",".",",",";","(",")",":","=","<>","<",">","+","*",
"/","[","]",":=",".."};

//Palavras reservadas
const char *reservadas[] = {"false", "true", "program", "begin", "end", "label",
 "type", "array", "of", "var", "procedure", "function", "if", "then", "else",
 "while", "do", "or", "and", "div", "not", "case", "record", "uses", "integer"};

//Prototipos
extern int analiseLexica(FILE *entrada, struct Fila *fila);

//verifica espaco em branco
int espaco(char c);

//le proximo caracter na entrada
char proximo();

//retorna o buffer, volta a leitura
void retornaBuffer(char c);

//retorna o proximo token
struct Token capturaToken();

//faz a analise lexica, retorna ERRO caso entrada invalida
int analiseLexica(FILE *entrada, struct Fila *fila)
{
	//ininicializa dados do arquivo
	arquivo = entrada;
	linha = coluna = 1;

	//token auxiliar
	struct Token token;

	//enfilera os tokens lidos
	do
	{
        token = capturaToken();
		enfilera(fila, token);

		//retorna caso encontre um erro
		if(token.tipo == ERRO) return ERRO;
	}
	while(token.tipo != TERMINO && token.tipo != ERRO);
	return 0; //allok
}

//retorna Token lido
struct Token capturaToken()
{
	//concatenacao
	char palavra[MAX_CHAR];
	int i;
	int p = 0;

	//token auxiliar
	struct Token t;

	//caracter auxiliar
	char c;
	
	//numero gambiarrar
	int comment = 0;
	
	//verifica espacos em branco
	while (espaco(c = proximo()));

	//setando token
	t.linha = linha;
	t.coluna = coluna;

	//checa fim do arquivo
	if (feof(arquivo))
	{
		t.tipo = TERMINO;
		return t;
	}

    //concatena
    palavra[(p < MAX_CHAR) ? p++ : p] = c;
	palavra[p] = '\0';

	//verifica se char eh letra
	if (isalpha(c))
    {
        while (isalnum(c = proximo()) || c == '_') {
            //passa para minusculas pra nao ter problemas de checagem
            c = tolower(c);
            //concatena
            palavra[(p < MAX_CHAR) ? p++ : p] = c;
            palavra[p] = '\0';

        }
		//retorna ao inicio da token
		retornaBuffer(c);

		//busca na lista de palavras reservadas
		for (i = 0; i < N_RESERVADAS; i++)
			if (strcmp(palavra, reservadas[i]) == 0)
			{
					//verifica tipo de palavra
					t.tipo = (strcmp(palavra, reservadas[TRUE]) == 0 || strcmp(palavra, reservadas[FALSE]) == 0)?
					 BOLEANO : PAL_RESERVADA;
					t.valor = i;
					return t;
			}

		//eh identificador
		t.tipo = IDENTIFICADOR;
		//copia para nome
		t.nome = (char*) malloc(sizeof(char)*(strlen(palavra)+1));
		strcpy(t.nome, palavra);
	}
	else if (isdigit(c) || c == '-')
	{
		while (isdigit(c = proximo())) {
            //concatena
            palavra[(p < MAX_CHAR) ? p++ : p] = c;
            palavra[p] = '\0';

		}
		//retorna ao inicio
		retornaBuffer(c);

        //verifica se eh -
		if (strcmp(palavra, "-") == 0)
		{
			t.tipo = SIMBOLO;
			t.valor = MENOS;
			return t;
		}

		//nao pode ser alpha pq
		if (isalpha(c))
		{
			t.tipo = ERRO;
			t.valor = ERRO_ID_INVALIDO;

			//copia para nome
			//t.nome = (char*) malloc(sizeof(char)*(strlen(palavra)+1));
			//strcpy(t.nome, palavra);
		}
		else
		{
			t.tipo = INTEIRO;
			t.valor = atoi(palavra);
		}
	}
	else
	{
		c = proximo();
		if (c == '*')
				comment = 1;

        //se proximo tbh eh simbolo
		if ( !isalnum(c) && !espaco(c) )
		{
			
            //concatena
            palavra[(p < MAX_CHAR) ? p++ : p] = c;
            palavra[p] = '\0';

			for (i = 0; i < N_SIMBOLOS; i++)
				if (strcmp(palavra, simbolos[i]) == 0)
				{
					//simbolo eh composto
					t.tipo = SIMBOLO_COMP;
					t.valor = i;
					return t;
				}

			//limpa ultimo char lido
			palavra[--p] = '\0';
		}


		//buscar por simbolos de um char
		retornaBuffer(c);
		
		for (i = 0; i < N_SIMBOLOS; i++)
			if (strcmp(palavra, simbolos[i]) == 0)
			{		
				//if (strcmp(palavra, simbolos[4]) == 0) // se for (
				//{					
				//	char teste42 = fgetc(arquivo);					
				//	printf("%c", teste42);
					
				//	if (teste42 == '*')
				//	{	
				//		printf("bosta");					
				//		comment = 1;
				//		fseek(arquivo, -1, SEEK_CUR); //gambs
				//		proximo();	  //gambs pro num d Linhas
				//	}							
				//	else						
				//		fseek(arquivo, -1, SEEK_CUR); //gambs
				//}								 				
								
				if (comment == 0)
				{
					t.tipo = SIMBOLO;
					t.valor = i;
					return t;
				}
			}

		//se nao eh nada eh erro
        if (comment == 0)
        {
        	t.tipo = ERRO;
			t.valor = ERRO_SIMBOLO_INV;
        }else
           	t.tipo = IGNORA;
      
		//copia erro para nome
		//t.nome = (char*)malloc(sizeof(char)*(strlen(palavra)+1));
		//strcpy(t.nome, palavra);
	}

	//retorna token final
	return t;
}

//verifica espacos e comentarios
int espaco(char c)
{
		static int comment = 0;
		static char lastchar = '\0';

		if (!comment && (c == '{' || (lastchar == '(' && c == '*')))
		{
			lastchar = c;
			return (comment = 1);
		}
		else if (comment && (c == '}' || (lastchar = '*' && c == ')')))
		{
			lastchar = c;
			return !(comment = 0);
		}

		lastchar = c;
		return comment || isspace(c);
}

//le proximo char
char proximo()
{
	if (posBuf > 0)
		return buffer[--posBuf];
	else
	{
		char c = fgetc(arquivo);

		if (c == '\n')
		{
			linha++;
			coluna = 0;
		}
		else
			coluna++;

		return c;
	}
}

//retorna buffer caso leitura foi equivocada
void retornaBuffer(char c)
{
	if (posBuf >= MAX_CHAR)
		fprintf(stderr, "Estouro de buffer.\n");
	else
		buffer[posBuf++] = c;
}
