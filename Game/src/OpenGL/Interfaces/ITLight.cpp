#include "ITLight.h"

//creacion rama en ITEntity, aqui se crea el ultimo nodo con la luz

//direccional/puntual
ITLight::ITLight(TNode* father,glm::vec4 direc, glm::vec3 amb,glm::vec3 dif,glm::vec3 spec):ITEntity(father){

    light= new TNode();

    translate->addChild(light);

    if(direc[3]==0){

    //Direccional = 0
    Direccional* luz= new Direccional(glm::vec3(direc), amb, dif, spec); 
    light->setEntity(luz);  
    }

    else if(direc[3]==1){
    //Puntual = 1
    Puntual* luz= new Puntual(glm::vec3(direc), amb, dif, spec);
    light->setEntity(luz);
    

    }

    act=false;

}
//focal
ITLight::ITLight(TNode* father, glm::vec3 amb, glm::vec3 dif ,glm::vec3 spec,glm::vec3 targ,glm::vec3 Pos,float cut,float out):ITEntity(father){

    Focal* luz= new Focal(amb,dif,spec,targ,Pos,cut,out);

    light= new TNode();

    translate->addChild(light);

    light->setEntity(luz);

    act=false;

}
//destructor
ITLight::~ITLight(){
    delete light;
}
//obtener la entidad luz del nodo
TLight* ITLight::getLight(){

    TLight* l;
    l=(TLight*)light->getEntity();

    return l;
}