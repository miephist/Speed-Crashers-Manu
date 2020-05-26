#include "Server.h"

Server *Server::instancia = nullptr;

Server *Server::getInstancia(){

    if(instancia == nullptr)
        instancia = new Server();

    return instancia;

}

Server::Server(){
	std::vector<int> vec;
	vec.push_back(0);
	vec.push_back(2);
	vec.push_back(-10);

	int meter=7; 	
	localizacion.insert(std::pair<int,std::vector<int>>(7,vec));
	std::vector<int> vec2;
	vec2.push_back(0);
	vec2.push_back(2);
	vec2.push_back(50);
	localizacion.insert(std::pair<int,std::vector<int>>(8,vec2));
	motor = GraphicsEngine::getInstancia();
	numPlayers = 0;

	idJugador = 7;

}

Server::~Server(){

    // Destruimos la interfaz del servidor
    peer->Shutdown(300);
    RakNet::RakPeerInterface::DestroyInstance(peer);


	instancia = nullptr;

}

void Server::Init(){

    peer = RakNet::RakPeerInterface::GetInstance();

    RakNet::SocketDescriptor sd(SERVER_PORT, 0);
    peer->Startup(MAX_CLIENTS, &sd, 1);
	//isServer = true;

	// Numero maximo de conexiones
    peer->SetMaximumIncomingConnections(MAX_CLIENTS);

	motor->addText(L"Starting the client.\nLocal IP: ");
	motor->addText(irr::core::stringw(peer->GetLocalIP(0)) + "\n");

	// Se realizan ping ocacionales a los clientes para comprobar, por ejemplo, paquetes perdidos
	peer->SetOccasionalPing(true); 	 
	// Se modifica el tiempo de espera de desconexion del servidor
	peer->SetUnreliableTimeout(1000);

}

