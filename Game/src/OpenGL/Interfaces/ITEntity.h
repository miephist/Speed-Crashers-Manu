#pragma once
#include <iostream>
#include "../Arbol/TEntity.h"
#include "../Arbol/TNode.h"
#include "../Arbol/TTransform.h"

class ITEntity{
    protected:

        TNode* translate;
        TNode* rotate;
        TNode* scale;

        glm::vec3 gtrans;
        glm::vec3 gsca;
        glm::vec3 grot; 

        float lastAngle;

        bool visible;
        ITEntity(TNode* father);

    public:
        //destructor
        ~ITEntity();
        //setters
        void setPosition(float x, float y, float z);
        void setPosition(glm::vec3);

        void setRotation(float x, float y, float z, float angle);
        void setRotation(glm::vec3, float angle);

        void setScale(float x, float y, float z);
        void setScale(glm::vec3);

        void setVisible(bool);

        //getters
        glm::vec3 getPosition(){return gtrans;};
        glm::vec3 getRotation(){return grot;};
        glm::vec3 getScale(){return gsca;};

        bool isVisible(){return visible;};
        
};