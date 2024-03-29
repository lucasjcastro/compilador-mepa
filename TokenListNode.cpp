#include "TokenListNode.h"

TokenListNode::TokenListNode()
{
	this->mLine = 0;		
	this->mValueString = "\0";
}

TokenListNode::~TokenListNode()
{
}

/* Sets and Gets */
			
			/* Token type */
			void
			TokenListNode::setTokenType(TokenType settingTT)
			{
				this->mTokenType = settingTT;
			}	
					
			TokenType
			TokenListNode::getTokenType()
			{
				return (this->mTokenType);
			}			
			
			/* Token Value sobrecarregados*/
			void
			TokenListNode::setTokenValue(std::string tokenValue)
			{
				this->mValueString = tokenValue;
			}
			
			void
			TokenListNode::setTokenValue(int tokenValue)
			{
				this->mValueInt = tokenValue;
			}
			
			std::string
			TokenListNode::getValueString()
			{
				return (this->mValueString);
			}
			
			int
			TokenListNode::getValueInt()
			{
				return (this->mValueInt);
			}
			
			/* Token Line in Sourece-code */
			void
			TokenListNode::setLine(int line)
			{
				this->mLine = line;
			}
			
			int
			TokenListNode::getLine()
			{
				return this->mLine;
			}
