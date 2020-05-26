#pragma once
#include <iostream>
#include "../Arbol/TShaderProgram.h"
#include "ITEntity.h"

class ITShader{
    private:

        TShaderProgram* sha;

    public:
        //Constructor y destructor
        ITShader(std::string, std::string );
        ~ITShader();

        //getter
        TShaderProgram* getShader(){return sha;};
};