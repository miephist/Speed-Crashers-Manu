#define GLM_ENABLE_EXPERIMENTAL

#pragma once
#include <iostream>
#include "TEntity.h"
#include <glm/glm.hpp>
#include "../Arbol/TMesh.h"

class TAnimation : public TEntity{

    private:
    
        std::vector<TMesh*> meshes;
        
        int currentIndex;
        int frames;

    public:
        // Constructor and destructor
        TAnimation(std::vector<TMesh*> );
        ~TAnimation();

        //dibujado
        void beginDraw(int);
        void endDraw(int){};
        void res(){currentIndex=0;};
       

};