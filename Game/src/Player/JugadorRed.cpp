#include "JugadorRed.h"

JugadorRed::JugadorRed(glm::vec3 initPos, int posx, int posz,int idNew,std::string name):Baseplayer(posx,posz,idNew,name){

    controles.push_back(GLFW_KEY_W);
    controles.push_back(GLFW_KEY_S);
    controles.push_back(GLFW_KEY_A);
    controles.push_back(GLFW_KEY_D);

}


/////////////////////////////////////
//////      DESTRUCTORES       //////
/////////////////////////////////////

JugadorRed::~JugadorRed(){
   
}

void JugadorRed::updateWheels(){
    
    Pelota *pelota = Pelota::getInstancia();

    btTransform ruedas= vehicle->getWheelTransformWS(0);

    wheelUL->setPosition(ruedas.getOrigin().getX(),ruedas.getOrigin().getY()-0.33,ruedas.getOrigin().getZ());

    //btVector3 axis = btVector3(ruedas.getRotation().getAxis().getX(),ruedas.getRotation().getAxis().getY(),ruedas.getRotation().getAxis().getZ());
    //btScalar angle = ruedas.getRotation().getAngle() * irr::core::RADTODEG;

    //wheelUL->setRotation(irr::core::vector3df(axis.getX(), axis.getY(), axis.getZ()));

    ruedas = vehicle->getWheelTransformWS(1);
    
    wheelUR->setPosition(ruedas.getOrigin().getX(),ruedas.getOrigin().getY()-0.33,ruedas.getOrigin().getZ());
    // wheelUR->setRotation(irr::core::vector3df(ruedas.getRotation().getX(),ruedas.getRotation().getY(),ruedas.getRotation().getZ()));
    
    ruedas = vehicle->getWheelTransformWS(2);

    wheelDL->setPosition(ruedas.getOrigin().getX(),ruedas.getOrigin().getY()-0.33,ruedas.getOrigin().getZ());
    // wheelDL->setRotation(irr::core::vector3df(ruedas.getRotation().getX(),ruedas.getRotation().getY(),ruedas.getRotation().getZ()));
    
    ruedas = vehicle->getWheelTransformWS(3);

    wheelDR->setPosition(ruedas.getOrigin().getX(),ruedas.getOrigin().getY()-0.33,ruedas.getOrigin().getZ());
    // wheelDR->setRotation(irr::core::vector3df(ruedas.getRotation().getX(),ruedas.getRotation().getY(),ruedas.getRotation().getZ()));
    
    // Updateamos angulo de la camara en funcion de las ruedas y del vehiculo una vez ya estas seteadas sus posiciones y rotaciones
    angle = atan2f( wheelUR->getPosition().x - vehicle->getRigidBody()->getCenterOfMassPosition().x(),
              wheelUR->getPosition().z - vehicle->getRigidBody()->getCenterOfMassPosition().z());
    angle += 225*M_PI/180;

    // Updatemos angulo de la camara en funcion de la pelota
    angleCamera = atan2f(pelota->getNode()->getPosition().x -  vehicle->getRigidBody()->getCenterOfMassPosition().x(),
            pelota->getNode()->getPosition().z -  vehicle->getRigidBody()->getCenterOfMassPosition().z() );
    angleCamera += 180 * M_PI/180;

    if(angle < 0)
        angle += 2*M_PI;

    if(angle > 2*M_PI)
        angle -= 2*M_PI;
    
    if(pelota->getNode()->getPosition().y > 15){
        relativePelotaHeight = 15;
    }else{
        relativePelotaHeight = pelota->getNode()->getPosition().y;
    }
        cameraHeight =  relativePelotaHeight / 15;

    //angulo camara
    angle = angle * 180 / M_PI; //pasamos a angulos para facilidad de trabajo
    lastAngle = lastAngle * 180 / M_PI;

    if(angle < 0)
        angle -= 360;

    if(angle >360)
        angle -= 360;


    if(abs(lastAngle - angle)<8){ //si la diferencia de angulos es de menos de 1 grado se igualan
        lastAngle =  angle;
    }else{
        if(angle < lastAngle){
            if(lastAngle - 180 < angle){//si la diferencia es de 180 o mas es porque hay que girar en la otra direccion
                lastAngle -= angleRotationCamera;
            }else{
                lastAngle += angleRotationCamera;
            }
        }else{
            if(angle > lastAngle){
                if(lastAngle + 180 > angle){
                    lastAngle += angleRotationCamera;
                }else{
                    lastAngle -= angleRotationCamera;
                }
            }
        }
    
        angle = lastAngle;

    }

    
    if(lastAngle < 0){
        lastAngle += 360;
    }else{
        if(lastAngle > 360){
            lastAngle -= 360;
        }
    }
    
    angle = angle / 180 * M_PI; //devolvemos a radianes 
    lastAngle = lastAngle / 180 * M_PI;

}


