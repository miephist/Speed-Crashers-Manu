#include "ITAnimation.h"
//creacion rama en ITEntity, aqui se crea el ultimo nodo con la animacion
ITAnimation::ITAnimation(TNode* scene, std::vector<TMesh*> mallas):ITEntity(scene){
 
        TAnimation* anim=new TAnimation(mallas);
        Animacion=new TNode();
        Animacion->setEntity(anim);
        Animacion->setFather(translate);

        translate->addChild(Animacion);
    

}


ITAnimation::~ITAnimation(){

}

void ITAnimation::reset(){
        TAnimation* ani =(TAnimation*)Animacion->getEntity();
        ani->res();
}