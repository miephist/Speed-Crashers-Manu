#pragma once
#include "structs.h"
#include "GraphicsEngine.h"
#include "../Player/JugadorRed.h"

class Client{

    private:

        //Instancia
        static Client* instancia;

        std::string str;
        bool isServer;
        RakNet::Packet *packet;
        RakNet::RakPeerInterface *peer;
        RakNet::SocketDescriptor sd;

        GraphicsEngine* motor;

        JugadorRed* player;
        std::vector<JugadorRed*> players;

        btVector3 initPos;
        char * IPGlob;
        bool check;

    public:

        Client();
        ~Client();

        static Client* getInstancia();

        void Init();
        void setIP();
        void Update();
        void refresh(JugadorRed* playerRefresh);
       
        JugadorRed* getPlayer(){return player;};
        std::vector<JugadorRed*> getPlayers(){return players;};

};