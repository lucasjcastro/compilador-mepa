#include "Sintatico.h"

/* Construtores */
Sintatico::Sintatico()
{
}

Sintatico::Sintatico( std::list<TokenListNode> lista)
{
	this->lexTokenList = lista;
}

/* Destrutor */
Sintatico::~Sintatico()
{
}

/* Metodos Auxiliares */
void
Sintatico::nextToken()
{
	this->currentToken = this->lexTokenList.front();
	this->lexTokenList.pop_front();
}

void
Sintatico::spyToken()
{
	this->aheadToken = this->lexTokenList.front();
}

/* Fim dos Metodos Auxiliares */

/* PRODUCOES */

/** 1. <programa> ::=
 * 			program <identificador>(<lista de identificadores>); <bloco>.
 */
void
Sintatico::programa()
{	
	
}

void
Sintatico::bloco()
{

}

void
Sintatico::parteDeclaracoesRotulo()
{
	
}

void
Sintatico::parteDefinicoesTipo()
{
	
}

void
Sintatico::definicaoTipo()
{
	
}

void
Sintatico::tipo()
{
	
}

void
Sintatico::indice()
{
	
}
        
void
Sintatico::parteDeclaracoesVariaveis()
{
	
}
        
void
Sintatico::declaracaoVariavel()
{
	
}

void
Sintatico::listaIdentificadores()
{
	
}

void
Sintatico::parteDeclaracoesSubRotinas()
{
	
}

void
Sintatico::declaracaoProcedimento()
{
	
}

void
Sintatico::declaracaoFuncoes()
{
	
}

void
Sintatico::parametrosFormais()
{
	
}

void
Sintatico::secaoParametrosFormais()
{
	
}

void
Sintatico::comandoComposto()
{
	
}

void
Sintatico::comando()
{
	
}

void
Sintatico::comandoSemRotulo()
{
	
}

void
Sintatico::atribuicao()
{
	
}

void
Sintatico::chamadaProcedimento()
{
	
}

void
Sintatico::desvios()
{
	
}

void
Sintatico::comandoCondicional()
{
	
}

void
Sintatico::comandoRepetitivo()
{
	
}

void
Sintatico::listaExpressoes()
{
	
}

void
Sintatico::expressao()
{
	
}

void
Sintatico::relacao()
{
	
}

void
Sintatico::expressaoSimples()
{
	
}

void
Sintatico::termo()
{
	
}

void
Sintatico::fator()
{
	
}

void
Sintatico::variavel()
{
	
}

void
Sintatico::chamadaFuncao()
{
	
}

/** 32.
 * 		<numero> ::= <digito>{<digito>}
 */
bool
Sintatico::numero()
{
	if( currentToken.getTokenType() == _NUMERO )
    {
    	nextToken();
    	return true;
    }
    else
    {
    	return false;
    }	
}

void
Sintatico::identificador()
{
	
}

