#ifndef CLIENT_H
#define CLIENT_H

#pragma once
#include <stdio.h>
#include <iostream>
//#include "structs.h"
#include "../../../include/raknet/RakPeerInterface.h"
#include "../../../include/raknet/MessageIdentifiers.h"
#include "../../../include/raknet/BitStream.h"
#include "../../../include/raknet/RakNetTypes.h"

class Client{

    private:

        std::string str;
        bool isServer;
        RakNet::Packet *packet;
        RakNet::RakPeerInterface *peer;
        RakNet::SocketDescriptor sd;

    public:

        Client();
        ~Client();

        void Init();
        void setIP();
        void Update();

};

#endif