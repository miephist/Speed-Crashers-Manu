#pragma once
#include "../Engines/structs.h"
#include "../Engines/AudioEngine.h"

class InitState{

    public:

        InitState();
        ~InitState();

        void Init();
        void Update();
        void Render();

    private:

        int carga;

        //Shader
        ITShader* Shader;

};