#pragma once

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../Arbol/TCamera.h"
#include "ITShader.h"

class Lines{

    public:

        Lines(float x, float y, float z, float a, float b, float c, glm::vec4 col);
        ~Lines();

        // GETTERS
        std::vector <GLfloat> getVertexPoints()     {return points;};
        glm::vec4 getColorLines()                   {return color;};

        // SETTERS
        void setAdditionalPoints(float x, float y, float z, float a, float b, float c);
        void setColorLine(glm::vec4 newColor){color = newColor;};

        // DRAW
        void drawDebugLines(ITShader* shaderLines, bool isDebugActive);

    private:

        GLuint debugPhysicsVAO, debugPhysicsVBO;
        std::vector <GLfloat> points;
        glm::vec4 color;

};