#include "Direccional.h"
//la creacion base está en TLight
Direccional::Direccional(glm::vec3 direc, glm::vec3 amb,glm::vec3 dif,glm::vec3 spec):TLight(amb,dif,spec){

    setDirection(direc);

}

Direccional::~Direccional(){
    
}

void Direccional::beginDraw(int pasada){


    if(active && pasada==0){
        
        //Encadenamos para pasar en la posicion que ocupa en vector y ocupará en fragment
        std::string ss;

        ss = "dirLights[" + std::to_string(id) + std::string("].");

    
        std::string zz;
        
        TEntity::cache.shader->setVec3("viewPos",TEntity::cache.camera->getPosition());
        zz=ss+std::string("ambient");
        TEntity::cache.shader->setVec3(zz, ambient);
        zz=ss+"diffuse";
        TEntity::cache.shader->setVec3(zz, diffuse);
        zz=ss+"specular";
        TEntity::cache.shader->setVec3(zz, specular);
        zz=ss+"direction";
        TEntity::cache.shader->setVec3(zz, Direction);
        zz=ss+"creada";
        TEntity::cache.shader->setBool(zz, true); 

    }
}