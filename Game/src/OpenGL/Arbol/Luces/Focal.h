
#define GLM_ENABLE_EXPERIMENTAL

#pragma once
#include <iostream>
#include "../TLight.h"
#include <glm/glm.hpp>

class Focal : public TLight{

    private:

        glm::vec3 target;
        glm::vec3 lightPos;

        float cutOff;
        float outerCut;

    //variables base
        //float constant;
        //float linear;
        //float quadratic;
    
    public:

    //constructor y destructor
    Focal(glm::vec3, glm::vec3 ,glm::vec3 ,glm::vec3 ,glm::vec3  ,float ,float );
    ~Focal();
    //dibujado
    void beginDraw(int) override;
    void endDraw(int) override {};
    //setters
    void setTarget(glm::vec3 tar){target=tar;};
    void setPos(glm::vec3 pos){lightPos=pos;};
    void setCut(float C){cutOff=C;};
    void setOuter(float O){outerCut=O;};
    //getters
    glm::vec3 getPosition(){return lightPos;};
    glm::vec3 getTarget(){return target;};

};
