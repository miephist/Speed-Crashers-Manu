#ifndef SERVER_H
#define SERVER_H

#pragma once
#include <stdio.h>
#include <iostream>
//#include "structs.h"
#include "../../../include/raknet/RakPeerInterface.h"
#include "../../../include/raknet/MessageIdentifiers.h"
#include "../../../include/raknet/BitStream.h"
#include "../../../include/raknet/RakNetTypes.h"

#define SERVER_PORT 60000
#define MAX_CLIENTS 10

class Server{

    private:

        RakNet::RakPeerInterface *peer;
        RakNet::Packet *packet;

    public:

        Server();
        ~Server();

        void Init();
        void Update();

};

#endif