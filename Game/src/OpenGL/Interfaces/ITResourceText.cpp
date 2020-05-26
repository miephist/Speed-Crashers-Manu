#include "ITResourceText.h"
//creacion base en ITEntity, aqui crea el objeto al final
ITResourceText::ITResourceText(TNode* father, TResourceText* t, TShaderProgram* s):ITEntity(father){

    text = t;

    TText* textEntity = new TText(text, s);

    node=new TNode();
    node->setEntity(textEntity);
    node->setFather(translate);
    translate->addChild(node);
    
}


ITResourceText::~ITResourceText(){

    delete node;
    delete text;

}