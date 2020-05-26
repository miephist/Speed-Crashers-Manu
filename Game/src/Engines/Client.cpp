#include "Client.h"
#include "../Game/Game.h"
#include "PhysicsEngine.h"

#define SERVER_PORT 60000

Client *Client::instancia = nullptr;

Client *Client::getInstancia(){

    if(instancia == nullptr)
        instancia = new Client();

    return instancia;

}

Client::Client(){

	// http://www.dinomage.com/2012/06/basic-networking-with-raknet/
    // Obtenemos la instancia de la interfaz para el cliente
    //peer = RakNet::RakPeerInterface::GetInstance();

	// Posiciones iniciales del jugador
	initPos.setX(0);
	initPos.setY(2);
	initPos.setZ(-10);
	check = false;
	

}

Client::~Client(){

    // Destruimos la interfaz del cliente
	peer->Shutdown(300);
    RakNet::RakPeerInterface::DestroyInstance(peer);

	//delete player;
	//delete motor;
	//delete IPGlob;
    
	instancia = nullptr;
}

void Client::Init(){

	peer = RakNet::RakPeerInterface::GetInstance();

    // Inicializamos el cliente con un maximo de 6 jugadores
    peer->Startup(6,&sd, 1);
    isServer = false;

}

void Client::setIP(){

	motor = GraphicsEngine::getInstancia();

    // Mostramos mensaje y esperamos a que se introduzca el servidor
    printf("Escribe por consola la IP o pulsa 0 para utilizar 127.0.0.1\n");
    //std::cin >> str;

	str = "127.0.0.1";

    // Convertimos el string en char
    char * IP = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), IP);
    IP[str.size()] = '\0';

    // Servidor por defecto al escribir 0
    if (IP[0]==0){
		strcpy(IP, "127.0.0.1");
	}
	IPGlob = IP;
    // Realizamos la conexion con la IP pasada y el puerto por defecto
    motor->addText(L"Starting the client.\n");
    peer->Connect(IP, SERVER_PORT, 0,0);

}

