#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "Cache.h"

//base que llevan todas las entidades
class TEntity{

    public:
        //dispone de cache para permitir el manejo de matrices
        static Cache cache;
        //metodos virtuales de dibujado
        virtual void beginDraw(int pasada)=0;
        virtual void endDraw(int pasada)=0;

};