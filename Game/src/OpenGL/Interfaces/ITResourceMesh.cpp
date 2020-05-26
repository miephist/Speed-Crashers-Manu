#include "ITResourceMesh.h"
//creacion base en ITEntity, aqui crea el objeto al final
ITResourceMesh::ITResourceMesh(TNode* scene, TResourceMesh* res, TResourceTexture* text):ITEntity(scene){

    
    resource = res;
    texture = text;
    material = resource->getMaterial();
    TMesh* mesh=new TMesh(resource, texture);
    node=new TNode();
    node->setEntity(mesh);
    node->setFather(translate);
    translate->addChild(node);
    
}


ITResourceMesh::~ITResourceMesh(){

  
    delete node;
    delete resource;
    delete texture;
}