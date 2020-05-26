#pragma once
#include <iostream>
#include "ITEntity.h"
#include <glm/gtx/matrix_decompose.hpp>

//clase usada como soporte en el caso de querer un nodo que no contenga entidad
class ITPivote: public ITEntity{

    private:

        TNode* pivote;

    public:

        ITPivote(TNode* father);
        ~ITPivote();

        TNode* getNode(){return pivote;};

};