void Server::Update(){

	motor = GraphicsEngine::getInstancia();

    for (packet=peer->Receive(); packet; peer->DeallocatePacket(packet), packet=peer->Receive())
		{

			packetIdentifier = GetPacketIdentifier(packet); // We got a packet, get the identifier with our handy function

			switch (packetIdentifier)
				{
				case ID_REMOTE_DISCONNECTION_NOTIFICATION:
					motor->addText(L"Another client has disconnected.\n");
					break;
				case ID_REMOTE_CONNECTION_LOST:
					motor->addText(L"Another client has lost the connection.\n");
					break;
				case ID_REMOTE_NEW_INCOMING_CONNECTION:
					motor->addText(L"Another client has connected.\n");
					break;
				case ID_CONNECTION_REQUEST_ACCEPTED:
					motor->addText(L"Our connection request has been accepted.\n");
					break;					
				case ID_NEW_INCOMING_CONNECTION:
					{
					motor->addText(L"A connection is incoming.\n");
					
					RakNet::BitStream bsOut;
					bsOut.Write((RakNet::MessageID)Auxiliar::GameMessages::ID_SPAWN_PLAYER_CLIENT);
					bsOut.Write(idJugador);
					bsOut.Write(localizacion.find(idJugador)->second.at(0));
					bsOut.Write(localizacion.find(idJugador)->second.at(1));
					bsOut.Write(localizacion.find(idJugador)->second.at(2));
					peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);

					//std::cout << "Id enviada: " << idJugador << std::endl;

					}
					break;
				case ID_NO_FREE_INCOMING_CONNECTIONS:
					motor->addText(L"The server is full.\n");
					break;
				case ID_DISCONNECTION_NOTIFICATION:
						motor->addText(L"A client has disconnected.\n");
					break;
				case ID_CONNECTION_LOST:
						motor->addText(L"A client lost the connection.\n");
					break;

                case Auxiliar::GameMessages::ID_GAME_MESSAGE_1:
				    {
					RakNet::RakString rs;
					RakNet::BitStream bsIn(packet->data,packet->length,false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(rs);
					motor->addText(rs.C_String());
				    }
				break;

				case Auxiliar::GameMessages::ID_SPAWN_PLAYER_SERVER:
					{

					int id;

					RakNet::BitStream bsIn(packet->data,packet->length,false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(initPos);
					bsIn.Read(id);

					player = new JugadorRed(glm::vec3(initPos[0], initPos[1], initPos[2]),initPos[0],initPos[2], id,"JugadorRed");

					players.push_back(player);
					
					////std::cout << "ID Coche: " << player->getCoche()->getID() << std::endl;

					////std::cout << "ID Vector Coche: " << players.at(0)->getCoche()->getID() << std::endl;

					//std::cout << initPos.getX() <<", "<< initPos.getY() << ", " << initPos.getZ() << std::endl;

					idJugador++;

					numPlayers++;
					
					//std::cout << "Size vvector:"<<players.size()<<std::endl;;
					irr::core::stringw prueba = L"Jugador creado, en total: ";
        			prueba += numPlayers;
        			prueba += "\n";
					motor->addText(prueba);

						// Cuando hayamos creado todos los jugadores permitidos (por ahora 2)
						if(numPlayers == MAX_CLIENTS){
							// Empieza la partida, llamar al GameState de Red utilizando los Jugadores de Red
							startGame();
						}
					}
				break;
				case Auxiliar::GameMessages::ID_WAITING_PLAYER:
				{
					
					RakNet::BitStream bsIn(packet->data,packet->length,false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					RakNet::BitStream bsOut;
					bsOut.Write((RakNet::MessageID)Auxiliar::GameMessages::ID_REFRESH_SERVER);
					peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);

				}
				break;
				case Auxiliar::GameMessages::ID_REFRESH_SERVER:
				{
					glm::vec3 pos = player->getCoche()->getPosition();
					glm::vec3 rot = player->getCoche()->getRotation();
					btScalar stering = player->getSteering();
					btScalar force = player->getEngineF();
					btScalar breakingbad = player->getbrakeForce();
					int comprobacion;
					int ID;
					int idpasar = 0;
					RakNet::BitStream bsOut;
					RakNet::BitStream bsIn(packet->data,packet->length,false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					// Leemos posiciones
					bsIn.Read(comprobacion);
					bsIn.Read(ID);
					
					
					
					switch(comprobacion){
						case 1:
						{
								bsIn.Read(pos.x);
								bsIn.Read(pos.y);
								bsIn.Read(pos.z);
								bsIn.Read(rot.x);
								bsIn.Read(rot.y);
								bsIn.Read(rot.z);
								for(int i=0; i < players.size(); i++){
									if(players.at(i)!=nullptr && players.at(i)->getCoche()->getResource()->getID() == ID){
										players.at(i)->getCoche()->setPosition(pos);
										players.at(i)->getCoche()->setRotation(rot, 0);
									}
								}
								
								bsOut.Write((RakNet::MessageID)Auxiliar::GameMessages::ID_REFRESH_CLIENT);
								bsOut.Write(comprobacion);
								bsOut.Write(numPlayers);
								
								for(int i=0; i < players.size(); i++){
									if(ID!=players.at(i)->getCoche()->getResource()->getID()){
										idpasar = players.at(i)->getCoche()->getResource()->getID();
										bsOut.Write(idpasar);
										bsOut.Write(players.at(i)->getCoche()->getPosition().x);
										bsOut.Write(players.at(i)->getCoche()->getPosition().y);
										bsOut.Write(players.at(i)->getCoche()->getPosition().z);
										bsOut.Write(players.at(i)->getCoche()->getRotation().x);
										bsOut.Write(players.at(i)->getCoche()->getRotation().y);
										bsOut.Write(players.at(i)->getCoche()->getRotation().z);

									}
								}
						}
						break;

						case 2:
						{
								bsIn.Read(stering);
								bsIn.Read(force);
								bsIn.Read(breakingbad);
								for(int i=0; i < players.size(); i++){
									if(players.at(i)!=nullptr && players.at(i)->getCoche()->getResource()->getID() == ID){
										players.at(i)->setSteering(stering);
										players.at(i)->setEngineF(force);
										players.at(i)->setBrakeForce(breakingbad);
									}
								}
								bsOut.Write((RakNet::MessageID)Auxiliar::GameMessages::ID_REFRESH_CLIENT);
								bsOut.Write(comprobacion);
								
								for(int i=0; i < players.size(); i++){
									if(ID != players.at(i)->getCoche()->getResource()->getID()){
										idpasar = players.at(i)->getCoche()->getResource()->getID();
										bsOut.Write(idpasar);
						
										bsOut.Write(players.at(i)->getSteering());
										bsOut.Write(players.at(i)->getEngineF());
										bsOut.Write(players.at(i)->getbrakeForce());
									}
								}
						}
						break;

						case 3:
						{}
						break;
					}
					
					
					// Leemos numero de jugadores
					//bsIn.Read(numPlayers);

					// Seteamos posiciones y rotaciones de los coc-1hes
					
					
					
					
					
					
					peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);
					
					

				}
				break;

				default:
					motor->addText(L"Message with identifier %i has arrived.\n");
					motor->addText(irr::core::stringw(packet->data[0]));
					break;
				}
		}
}

// Obtenemos el identificador del paquete
unsigned char Server::GetPacketIdentifier(RakNet::Packet *p){
	
	if (p == 0)
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
		return (unsigned char) p->data[sizeof(unsigned char) + sizeof(unsigned long)];
	else
		return (unsigned char) p->data[0];
}


void Server::refreshServer(){

	//std::cout << "Refrescamos servidor\n";

	// Tipo de RakNet para el mensaje de salida
	RakNet::BitStream bsOut;

	// Se escribe el tipo de ID en el mensaje de salida
	bsOut.Write((RakNet::MessageID)Auxiliar::GameMessages::ID_REFRESH_SERVER);

	//std::cout << "Numero de jugadores: " << numPlayers << std::endl;

	// Entidades a refrescar
	for (int i = 0; i < players.size(); i++)
	{
		// Le pasamos la posicion del jugador
		pos = players.at(i)->getCoche()->getPosition();
		bsOut.Write(pos.x);
		bsOut.Write(pos.y);
		bsOut.Write(pos.z);

		// Le indicamos tambien la rotacion
		rot = players.at(i)->getCoche()->getRotation();
		bsOut.Write(rot.x);
		bsOut.Write(rot.y);
		bsOut.Write(rot.z);

	}

	// Se envia el mensaje de salida
	peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, false);
}

void Server::startGame(){

	// Llamamos al caso ID_START_GAME de cada Cliente
	RakNet::BitStream bsOut;
    bsOut.Write((RakNet::MessageID)Auxiliar::GameMessages::ID_START_GAME);
    peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);

}