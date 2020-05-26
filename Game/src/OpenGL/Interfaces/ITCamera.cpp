#include "ITCamera.h"
//creacion rama en ITEntity, aqui se crea el ultimo nodo con la camara
ITCamera::ITCamera(TNode* scene, glm::vec3 pos, glm::vec3 target, viewport v):ITEntity(scene){

    camera= new TNode();

    TCamera* cam= new TCamera(v);

    cam->setCameraPosition(pos);
    cam->setTargetPosition(target);

    act = false;

    camera->setEntity(cam);
    camera->setFather(translate);

    translate->addChild(camera);
}
ITCamera::~ITCamera(){
    delete camera;
}
//Obtener entidad camara
TCamera* ITCamera::getCamera(){

    TCamera* cam;
    cam=(TCamera*)camera->getEntity();

    return cam;
}
//se activa para mostrar y se cocola en la cache
void ITCamera::Activate(bool x){

    act = x;

    if(act == true)
        TEntity::cache.setCamera(this->getCamera());

}