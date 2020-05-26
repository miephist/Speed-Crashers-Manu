#define GLM_ENABLE_EXPERIMENTAL

#pragma once
#include <iostream>
#include "../TLight.h"


class Puntual : public TLight{

    private:

        glm::vec3 lightPos;

    public:

    //constructor y destructor
    Puntual(glm::vec3, glm::vec3 ,glm::vec3 ,glm::vec3);
    ~Puntual();
    //dibujado
    void beginDraw(int) override;
    void endDraw(int) override {};
    //setter
    void setPos(glm::vec3 pos){lightPos=pos;};
};

        