void Client::Update(){

	motor = GraphicsEngine::getInstancia();
	Game *game = Game::getInstancia();
	PhysicsEngine *bullet = PhysicsEngine::getInstancia();
	
    for (packet=peer->Receive(); packet; peer->DeallocatePacket(packet), packet=peer->Receive())
		{
			switch (packet->data[0])
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
                    {
					motor->addText(L"Our connection request has been accepted.\n");

					// Use a BitStream to write a custom user message
					// Bitstreams are easier to use than sending casted structures, and handle endian swapping automatically

				    }
					break;					
				case ID_NEW_INCOMING_CONNECTION:
					motor->addText(L"A connection is incoming.\n");
					break;
				case ID_NO_FREE_INCOMING_CONNECTIONS:
					motor->addText(L"The server is full.\n");
					break;
				case ID_DISCONNECTION_NOTIFICATION:
						motor->addText(L"We have been disconnected.\n");
					break;
				case ID_CONNECTION_LOST:
						motor->addText(L"Connection lost.\n");
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

				case Auxiliar::GameMessages::ID_SPAWN_PLAYER_CLIENT:
					{
					
					int id;
					int x;
					int y;
					int z;
					RakNet::BitStream bsIn(packet->data,packet->length,false);
					

					motor->addText(L"CREACION DE UN JUGADOR\n");
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(id);
					bsIn.Read(x);
					bsIn.Read(y);
					bsIn.Read(z);
					//Initpos se setea para que server cree el vector de jugadores
					initPos.setX(x);
					initPos.setY(y);
					initPos.setZ(z);
					
					//std::cout << "Pos iniciales: " << x<<", "<< y << ", " <<z<< std::endl;
					player = new JugadorRed(glm::vec3(x,y,z), x, z, id, "JugadorRed");
					player->InitCollide(bullet->getWorld());
					
					////std::cout << "ID Jugador: " << player->getCoche()->getID() << std::endl;
    				////std::cout << "Nombre Jugador: " << player->getCoche()->getName() << std::endl;
    				////std::cout << "Angulo Jugador: " << player->getAngle() << std::endl; 

					RakNet::BitStream bsOut;

					bsOut.Write((RakNet::MessageID)Auxiliar::GameMessages::ID_SPAWN_PLAYER_SERVER);
					bsOut.Write(initPos);
					bsOut.Write(id);
					peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);

					initPos.setZ(initPos.getZ()+50);

					}
				break;

				case Auxiliar::GameMessages::ID_START_GAME:
					{
					RakNet::BitStream bsOut;
					bsOut.Write((RakNet::MessageID)Auxiliar::GameMessages::ID_WAITING_PLAYER);
					peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);
					// Cambiamos el estado del juego al de red
					game->changeState(Auxiliar::GameStateRed);
					

					}
				break;


				case Auxiliar::GameMessages::ID_REFRESH_CLIENT:
					{
					int numPlayers=0;
					//cambiar a variable en el .h
					glm::vec3 pos;
					glm::vec3 rot;
					btScalar stering = player->getSteering();
					btScalar force = player->getEngineF();
					btScalar breakingbad = player->getbrakeForce();
					int comprobacion = 0;
					int ID = 0;
					RakNet::BitStream bsOut;
					RakNet::BitStream bsIn(packet->data,packet->length,false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					bsIn.Read(comprobacion);
					
					
						if(comprobacion==1){
							bsIn.Read(numPlayers);
							numPlayers--;
						if(players.capacity()!=numPlayers){
							PhysicsEngine *bullet = PhysicsEngine::getInstancia();
							std::vector<btRigidBody *> objects = bullet->getObjects();
							if(numPlayers>6){
								numPlayers=5;
							}
							players.reserve(numPlayers);
						
							for(int i=0; i<numPlayers;i++){
								//std::cout<<"entro"<<std::endl;
								bsIn.Read(ID);
							
								bsIn.Read(pos.x);
								bsIn.Read(pos.y);
								bsIn.Read(pos.z);
							
								bsIn.Read(rot.x);
								bsIn.Read(rot.y);
								bsIn.Read(rot.z);
								//std::cout<<"IDs: "<< ID<< std::endl;
								//std::cout<<"Pos x: "<< pos.x<< std::endl;
								//std::cout<<"Pos y: "<< pos.y<< std::endl;
								//std::cout<<"Pos z: "<< pos.z<< std::endl;
								if(ID!=player->getCoche()->getResource()->getID()){
								//std::cout<<"IDs: "<< ID<< std::endl;
								//std::cout <<"ID Player: "<< player->getCoche()->getResource()->getID() << std::endl;

								// PETA POR CONSTRUCTOR
								/*JugadorRed* apoyo= new JugadorRed(pos,pos.x, pos.z, ID, "JugadorRed");
								apoyo->InitCollide(bullet->getWorld());
								apoyo->getCoche()->setRotation(rot,0);
								players.push_back(apoyo);
								*/
								}
							}
							for(int i=0; i<players.size();i++){
								objects.push_back(players.at(i)->getBody());
							}
							bullet->setObjects(objects);
						}
						/*else{
							for(int i=0; i<players.size();i++){
								bsIn.Read(ID);
								bsIn.Read(pos.X);
								bsIn.Read(pos.Y);
								bsIn.Read(pos.Z);
							
								bsIn.Read(rot.X);
								bsIn.Read(rot.Y);
								bsIn.Read(rot.Z);
								if(players.at(i)->getCoche()->getID()==ID){ //mirar luego
									players.at(i)->getCoche()->setPosition(pos);
									players.at(i)->getCoche()->setRotation(rot);
								}
							
							}
						}*/
					}
					if(comprobacion==2){
						for(int i=0; i<players.size();i++){
						bsIn.Read(ID);
						if(players.at(i)->getCoche()->getResource()->getID() == ID){
							bsIn.Read(stering);
							bsIn.Read(force);
							bsIn.Read(breakingbad);
							players.at(i)->setSteering(stering);
							players.at(i)->setEngineF(force);
							players.at(i)->setBrakeForce(breakingbad);
						}
					}
					
					}
					// Leemos posiciones

					bsOut.Write((RakNet::MessageID)Auxiliar::GameMessages::ID_WAITING_PLAYER);
					peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);

					}
				break;
				
				case Auxiliar::GameMessages::ID_REFRESH_SERVER:
					{
					
					btScalar stering = player->getSteering();
					btScalar force = player->getEngineF();
					btScalar breakingbad = player->getbrakeForce();
					RakNet::BitStream bsIn(packet->data,packet->length,false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
					RakNet::BitStream bsOut;
					int comprobacion=0;
					if(!check){
					
					bsOut.Write((RakNet::MessageID)Auxiliar::GameMessages::ID_WAITING_PLAYER);
					peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);
					}
					else{
						if(players.empty()){
							glm::vec3 pos = player->getCoche()->getPosition();
							glm::vec3 rot = player->getCoche()->getRotation();
							comprobacion = 1;
							bsOut.Write((RakNet::MessageID)Auxiliar::GameMessages::ID_REFRESH_SERVER);
							bsOut.Write(comprobacion);
							bsOut.Write(player->getCoche()->getResource()->getID());
							bsOut.Write(pos.x);
							bsOut.Write(pos.y);
							bsOut.Write(pos.z);
							bsOut.Write(rot.x);
							bsOut.Write(rot.y);
							bsOut.Write(rot.z);
						}
						else{
							comprobacion = 2;
							bsOut.Write((RakNet::MessageID)Auxiliar::GameMessages::ID_REFRESH_SERVER);
							bsOut.Write(comprobacion);
							bsOut.Write(player->getCoche()->getResource()->getID());
							bsOut.Write(stering);
							bsOut.Write(force);
							bsOut.Write(breakingbad);
						}
						check=false;
						peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);
					}
					}
				break;

				
				default:
					motor->addText(L"Message with identifier %i has arrived.\n");
					motor->addText(irr::core::stringw(packet->data[0]));
					break;
				}
		}
}

void Client::refresh(JugadorRed* playerRefresh){
	
	// Le decimos al servidor que refresque el jugador
	player=playerRefresh;
	check = true;
	/*RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)Auxiliar::GameMessages::ID_REFRESH_SERVER);
	bsOut.Write(playerRefresh);
	//std::cout<<"refres : "<< std::endl;
	peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);*/

}