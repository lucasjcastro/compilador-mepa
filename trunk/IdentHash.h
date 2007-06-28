#ifndef _IDENTHASH__H
#define _IDENTHASH__H

#include <string>
#include <list>
#include <iostream>

#include "HashNode.h"

#define PRIME_NUMBER 211
#define EOS '\0'

/**
*   CLASS Hash
*   Stores a identifier that will be used to verify the level or escope for the
*   ident. declaration
*/

class IdentHash {
    
    public:
        
        // constructor e destructor limpos
        IdentHash();
        virtual ~IdentHash();
        
        /*
            method insert
            param: HashNode =       na a ser armazenado na tabela hash;
        */
        void insert( HashNode hNode );
        
        /*
            method search
            param: char* =          string para o nome ou descricao do token
                                    que sera usada para buscar o no de Hash
                                    na tabela;
            return: HashNode =      no da Hash encontrado;
        */
        HashNode search( char* key );
        
    private:
        
        // vetor de listas de HashNode que sera usado como nossa tabela Hash
        std::list < HashNode > hashTable[PRIME_NUMBER];
        
        /*
            method hashing
            param: char* =          string chave para conversao que resultara
                                    em um valor int que sera o indice do 
                                    vetor hashTable[];
            return: unsigned =      valor unsigned int que sera usado como indice
                                    do vetor hashTable[];
        */
        unsigned hashing( char* key );
};

#endif
