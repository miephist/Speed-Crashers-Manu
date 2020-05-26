#include "TriggerSystem.h"


TriggerSystem::TriggerSystem(){

    organizar = false;

}

void TriggerSystem::checkCollides(std::vector<Nitro*> nitros, Team *blue, Team *red){

    PhysicsEngine *bullet = PhysicsEngine::getInstancia();
	std::vector<btRigidBody *> objets = bullet->getObjects();

    // Obtenemos el numero de objetos a colisionar
    // Sera igual a 8 = 6 nitros + 1 coche + 1 pelota
	int numCollides = bullet->getWorld()->getDispatcher()->getNumManifolds();

	for(int i=0; i < numCollides; i++){

		// Obtenemos las dos colisiones que se producen
        btPersistentManifold *contact = bullet->getWorld()->getDispatcher()->getManifoldByIndexInternal(i);
        firstCollide = contact->getBody0();
        secondCollide = contact->getBody1();

        // Obtenemos los objetos colisionados
        firstNode = static_cast<ITResourceMesh *>(firstCollide->getUserPointer());
		secondNode = static_cast<ITResourceMesh *>(secondCollide->getUserPointer());
        
        // Si colisionan
        if(firstNode != 0 && secondNode != 0){
            for(int j = 0; j<blue->getPlayers().size();j++){
                 
               if(firstNode!=nullptr && blue->getPlayers().at(j)!=nullptr){

                    if(firstNode->getResource()->getID() == blue->getPlayers().at(j)->getCoche()->getResource()->getID()){
                        
                        collideNitro(blue->getPlayers().at(j),nitros);
                    }   
               }
            }
            for( int j = 0; j<red->getPlayers().size();j++){

                if(firstNode!=nullptr && blue->getPlayers().at(j)!=nullptr){

                    if(firstNode->getResource()->getID() == red->getPlayers().at(j)->getCoche()->getResource()->getID()){

                        collideNitro(red->getPlayers().at(j),nitros);
                    }
                }
            }
        }
	}

    // Comprobamos si se ha marcado gol y hay que actualizar respawns
    marcarGol(blue,red);
}


void TriggerSystem::collideNitro(Baseplayer *coche, std::vector<Nitro*> nitros){

    PhysicsEngine *bullet = PhysicsEngine::getInstancia();
	std::vector<btRigidBody *> objets = bullet->getObjects();
    CAudioEngine *aEngine= CAudioEngine::getInstancia();
    //Si el primer nodo es un jugador o una ia y el segundo un nitro ha habido colision
    if (strcmp("Jugador", firstNode->getResource()->getNickname()) == 0 || strcmp("JugadorIA", firstNode->getResource()->getNickname()) == 0)
    {
        if (strcmp("Nitro", secondNode->getResource()->getNickname()) == 0)
        {

            for(int i=0; i<6; i++){
                if(nitros.at(i)!=NULL){
                    if(nitros.at(i)->getNode()->getResource()->getID() == secondNode->getResource()->getID()){
                        if(coche->getCargas() < 3){
                            if(organizar == true){
                                // Despertamos los nitros
                                for(int j=0; j<6; j++){
                                    if(nitros.at(j)!=NULL){
                                        nitros.at(j)->awakeCollide();
                                    }
                                }
                                organizar = false;
                            }
                            
                            nitros.at(i)->Delete();
                            
                            coche->setCargas();

                            if(strcmp(coche->getCoche()->getResource()->getNickname(),"Jugador")==0){
                                dynamic_cast<Jugador*>(coche)->UpdateHud();
                            }
                            
                            aEngine->PlayEvent("event:/SFX/Coche/Recogernitro");

                        }

                        if(coche->getCargas() >= 3){
                            // Ponemos a dormir los nitros
                            for(int j=0; j<6; j++){
                                if(nitros.at(j)!=NULL){
                                    nitros.at(j)->sleepCollide();
                                }
                            }
                            organizar = true;
                        }
                    }
                }
            }
        }
    }
}


void TriggerSystem::marcarGol(Team *blue, Team *red){
    
    srand(time(NULL));

	PhysicsEngine *bullet = PhysicsEngine::getInstancia();
    Pelota *pelota = Pelota::getInstancia();
    CAudioEngine *aEngine= CAudioEngine::getInstancia();

    bool goal = false;
    std::stringstream ss;

    // Marcador azul
	if(pelota->getNode()->getPosition().z > Options::getInstancia()->getForwardScenario()+10){

        blue->addGoal();
        goal = true;

        ss << "media/Hud/Contador/" << blue->getScore() << ".png";

        ITEngine::getInstancia()->getHud("GameHud")->deleteElement("Marcador Azul");
        ITEngine::getInstancia()->getHud("GameHud")->addElement("Marcador Azul", ss.str().c_str());
        ITEngine::getInstancia()->getHud("GameHud")->scaleElement("Marcador Azul",0.9,0.9);
        ITEngine::getInstancia()->getHud("GameHud")->traslateElement("Marcador Azul", -0.245, 1.03);

    //Marcador rojo
	}else if(pelota->getNode()->getPosition().z < -Options::getInstancia()->getForwardScenario()-10){
        red->addGoal();
        goal = true;

        ss << "media/Hud/Contador/" << red->getScore() << ".png";

        ITEngine::getInstancia()->getHud("GameHud")->deleteElement("Marcador Rojo");
        ITEngine::getInstancia()->getHud("GameHud")->addElement("Marcador Rojo", ss.str().c_str());
        ITEngine::getInstancia()->getHud("GameHud")->scaleElement("Marcador Rojo",0.9,0.9);
        ITEngine::getInstancia()->getHud("GameHud")->traslateElement("Marcador Rojo", 0.245, 1.03);
        
    }

    // Si se ha marcado gol realizamos los respawns
    if(goal == true){
        // Evento de sonido
        aEngine->PlayEvent("event:/SFX/Pelota/Gol");
        int voz = rand()%4;
        switch (voz){
            case 0:
                aEngine->PlayEvent("event:/Voces/Personaje1/Wow");
            break; 
            case 1:
                aEngine->PlayEvent("event:/Voces/Personaje1/MenudoGol");
            break;
            case 2:
                aEngine->PlayEvent("event:/Voces/Personaje4/DurarEsto");
            break;
            case 3:
                aEngine->PlayEvent("event:/Voces/Personaje4/FacilJuego");
            break;
            
        }
        // Respawns
        pelota->InitCollide(bullet->getWorld());
        blue->respawn();
        red->respawn();
        Options::getInstancia()->setStartTimer(glfwGetTime());
    }
}