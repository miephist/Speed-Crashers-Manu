#define GLM_ENABLE_EXPERIMENTAL

#pragma once
#include <iostream>
#include "TEntity.h"
#include <glm/glm.hpp>

#include "TCamera.h"
#include "TShaderProgram.h"

class TShaderProgram;
class TCamera;

class TLight : public TEntity{

    protected:
       
        //Atributos comunes a todas las luces
        unsigned int VBO;
        unsigned int lightVAO;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        bool active;
        unsigned int id;

        //esta en privado porque solo accederán los hijos
        TLight(glm::vec3 ,glm::vec3 ,glm::vec3 ,glm::vec4 ,float ,float );

    public:

        // Constructor y destructor
        
        TLight(glm::vec3 ,glm::vec3 ,glm::vec3);
        ~TLight();

        //setters
        void setSpecular(glm::vec3 spec){specular=spec;};
        void setAmbient(glm::vec3 amb){ambient=amb;};
        void setDiffuse(glm::vec3 dif){diffuse=dif;};
        void Activate(bool act){active=act;};
        void setID(unsigned int newid){id=newid;};        

        // Metodos dibujado
        virtual void beginDraw(int pasada)=0;
        virtual void endDraw(int pasada)=0;

};