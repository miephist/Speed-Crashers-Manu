#include "Focal.h"
//la creacion base está en TLight
Focal::Focal(glm::vec3 amb, glm::vec3 dif ,glm::vec3 spec,glm::vec3 targ,glm::vec3 Pos,float cut,float out):TLight(amb, dif, spec){

    setTarget(targ);
    setPos(Pos);
    setCut(cut);
    setOuter(out);

}

Focal::~Focal(){

}

void Focal::beginDraw(int pasada){

    if(active && pasada==0){
        //aplicamos las transformaciones a la posicion
        //se trabaja con posicion relativa al centro cuando se crea la camara pero la posicion va en relacion al mundo
        glm::vec3 Pos=glm::vec3(TEntity::cache.mpila.top()*glm::vec4(lightPos,1.f));
        glm::vec3 tar=glm::vec3(TEntity::cache.mpila.top()*glm::vec4(target,1.f));

        TEntity::cache.shader->setVec3("viewPos",TEntity::cache.camera->getPosition());

        std::string ss;

        ss = "spotLights[" + std::to_string(id) + std::string("].");

    
        std::string zz;
        
        zz=ss+"position";
        TEntity::cache.shader->setVec3(zz, Pos);
        zz=ss+"direction";
        TEntity::cache.shader->setVec3(zz, tar);
        zz=ss+"ambient";
        TEntity::cache.shader->setVec3(zz, ambient);
        zz=ss+"diffuse";
        TEntity::cache.shader->setVec3(zz, diffuse);
        zz=ss+"specular";
        TEntity::cache.shader->setVec3(zz, specular);
        zz=ss+"constant";
        TEntity::cache.shader->setFloat(zz, 1.0f);
        zz=ss+"linear";
        TEntity::cache.shader->setFloat(zz, 0.007);
        zz=ss+"quadratic";
        TEntity::cache.shader->setFloat(zz, 0.0002);
        zz=ss+"cutOff";
        TEntity::cache.shader->setFloat(zz, glm::cos(glm::radians(cutOff)));
        zz=ss+"outerCutOff";
        TEntity::cache.shader->setFloat(zz, glm::cos(glm::radians(outerCut))); 
        zz=ss+"creada";
        TEntity::cache.shader->setBool(zz, true);


    }
}

