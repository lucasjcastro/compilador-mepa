#include "IdentHash.h"

IdentHash::IdentHash() {}
IdentHash::~IdentHash() {}

void IdentHash::insert( HashNode hNode ) {
    
    char* key = new char[hNode.getValueString().size() + 1];
    strcpy(key, hNode.getValueString().c_str());
    
    // inclue na posicao indicada pela funcao hashing o novo no hNode
    hashTable[ hashing( key ) ].push_back( hNode );
    
}

HashNode IdentHash::search( char* key ) {
    
    // iterador que percorrera a lista de HashNode em busca da palavra de busca
    std::list<HashNode>::iterator it;
    
    // lista auxiliar para busca de key
    std::list<HashNode> listAux = hashTable[ hashing( key ) ];
    
    // busca na lista por key
    for ( it = listAux.begin(); it != listAux.end(); it++ ) {
            
        if ( it->getValueString() == key ) {
            return *it;
        }
    }
    
    HashNode null;
    // retorna nulo caso a busca tenha falhado
    return null;
    
}

/**
    method hashing = implementacao padrao para hash retirada do livro AHO
    usa um numero primo como tamanho do vetor para minimizar colisoes
*/
unsigned IdentHash::hashing( char* key ) {
    
    char* p;
	
	unsigned h = 0, g;
	
	for ( p = key; *p != EOS; p = p + 1 ) {
        
		h = ( h << 4 ) + (*p);
		
		if ( g = h&0xf0000000 ) {
            
			h = h ^ ( g >> 24 );
			h = h ^ g;
			
		}
		
	} 	
	return h % PRIME_NUMBER;
}
