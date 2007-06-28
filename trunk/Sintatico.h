#ifndef SINTATICO_H_
#define SINTATICO_H_

#include "TokenListNode.h"

class Sintatico
{
	private:
	
		//Arvore Sintática
		//Noh de Arvore sintática*;
		
		TokenListNode
		currentToken;
				
		TokenListNode
		aheadToken;
		
		void
		nextToken();
		
		void
		spyNextToken();
	
		void
        programa();
        
        void
        bloco();
        
        void
        parteDeclaracoesRotulo();
        
        void
        parteDefinicoesTipo();
        
        void
        definicaoTipo();
        
        void
        tipo();
        
        void
        indice();
        
        void
        parteDeclaracoesVariaveis();
        
        void
        declaracaoVariavel();
        
        void
        listaIdentificadores();
        
        void
        parteDeclaracoesSubRotinas();
        
        void
        declaracaoProcedimento();
        
        void
        declaracaoFuncoes();
        
        void
        parametrosFormais();
        
        void
        secaoParametrosFormais();
        
        void
        comandoComposto();
        
        void
        comando();
        
        void
        comandoSemRotulo();
        
        void
        atribuicao();
        
        void
        chamadaProcedimento();
        
        void
        desvios();
        
        void
        comandoCondicional();
        
        void
        comandoRepetitivo();
        
        void
        listaExpressoes();
        
        void
        expressao();
        
        void
        relacao();
        
        void
        expressaoSimples();
        
        void
        termo();
        
        void
        fator();
        
        void
        variavel();
        
        void
        chamadaFuncao();
        
        bool
        numero();
        
        bool
        digito();
        
        void
        identificador();
        
        bool
        letra();
        
        void
        proximo();
        
        void
        olhaProximo();
        
	public:
	
		Sintatico(std::list< TokenListNode >);
		
		Sintatico();
		
		virtual
		~Sintatico();
	

};

#endif /*SINTATICO_H_*/
