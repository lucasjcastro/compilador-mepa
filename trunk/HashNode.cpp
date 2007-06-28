#include "HashNode.h"

// sets
void HashNode::setLevel( int nlevel ) {
    level = nlevel;
}

void HashNode::setValueString( std::string nvalue ) {
    value = nvalue;
}
void HashNode::setIdentifierType( identifierType ntIdent ) {
    tIdent = ntIdent;
}
void HashNode::setVariableType( variableType ntVar ) {
    tVar = ntVar;
}
                                                    
// gets
int HashNode::getLevel() {
    return level;
}

std::string HashNode::getValueString() {
    return value;
}

identifierType HashNode::getIdentifierType() {
    return tIdent;
}

variableType HashNode::getVariableType() {
    return tVar;
}
