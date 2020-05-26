#define GLM_ENABLE_EXPERIMENTAL

#pragma once
#include <iostream>
#include "TEntity.h"
#include <glm/mat4x4.hpp> // glm::mat4

#include <GL/gl.h>
#include <GL/glu.h>

#include <stack>
#include <glm/gtx/string_cast.hpp> 


class TTransform : public TEntity{

    private:
        //matriz que guarda la transformacion
        glm::mat4 matrix;

        glm::mat4 resultado;

    public:

        // Constructor y destructor
        TTransform();
        ~TTransform();

        //identidad
        void identity();
        //cargar una nueva
        void load(glm::mat4 newMatrix);
        //transpuesta
        void transpose();
        //inversa
        void inverse();

        //Metodos de transformacion
        void translate(float x, float y, float z);
        void translate(glm::vec3);
        void rotate(float x, float y, float z, float angle);
        void rotate(glm::vec3, float);
        void scale(float x, float y, float z);
        void scale(glm::vec3);

        //Metodos de dibujado
        void beginDraw(int);
        void endDraw(int);

        //obtener resultado
        glm::mat4 getResultado(){return resultado;};
};