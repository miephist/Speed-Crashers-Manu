#pragma once

#include "TCamera.h"
#include "TShaderProgram.h"
#include "TEntity.h"
#include "../ResourceManager/TResourceMesh.h"
#include "../ResourceManager/TResourceTexture.h"
#include "../ResourceManager/TResourceMaterial.h"


class TMesh : public TEntity{

    public:

        //constructor y destructor
        TMesh(TResourceMesh* m, TResourceTexture* t);
        ~TMesh();
        //metodos dibujado
        void beginDraw(int);
        void endDraw(int);

    private:
        //Almacenamiento del buffer
        GLuint textureID;

        //malla
        TResourceMesh* mesh;
        //textura
        TResourceTexture* texture;
        //material
        TResourceMaterial* material;

};