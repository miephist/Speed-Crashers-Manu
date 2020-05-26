#pragma once

#include <iostream>
#include "ITEntity.h"

#include "../Arbol/TShaderProgram.h"
#include "../ResourceManager/TResourceText.h"
#include "../Arbol/TText.h"


class ITResourceText: public ITEntity{
    private:

        TNode* node; 
        TResourceText* text;    

    public:
        //constructor y destructor
        ITResourceText(TNode* father, TResourceText* t, TShaderProgram* s);
        ~ITResourceText();
        //obtener nodo
        TNode* getNode(){return node;};
        //setter
        void setResource(TResourceText* resour){text=resour;};
        //getters
        TResourceText* getText(){return text;};

};

