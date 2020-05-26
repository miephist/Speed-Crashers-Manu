#include "Client.h"
#include "enums.h" 

#define SERVER_PORT 60000

Client::Client(){

	// http://www.dinomage.com/2012/06/basic-networking-with-raknet/
    // Obtenemos la instancia de la interfaz para el cliente
    //peer = RakNet::RakPeerInterface::GetInstance();

}

Client::~Client(){

	std::cout << "Cerramos cliente" << std::endl;
    // Destruimos la interfaz del cliente
	peer->Shutdown(300);
    RakNet::RakPeerInterface::DestroyInstance(peer);
    
}

void Client::Init(){

	peer = RakNet::RakPeerInterface::GetInstance();

    // Inicializamos el cliente con un maximo de 6 jugadores
    peer->Startup(6,&sd, 1);
    isServer = false;

}

void Client::setIP(){

    // Mostramos mensaje y esperamos a que se introduzca el servidor
    printf("Enter server IP or write 0 for 127.0.0.1\n");
    std::cin >> str;

    // Convertimos el string en char
    char * IP = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), IP);
    IP[str.size()] = '\0';

    // Servidor por defecto al escribir 0
    if (IP[0]==0){
		strcpy(IP, "127.0.0.1");
	}

    // Realizamos la conexion con la IP pasada y el puerto por defecto
    printf("Starting the client.\n");
    peer->Connect(IP, SERVER_PORT, 0,0);

}

void Client::Update(){

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
						printf("We have been disconnected.\n");
					break;
				case ID_CONNECTION_LOST:
						printf("Connection lost.\n");
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