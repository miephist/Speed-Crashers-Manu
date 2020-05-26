#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "ITEntity.h"

#include "../ResourceManager/TResourceMesh.h"
#include "../ResourceManager/TResourceTexture.h"
#include "../ResourceManager/TResourceMaterial.h"
#include "../Arbol/TMesh.h"


class ITResourceMesh: public ITEntity{
    private:

        
        TNode* node; 
        TResourceMesh* resource;
        TResourceTexture* texture;
        TResourceMaterial* material;
        

    public:
        //constructor y destructor
        ITResourceMesh(TNode* father, TResourceMesh* res, TResourceTexture* text);
        ~ITResourceMesh();
        //obtener nodo
        TNode* getNode(){return node;};
        //setter
        void setResource(TResourceMesh* resour){resource=resour;};
        //getters
        TResourceTexture* getTextureID(){return texture;};
        TResourceMesh* getResource(){return resource;};
        
};

