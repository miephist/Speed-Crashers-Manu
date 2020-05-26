#pragma once
#include <iostream>
#include <vector>
#include "../Arbol/TAnimation.h"
#include "ITEntity.h"


class ITAnimation: public ITEntity{
    private:

        TNode* Animacion;
        
    public:
        //constructor y destructor
        ITAnimation(TNode* scene, std::vector<TMesh*> mallas);
        ~ITAnimation();
        void reset();
        
};

