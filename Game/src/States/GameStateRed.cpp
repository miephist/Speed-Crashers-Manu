#include "GameStateRed.h"

GameStateRed::GameStateRed(){

    Init();

}

GameStateRed::~GameStateRed(){


}

void GameStateRed::Init(){

    /*
    
    // Cargamos el nodo del campo
    GraphicsEngine::getInstancia()->setCampo();

    collide = new TriggerSystem();

    bullet = PhysicsEngine::getInstancia();

    // Cargamos el mundo y le damos una gravedad
    bullet->setWorld("Campo_muro2.bullet");

    client = Client::getInstancia();

    player = client->getPlayer();

    gEngine = GraphicsEngine::getInstancia();

    // Ocultamos el cursor
    gEngine->getDevice()->getCursorControl()->setVisible(false);

    // Inicializamos la interfaz
    // Creamos el texto para las pruebas        
    text = L"Datos del jugador:\n";
	irr::gui::IGUIFont *font = gEngine->getInterface()->getFont("fonts/fontcourier.bmp");
	textoUI = gEngine->getInterface()->addStaticText(
		text.c_str(),				                    // Texto
		irr::core::rect<irr::s32>(10, 10, 260, 400),    // Rectangulo de los bordes
		false,						                    // Mostrar bordes
		true,						                    // Cortar en varias lineas
		0,							                    // Nodo padre
		0,					                            // Id del elemento
		true);						                    // Rellenado (o transparente)
    textoUI->setOverrideFont(font);

    // Seteamos el texto
    gEngine->createText(textoUI, text);

    // FPS juego
    lastFPS = -1;

    // Iniciamos el temporizador con irrlicht
    // TimeStamp
    then = glfwGetTime();

    // Seteamos el recibidor del juego
    receiver = Receiver::getInstancia();
    gEngine->getDevice()->setEventReceiver(receiver);

    */

}


void GameStateRed::Update(){

    /*

    if(gEngine->getDevice()->isWindowActive()){
        
        receiver->Finalizado();

        // Actualiza temporizador
        int now = glfwGetTime() * 1000 - then;
        then = glfwGetTime() * 1000;

        // Actualiza fisicas
        Render(now);

        // Actualiza jugador
        player->movement();
        player->updateWheels();
        // Calcula la velocidad
        player->calculateSpeed();

        //Enviar Info de jugador
        client->Update();
        client->refresh(player);

        players = client->getPlayers(); 
        UpdatePlayersWheels();
        //Recibir info jugador X

        //Actualizar X jugadores (vector de jugadores)

        // Actualiza camara
        Camera::getInstancia()->updateCamera(
        player->getAngle(),
        player->getAngleCamera(),
        player->getCoche(),
        player->getCameraHeight());

        gEngine->getDriver()->beginScene(true, true, irr::video::SColor(255,113,113,133));

        gEngine->getScene()->drawAll();

        int fps = gEngine->getDriver()->getFPS();

        if (lastFPS != fps){

            irr::core::stringw tmp(L"Speed Crashers [");
            tmp += gEngine->getDriver()->getName();
            tmp += L"] fps: ";
            tmp += fps;

            gEngine->getDevice()->setWindowCaption(tmp.c_str());
            lastFPS = fps;
        }

        gEngine->getDriver()->endScene();


    }else{

        gEngine->getDevice()->yield();

    }

    receiver->Iniciado();

    // Actualizamos servidor
    // client->refresh(player);

    //server->refreshServer();

    */

}

void GameStateRed::Render(int TDeltaTime){

    /*

    // UpdatePhysics y UpdateRender
    PhysicsEngine *bullet = PhysicsEngine::getInstancia();
	btDynamicsWorld *mundo = bullet->getWorld();
	mundo->stepSimulation(TDeltaTime * 0.001f, 60);

    std::vector<btRigidBody *> objects = bullet->getObjects();

	for(int i=0; i<objects.size(); i++) {
		
		UpdateRender(objects.at(i));
	}	
    */
}

void GameStateRed::UpdateRender(btRigidBody *TObject) {

    /*
	
	irr::scene::ISceneNode *Node = static_cast<irr::scene::ISceneNode *>(TObject->getUserPointer());

	// Cambiamos la posicion
	btVector3 Point = TObject->getCenterOfMassPosition();
	
	if(strcmp(Node->getName(),"JugadorRed") == 0){
        for(int i=0; i < players.size(); i++){
        if(Node->getID()==players.at(i)->getCoche()->getID()){
            TObject = players.at(i)->getBody();
            Node = static_cast<irr::scene::ISceneNode *>(TObject->getUserPointer());
            Point = TObject->getCenterOfMassPosition();
        }
       
    
	    Node->setPosition(irr::core::vector3df((irr::f32)Point[0],(irr::f32)Point[1]+1,(irr::f32)Point[2]));
       
    }
    else
	    Node->setPosition(irr::core::vector3df((irr::f32)Point[0],(irr::f32)Point[1],(irr::f32)Point[2]));
    // Inicializamos la posicion de la camara
    irr::core::vector3df nodePositionCamera;
    
	// Cambiamos la rotacion
	irr::core::vector3df Euler;
	const btQuaternion& TQuat = TObject->getOrientation();
	irr::core::quaternion q(TQuat.getX(), TQuat.getY(), TQuat.getZ(), TQuat.getW());
	q.toEuler(Euler);
	Euler *= irr::core::RADTODEG;
	Node->setRotation(Euler);

    */

}

void GameStateRed::UpdatePlayersWheels(){

    /*

    std::vector<btRigidBody *> objects = bullet->getObjects();
    
	
		
    for(int j=0; j < players.size();j++){
		
        players.at(j)->movementServer();
            
    }
		
    for(int i=0; i < players.size();i++){
        if(players.at(i)!=nullptr && players.at(i)->getCoche()->getID()!=player->getCoche()->getID()){
            
            players.at(i)->updateWheels();
        }
    }

    */
}