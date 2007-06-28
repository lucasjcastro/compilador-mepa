#ifndef _HASHNODE__H
#define _HASHNODE__H

#include <string>

/**
*   CLASS Hash
*   Stores a identifier that will be used to verify the level or escope for the
*   ident. declaration
*/

// enum usado para facilitar a classificacao dos tipos de identificador
enum identifierType { t_variable, t_precedure, t_function };

// enum usado para classificar os tipos de variavel
enum variableType { t_integer, t_boolean, t_string };


class HashNode {
    
    public:
        // sets para variaveis privadas
        void setLevel( int level );
        
        void setValueString( std::string value );
        
        void setIdentifierType( identifierType tIdent );
        void setVariableType( variableType tVar );
        
        // gets para as variaveis
        int getLevel();
        std::string getValueString();
        identifierType getIdentifierType();
        variableType getVariableType();                     
        
    private:
        
        int level;
        
        std::string value;
        
        identifierType tIdent;
        
        variableType tVar;
    
};

#endif
