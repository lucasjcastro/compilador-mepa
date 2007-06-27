#ifndef TOKENLISTNODE_H_
#define TOKENLISTNODE_H_

#include <string>

/**
 * Esta classe é usada para reunir os atributos
 * dos Tokens. Os objetos serão armazenados na
 * Lista Ligadao de Tokens que o analisador léxico pas-
 * sara para o analisador sintático.
 */

class TokenListNode
{
	
	private:
	
		std::string
		mTokenType;
		
		std::string  
		mValueString;
		
		int
		mValueInt;
	
		int
		mLine;		
		
	
	public:

		TokenListNode();
		
		virtual
		~TokenListNode();
		
		/* Sets and Gets */
			
			/* Token type */
			void
			setTokenType(std::string tokenType);	
					
			std::string
			getTokenType();			
			
			/* Token Value */
			void
			setTokenValue(std::string tokenValue);
			void
			setTokenValue(int tokenValue);
			
			std::string
			getValueString();
			int
			getValueInt();
			
			/* Token Line in Sourece-code */
			void
			setLine(int line);
			
			int
			getLine();		
};

#endif /*TOKENLISTNODE_H_*/
