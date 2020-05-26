#pragma once
#include <iostream>
#include <vector>
#include "TResourceMesh.h"
#include "TResourceTexture.h"
#include "TResourceMaterial.h"
#include "TResourceText.h"
#include "TResourceJSON.h"

class TResourceManager{

    private:
        //array con los recursos a gestionar
        std::vector<TResource*> resources;

    public:
        // Constructor and destructor
        TResourceManager();
        ~TResourceManager();

        //obtener un recurso
        TResource *getResource(const char *name, int type, bool flip=false);
        std::vector<TResource*> getVectorResources(){return resources;};

};