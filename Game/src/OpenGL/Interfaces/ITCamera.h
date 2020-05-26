#pragma once
#include <iostream>
#include "../Arbol/TCamera.h"
#include "ITEntity.h"

class ITCamera: public ITEntity{
    private:

        TNode* camera;  

        bool act;

    public:
        //constructor y destructor
        ITCamera(TNode* scene, glm::vec3 pos, glm::vec3 target,viewport v);
        ~ITCamera();

        //acivar camara
        void Activate(bool x);
        //obtener camara
        TCamera* getCamera();

};
