#pragma once
#include "../Engines/structs.h"
#include "../Engines/AudioEngine.h"
#include "../Engines/Client.h"
#include "../Engines/Server.h"
#include "../Engines/Options.h"

class MenuState{

    public:

        // Constructor
        MenuState();
        ~MenuState();

        void Init();
        void Update();
        void Render();
        void CheckInputs();
        void startMenu();
        void optionsMenu();

        //Multiplayer
        void multiplayerMenu();
        void lobbyMenu(bool isServer2);
        void cleanMultiplayer();
        
        bool getIsServer(){return isServer;};

    private:

        // Keyboard && JOystick
        int oldState;
        int oldState2;

        int newState;
        int newState2;

        int isPressed;
        int actualOption;

        // Menus
        int numOptions;
        int actualMenu;
        int lastMenu;
        bool multiplayer;

        bool entro;

        // Opciones Partido
        int cont;

        int actualMode;
        bool mode;

        int actualTimer;

        bool derecha;
        bool izquierda;

        int carga;

        //Shader
        ITShader* Shader;
        ITShader* shaderModelo;

        GraphicsEngine* gEngine;

        //Multiplayer
        bool isServer;

        int act;
        void changePnj(int);
        void noPnj();

        std::vector<ITAnimation*>pnjAct;
        
};