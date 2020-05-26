#define GLM_ENABLE_EXPERIMENTAL

#pragma once
#include <iostream>
#include <vector>
#include "TEntity.h"

class TNode{

    private:

        TEntity *entity;
        std::vector<TNode*> children;
        TNode *father;

        //visibilizar a partir de este nodo
        bool visible;

    public:

        // Constructor and destructor
        TNode();
        ~TNode();

        // Manejo de hijos
        // Añade un hijo
        int addChild(TNode* child);
        // Borra un hijo
        int removeChild(TNode* child);
        

        // Setters
        bool setEntity(TEntity* newEntity);
        void setFather(TNode* fat){father=fat;};
        void setVisible(bool v){visible=v;};
        //getters
        TEntity *getEntity(){return entity;};
        TNode *getFather(){return father;};
        std::vector<TNode*> getChildren(){return children;};
        
        // funcion de dibujado
        void draw(int);

};