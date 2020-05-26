#pragma once
#include "../Engines/structs.h"
#include "../Engines/PhysicsEngine.h"
#include "../Engines/TriggerSystem.h"
#include "../Engines/GraphicsEngine.h"
#include "../Player/JugadorRed.h"
#include "../Engines/Server.h"
#include "../Engines/Client.h"

class GameStateRed {

    private:

        // Motor de fisicas
        PhysicsEngine * bullet;
        TriggerSystem *collide;

        // Jugadores Red
        JugadorRed* player;

        // Motor Grafico
        GraphicsEngine *gEngine;
        //Receiver *receiver;

        // Servidor
        Server *server;

        // Cliente
        Client *client;

        // Temporizador
        int lastFPS;
        int then;
        
        //vector players
        std::vector<JugadorRed*> players;

        // Texto para la interfaz
        irr::gui::IGUIStaticText *textoUI;
        irr::core::stringw text;

    public:

        GameStateRed();
        ~GameStateRed();

        void Init();
        void UpdatePlayersWheels();
        void Update();
        void Render(int TDeltaTime);
        void UpdateRender(btRigidBody *TObject);
        JugadorRed* Getplayer()                 {return player;};

};