#include "Server.h"
#include "enums.h" 

Server::Server(){

}

Server::~Server(){

    std::cout << "Cerramos servidor" << std::endl;
    // Destruimos la interfaz del servidor
    peer->Shutdown(300);
    RakNet::RakPeerInterface::DestroyInstance(peer);

}

void Server::Init(){

    peer = RakNet::RakPeerInterface::GetInstance();

    RakNet::SocketDescriptor sd(SERVER_PORT, 0);
    peer->Startup(MAX_CLIENTS, &sd, 1);
	//isServer = true;

    peer->SetMaximumIncomingConnections(MAX_CLIENTS);

}

void Server::Update(){
    for (packet=peer->Receive(); packet; peer->DeallocatePacket(packet), packet=peer->Receive())
		{
			switch (packet->data[0])
				{
				case ID_REMOTE_DISCONNECTION_NOTIFICATION:
					printf("Another client has disconnected.\n");
					break;
				case ID_REMOTE_CONNECTION_LOST:
					printf("Another client has lost the connection.\n");
					break;
				case ID_REMOTE_NEW_INCOMING_CONNECTION:
					printf("Another client has connected.\n");
					break;
				case ID_CONNECTION_REQUEST_ACCEPTED:
                    {
					printf("Our connection request has been accepted.\n");

					// Use a BitStream to write a custom user message
					// Bitstreams are easier to use than sending casted structures, and handle endian swapping automatically
					RakNet::BitStream bsOut;
					bsOut.Write((RakNet::MessageID)GameMessages::ID_GAME_MESSAGE_1);
					bsOut.Write("Hello world");
					peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);
				    }
					break;					
				case ID_NEW_INCOMING_CONNECTION:
					printf("A connection is incoming.\n");
					break;
				case ID_NO_FREE_INCOMING_CONNECTIONS:
					printf("The server is full.\n");
					break;
				case ID_DISCONNECTION_NOTIFICATION:
						printf("A client has disconnected.\n");
					break;
				case ID_CONNECTION_LOST:
						printf("A client lost the connection.\n");
					break;

                case GameMessages::ID_GAME_MESSAGE_1:
				    {
					RakNet::RakString rs;
					RakNet::BitStream bsIn(packet->data,packet->length,false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(rs);
					printf("%s\n", rs.C_String());
				    }
				break;

				default:
					printf("Message with identifier %i has arrived.\n", packet->data[0]);
					break;
				}
		}
}