/////////////////////////////////////
//////       MECANICAS         //////
/////////////////////////////////////
void JugadorRed::movementServer(){

    vehicle-> setSteeringValue ( btScalar ( steeringValue ), 0 );
    vehicle-> setSteeringValue ( btScalar ( steeringValue ), 1 );

    vehicle->applyEngineForce(engineForce, 2);
    vehicle->setBrake(brakeForce, 2);
    vehicle->applyEngineForce(engineForce, 3);
    vehicle->setBrake(brakeForce, 3);
}

void JugadorRed::movement(){

    PhysicsEngine *bullet = PhysicsEngine::getInstancia();
    //CAudioEngine *aEngine = CAudioEngine::getInstancia();
    Pelota *pelota = Pelota::getInstancia();

	bool out = false;

        if(glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS){
            // Cerrar ventana
        }
    
        // Salto del personaje
        if(glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && salto > 0){

                //aEngine->PlayEvent("event:/SFX/Coche/salto_coche");
          
                bodyCollideChassis->applyCentralImpulse(btVector3(0,15500,0));
                 
                //receiver->setBoolean(true);

            if(salto == 1){
                doblesalto();
            }

            salto --;
        }
        
        // Comprobamos movimiento del jugador (W,A,S,D)
        out = checkMovement();

        vehicle-> setSteeringValue ( btScalar ( steeringValue ), 0 );
        vehicle-> setSteeringValue ( btScalar ( steeringValue ), 1 );

        if(!powerNitro){

            // Velocidad del jugador normal
            vehicle->applyEngineForce(engineForce + vNitro, 2);
            vehicle->setBrake(brakeForce + vNitro, 2);
            vehicle->applyEngineForce(engineForce + vNitro, 3);
            vehicle->setBrake(brakeForce + vNitro, 3);
        }else{

            // Velocidad del jugador con el poder del nitro
            vehicle->applyEngineForce(engineForce + vMaxNitro, 2);
            vehicle->setBrake(brakeForce + vNitro, 2);
            vehicle->applyEngineForce(engineForce + vMaxNitro, 3);
            vehicle->setBrake(brakeForce + vNitro, 3);
        }

        // Nitro
        if(glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_N) == GLFW_PRESS &&  vNitro < 500){
            if(cargas > 0){
                //if(!aEngine->IsEventPlaying("event:/SFX/Coche/iniciar_nitro"))
                    //aEngine->PlayEvent("event:/SFX/Coche/iniciar_nitro");
                    
                vNitro = vMaxNitro;
                
                cargas -= 1;
            }else{
                //if(!aEngine->IsEventPlaying("event:/SFX/Coche/clicknitro"))
                    //aEngine->PlayEvent("event:/SFX/Coche/clicknitro");
            }
            out = true;
        }

        // Decrecemos velocidad del coche mientras este en uso el nitro
        if(vNitro >0){
            vNitro -= 20;

            if(vNitro<0)
                vNitro = 0;
        }


        if(!out){
            steeringValue=0;
            engineForce=0;
            vehicle-> applyEngineForce ( engineForce , 2 );
            vehicle-> applyEngineForce ( engineForce , 3 );
        
            vehicle-> setSteeringValue ( steeringValue, 0 );
            vehicle-> setSteeringValue ( steeringValue, 1 );	
            brakeForce=200;
            vehicle->setBrake(brakeForce, 2);
            vehicle->setBrake(brakeForce, 3);
        }
        //true si rueda en contacto con algo
        contact=vehicle->getWheelInfo(1).m_raycastInfo.m_isInContact;

}

