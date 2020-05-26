#pragma once

#include <iostream>
#include <vector>
#include "TResource.h"
#include "../Arbol/TShaderProgram.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class TResourceMaterial : public TResource{

    private:
        //brillo
        float shiny;
        //colores para la iluminacion del objeto con las iluminaciones
        glm::vec3 colAmb;
        glm::vec3 colDif;
        glm::vec3 colSpec; 
    
    public:
        //constructor y destructor
        TResourceMaterial();
        ~TResourceMaterial();

        //uso para antes de dibujaado de malla
        void activeMaterial();

        //setters
        void loadMaterial(std::string name);
        void setShiny(float newShiny)                           {shiny = newShiny;};
        void setAmbient(float r, float g, float b)              {colAmb = glm::vec3(r,g,b);};
        void setDiffuse(float r, float g, float b)              {colDif = glm::vec3(r,g,b);};
        void setSpecular(float r, float g, float b)             {colSpec = glm::vec3(r,g,b);};

        //getters
        const char *getName() override;
        void setName(const char *newName) override;
};