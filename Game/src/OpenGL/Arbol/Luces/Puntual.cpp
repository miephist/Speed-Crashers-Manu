#include "Puntual.h"
//la creacion base está en TLight
Puntual::Puntual(glm::vec3 Pos, glm::vec3 amb,glm::vec3 dif,glm::vec3 spec):TLight(amb,dif,spec){

    setPos(Pos);

}

Puntual::~Puntual(){

}

void Puntual::beginDraw(int pasada){

    if(active && pasada==0){

        std::string ss;

        ss = "pointLights[" + std::to_string(id) + std::string("].");


        
        glm::vec3 Pos=glm::vec3(TEntity::cache.mpila.top()*glm::vec4(lightPos,1.f));

        TEntity::cache.shader->setVec3("viewPos",TEntity::cache.camera->getPosition());

        std::string zz;

        zz=ss+std::string("position");
        TEntity::cache.shader->setVec3(zz, Pos);
        zz=ss+std::string("ambient");
        TEntity::cache.shader->setVec3(zz, ambient);
        zz=ss+std::string("diffuse");
        TEntity::cache.shader->setVec3(zz, diffuse);
        zz=ss+std::string("specular");
        TEntity::cache.shader->setVec3(zz, specular);
        zz=ss+std::string("constant");
        TEntity::cache.shader->setFloat(zz, 1.0f);
        zz=ss+std::string("linear");
        TEntity::cache.shader->setFloat(zz, 0.007);
        zz=ss+std::string("quadratic");
        TEntity::cache.shader->setFloat(zz, 0.0002);
        zz=ss+std::string("creada");
        TEntity::cache.shader->setBool(zz, true);
    
    }
}