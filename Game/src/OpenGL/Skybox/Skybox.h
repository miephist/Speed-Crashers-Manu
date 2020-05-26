#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include "../Interfaces/ITShader.h"
#include "../Arbol/TEntity.h"
#include "../Arbol/TCamera.h"

class Skybox{

    private:

        GLuint skyboxID;

        /*  Render data  */
        unsigned int VAO, VBO;
        
        // Parametros de la imagen
        unsigned char *textures[6];
        int width[6];
        int height[6];
        int channels[6];

    public:

        // Constructor y destructor
        Skybox();
        ~Skybox();
        //cargas y ajustes
        unsigned char* loadImage(const char* file, int pos);
        void setupSkybox();
        void loadCubemap();
        void setSkyboxVertices();
        //dibujado
        void draw(ITShader* shaderSkybox);

};