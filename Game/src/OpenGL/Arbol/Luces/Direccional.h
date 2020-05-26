#define GLM_ENABLE_EXPERIMENTAL

#pragma once
#include <iostream>
#include "../TLight.h"
#include <glm/glm.hpp>

class Direccional : public TLight{

    private:

        glm::vec3 Direction;
    
    public:

    //constructor y destructor
    Direccional(glm::vec3 direc, glm::vec3 amb,glm::vec3 dif,glm::vec3 spec);
    ~Direccional();
    //dibujado
    void beginDraw(int) override;
    void endDraw(int) override {};
    //modificar direccion
    void setDirection(glm::vec3 direc){Direction=direc;};

};


