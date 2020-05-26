#pragma once
#include "structs.h"
#include "map"
#include "vector"
#include "GraphicsEngine.h"
#include "../Player/JugadorRed.h"

#define SERVER_PORT 60000
#define MAX_CLIENTS 2

class Server{

    private:

        //Instancia
        static Server* instancia;
        std::map<int,std::vector<int>> localizacion;
        
        RakNet::RakPeerInterface *peer;
        RakNet::Packet *packet;

        GraphicsEngine* motor;

        unsigned char packetIdentifier;

        int numPlayers;
        JugadorRed* player;
        std::vector<JugadorRed*> players;

        // Vector de posicion y rotacion de Irrlicht
	    glm::vec3 pos;
	    glm::vec3 rot;

        btVector3 initPos;

        int idJugador;

    public:

        Server();
        ~Server();

        static Server* getInstancia();

        void Init();
        void Update();
        unsigned char GetPacketIdentifier(RakNet::Packet *p);
        void refreshServer();
        void startGame();

        std::vector<JugadorRed*> getPlayers(){return players;};
};