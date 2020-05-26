#include "TNode.h"
//constructor
TNode::TNode(){

    entity=nullptr;
    
    father=nullptr;

    visible=true;

}
//Destructor
TNode::~TNode(){

    delete entity;

    father=nullptr;

    for(int i=0; i < children.size(); i++)
        delete children.at(i);

    children.clear();

}
//añadir un hijo al nodo
int TNode::addChild(TNode* child){

    if(child != nullptr){
        children.push_back(child);
        child->setFather(this);
        return 1;
    }

    return 0;
}
//quitar un hijo al nodo
int TNode::removeChild(TNode* child){

    for(int i=0; i < children.size(); i++){
        if(children.at(i) == child){
            delete children.at(i);
            return 1;
        }
    }
    return 0;
}
//asignar una entidad al nodo
bool TNode::setEntity(TEntity* newEntity){

    if(newEntity != nullptr){
        entity = newEntity;
        return true;
    }else{
        return false;
    }
}
//dibujado
void TNode::draw(int pasada){

    //comprobar si es visible
    if(visible){   
        //tiene entidad asignada
        if(entity!=nullptr)
            //dibujado
            entity->beginDraw(pasada);            
        
        //si tiene hijo llama al draw de los mismos
        if(!getChildren().empty()){
            for(int hijo=0; hijo < children.size(); hijo++){

                children.at(hijo)->draw(pasada); 
            }
        }

        //finaliza dibujado
        if(entity!=nullptr)   
            entity->endDraw(pasada);
    }   
}