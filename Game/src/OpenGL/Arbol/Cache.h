#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GL/gl.h"

#include <stack>
#include <glm/glm.hpp>

class TCamera;
class TShaderProgram;

class Cache {

    public:
        //pila donde se acumularán las matrices
        std::stack<glm::mat4> mpila;
        //camara que está actualmente en uso
        TCamera* camera;
        //Shader actualemente en uso
        TShaderProgram* shader;
        //constructor y destructor
        Cache();
        ~Cache();
        //setters
        void setShader(TShaderProgram* s){shader=s;};
        void setCamera(TCamera* cam){camera=cam;};
        //getter
        TCamera* getCamera(){return camera;};

    private:


};