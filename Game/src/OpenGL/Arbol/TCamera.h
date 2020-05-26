#define GLM_ENABLE_EXPERIMENTAL

#pragma once
#include <iostream>
#include "TEntity.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

struct viewport
{

    float near;
    float far;
    float fov;
    float ratio;

};


class TCamera : public TEntity{
    public:

    enum CamType{ PERSPECTIVE, ORTHOGRAPHIC };
    
    private:

    viewport view;

    CamType type;

    glm::vec3 target;
    glm::vec3 camPosition;

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;

    bool tipo;

    public:

        // Constructor and destructor
        TCamera(viewport);

        ~TCamera();

        // Metodos dibujado
        void beginDraw(int);
        void endDraw(int);
        
        //metodos para recalcular cuando se producen cambios
        void calculateProjectionMatrix();
        void calculateViewMatrix();
        void calculateViewMatrix(glm::vec3 Pos);
        void calculateViewMatrix(glm::vec3 Pos, glm::vec3 Tar);
        //setters
        void setTargetPosition(glm::vec3);
        void setCameraPosition(glm::vec3);
        void setNear(float);
        void setFar(float);
        void setFov(float);
        void setTipo(bool t){tipo=t;};
        //getters
        glm::mat4 getProjectionMatrix();
        glm::mat4 getViewMatrix();
        glm::vec3 getPosition();
        glm::vec3 getTarget(){return target;};

       

};