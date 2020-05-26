#pragma once
#include "../Engines/structs.h"
#include "../Engines/AudioEngine.h"

class ScoreState{

    public:

        ScoreState();
        ~ScoreState();

        void Init();
        void Update();
        void Render();
        void CheckInputs();

    private:

        int oldState;
        int oldState2;

        int newState;
        int newState2;

        int isPressed;
        int actualOption;

        bool entro;

        char* rutaB; 
        char* rutaR;

        //Shader
        ITShader* Shader;

};