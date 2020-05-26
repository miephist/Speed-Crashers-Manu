#pragma once

#include "TCamera.h"
#include "TShaderProgram.h"
#include "TEntity.h"
#include "../ResourceManager/TResourceText.h"

#include "../../Engines/Options.h"


class TText : public TEntity{

    public:

        //constructor y destructor
        TText(TResourceText* t, TShaderProgram* s);
        ~TText();
        //metodos dibujado
        void beginDraw(int);
        void endDraw(int);

    private:
        //Almacenamiento del buffer
        GLuint textID;

        //malla
        TResourceText* text;
        TShaderProgram* shader;

        bool entro = false;
};