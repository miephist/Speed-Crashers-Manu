#include "ITPivote.h"
//Creacion base en ITEntity, aqui crea un pivote al final
ITPivote::ITPivote(TNode* father):ITEntity(father){

    
    pivote = new TNode();

    translate->addChild(pivote);

    pivote->setFather(translate);


}

ITPivote::~ITPivote(){
    delete pivote;
}
