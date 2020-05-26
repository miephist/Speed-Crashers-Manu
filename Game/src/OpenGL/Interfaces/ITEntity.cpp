#include "ITEntity.h"
//constructor que crea una rama donde estan las 3 transformaciones
//los hijos colocarán su nodo al final de la rama
ITEntity::ITEntity(TNode* father){

    translate = new TNode();
    rotate = new TNode();
    scale = new TNode();

    TTransform* trans = new TTransform();
    TTransform* rot = new TTransform();
    TTransform* sca = new TTransform();

    translate->setEntity(trans);
    rotate->setEntity(rot);
    scale->setEntity(sca);

    father->addChild(rotate);
    rotate->setFather(father);

    rotate->addChild(scale);
    scale->setFather(rotate);
    
    scale->addChild(translate);
    translate->setFather(scale);

    gtrans=glm::vec3(0);
    gsca=glm::vec3(0);
    grot=glm::vec3(0);

    lastAngle = 0;

    visible = true;
}

ITEntity::~ITEntity(){
    delete translate;
    delete rotate;
    delete scale;

}


void ITEntity::setPosition(float x, float y, float z){

    TTransform* t = (TTransform*)translate->getEntity();
    t->translate(x, y, z);
    gtrans = glm::vec3(x, y, z);
}

void ITEntity::setPosition(glm::vec3 pos){

    TTransform* t = (TTransform*)translate->getEntity();
    t->translate(pos);
    gtrans = pos;
}

void ITEntity::setRotation(float x, float y, float z, float angle){

    TTransform* r = (TTransform*)rotate->getEntity();
    r->rotate(x, y, z, angle);
    grot = glm::vec3(x, y, z);
}

void ITEntity::setRotation(glm::vec3 eje, float angle){

    TTransform* r = (TTransform*)rotate->getEntity();
    r->rotate(eje, angle);
    grot = eje;
    lastAngle = angle;
}

void ITEntity::setScale(float x, float y, float z){

    TTransform* s = (TTransform*)scale->getEntity();
    s->scale(x, y, z);
    gsca = glm::vec3(x, y, z);
}

void ITEntity::setScale(glm::vec3 scal){

    TTransform* s = (TTransform*)scale->getEntity();
    s->scale(scal);
    gsca = scal;
}

void ITEntity::setVisible(bool vis){
    rotate->setVisible(vis);
    visible = vis;
}