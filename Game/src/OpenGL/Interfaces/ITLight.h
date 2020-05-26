#pragma once
#include <iostream>
#include "../Arbol/Luces/Direccional.h"
#include "../Arbol/Luces/Focal.h"
#include "../Arbol/Luces/Puntual.h"

#include "ITEntity.h"

class ITLight: public ITEntity{

    private:

        TNode* light;

        bool act;
        

    public:

        //Constructor luces puntual y direccional
        ITLight(TNode* father,glm::vec4 ,glm::vec3 ,glm::vec3 ,glm::vec3 );
        //Constructor luz focal
        ITLight(TNode* father, glm::vec3 amb, glm::vec3 dif ,glm::vec3 spec,glm::vec3 targ,glm::vec3 Pos,float cut,float out);

        //destructor
        ~ITLight();

        //activate
        void Activate(bool x){act=x;};

        //getters
        TNode* getNode(){return light;};
        TLight* getLight();

};