bool JugadorRed::checkMovement(){

    bool out = false;

    // Pulsa A
    if(glfwGetKey(ITEngine::getInstancia()->getWindow(), controles.at(2)) == GLFW_PRESS){

        if(vehicle->getCurrentSpeedKmHour() > 150){
             steeringValue = -0.1f;
        }else if ( vehicle->getCurrentSpeedKmHour() > 100 &&  vehicle->getCurrentSpeedKmHour() <= 150){
             steeringValue = -0.2f;
        }else if ( vehicle->getCurrentSpeedKmHour() >= 50 &&  vehicle->getCurrentSpeedKmHour() <= 100){
             steeringValue = -0.3f;
        }else if ( vehicle->getCurrentSpeedKmHour() < 50){
             steeringValue = -0.4f;
        }

        out = true;

    }else{
        // Pulsa D
        if(glfwGetKey(ITEngine::getInstancia()->getWindow(), controles.at(3)) == GLFW_PRESS){
            if(vehicle->getCurrentSpeedKmHour() > 150){
                 steeringValue = 0.1f;
            }else if ( vehicle->getCurrentSpeedKmHour() > 100 &&  vehicle->getCurrentSpeedKmHour() <= 150){
                 steeringValue = 0.2f;
            }else if ( vehicle->getCurrentSpeedKmHour() >= 50 &&  vehicle->getCurrentSpeedKmHour() <= 100){
                 steeringValue = 0.3f;
            }else if ( vehicle->getCurrentSpeedKmHour() < 50){
                 steeringValue = 0.4f;
            }

            out = true;
        }else{
             steeringValue = 0.0f;
        }
    }

    // Pulsa W
    if (glfwGetKey(ITEngine::getInstancia()->getWindow(), controles.at(0)) == GLFW_PRESS){
        if( vehicle->getCurrentSpeedKmHour() <  maxSpeed){             
             engineForce = 10000.0f;
             brakeForce = 0.0f;
        }
        out = true;
    }else{
        // Pulsa S
        if(glfwGetKey(ITEngine::getInstancia()->getWindow(), controles.at(1)) == GLFW_PRESS){
            if( vehicle->getCurrentSpeedKmHour() > - maxSpeed/2){ 
                 brakeForce = 650.0f;
                 engineForce = -5000.0f;
            }
            out = true;
        }
    }

    return out;

}


bool JugadorRed::doblesalto(){
    PhysicsEngine *bullet = PhysicsEngine::getInstancia();

    if(glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_W) == GLFW_PRESS){
                bodyCollideChassis->applyCentralImpulse(btVector3(0,-16000,0));
                btVector3 n = bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(0,0,2500));
                bodyCollideChassis->applyCentralImpulse(n);
                btVector3 m = bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(4000,0,0));
                bodyCollideChassis->applyTorqueImpulse(m);
                salto --;
        return true;
    }

    if(glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_S) == GLFW_PRESS){
                bodyCollideChassis->applyCentralImpulse(btVector3(0,-15000,0));
                btVector3 n = bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(0,0,-2500));
                bodyCollideChassis->applyCentralImpulse(n);
                btVector3 m = bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(-4000,0,0));
                bodyCollideChassis->applyTorqueImpulse(m);
                salto --;
        return true;
    }

    if(glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_A) == GLFW_PRESS){
                bodyCollideChassis->applyCentralImpulse(btVector3(0,-15000,0));
                btVector3 n = bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(-3000,0,0));
                bodyCollideChassis->applyCentralImpulse(n);
                btVector3 m = bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(0,0,4000));
                bodyCollideChassis->applyTorqueImpulse(m);
                salto --;
        return true;
    }

    if(glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_D) == GLFW_PRESS){
                bodyCollideChassis->applyCentralImpulse(btVector3(0,-15000,0));
                btVector3 n = bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(5000,0,0));
                bodyCollideChassis->applyCentralImpulse(n);
                btVector3 m = bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(0,0,-4000));
                bodyCollideChassis->applyTorqueImpulse(m);
                salto --;
        return true;
    }

    if(glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS){

            //CAudioEngine *aEngine = CAudioEngine::getInstancia();

                //aEngine->PlayEvent("event:/SFX/Coche/salto_coche");

                bodyCollideChassis->applyCentralImpulse(btVector3(0,-5000,0));
                btVector3 n = bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(0,0,0));
                bodyCollideChassis->applyCentralImpulse(n);
                btVector3 m = bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(0,0,0));
                bodyCollideChassis->applyTorqueImpulse(m);
                salto --;
        return true;
    }
    return false;
}

void JugadorRed::calculateSpeed(){
    speed= sqrt(pow(lastPos.x - coche->getPosition().x, 2.0f) + pow(lastPos.z - coche->getPosition().z, 2.0f));
    speed = speed*10000 / (glfwGetTime() - timer);

    timer = glfwGetTime();
    lastPos = coche->getPosition();
    maxSpeedPercentage = speed / maxSpeed;		
    if(maxSpeedPercentage > 1){		
        maxSpeedPercentage = 1;		
    }

}