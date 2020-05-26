
#include "Jugador.h"

/////////////////////////////////////
//////      CONSTRUCTORES      //////
/////////////////////////////////////

Jugador::Jugador(int posx,int posz,int idNew,std::string name, char pant):Baseplayer(posx, posz, idNew, name){

    targeto= ITEngine::getInstancia()->createPivote(coche->getNode());

    targeto->setPosition(glm::vec3(0,0,10));

    poderes = new Powers();

    pressed = false;
    
    checked = false;

    pantalla = pant;

    controles.push_back(GLFW_KEY_W);
    controles.push_back(GLFW_KEY_S);
    controles.push_back(GLFW_KEY_A);
    controles.push_back(GLFW_KEY_D);
    bullet = PhysicsEngine::getInstancia();
    aEngine = CAudioEngine::getInstancia();
    Pelota *pelota = Pelota::getInstancia();
    timer = 0;
    timer2 = 0;
    timerspeed= 0;

    // Joystick
    oldState = GLFW_RELEASE;
    newState = -1;

    oldState2 = GLFW_RELEASE;
    newState2 = -1;

    oldState3 = GLFW_RELEASE;
    newState3 = -1;

    erase = false;
}

/////////////////////////////////////
//////      DESTRUCTORES       //////
/////////////////////////////////////

Jugador::~Jugador(){

    delete poderes;

}


void Jugador::updateWheels(){
    
    Pelota *pelota = Pelota::getInstancia();

    btTransform ruedas = vehicle->getWheelTransformWS(0);

    wheelUL->setPosition(glm::vec3(ruedas.getOrigin().getX(),ruedas.getOrigin().getY()+0.1,ruedas.getOrigin().getZ()));

    btVector3 axis = btVector3(ruedas.getRotation().getAxis().getX(),ruedas.getRotation().getAxis().getY(),ruedas.getRotation().getAxis().getZ());
    btScalar angle = ruedas.getRotation().getAngle() * (180.0f / M_PI);

    wheelUL->setRotation(glm::vec3(axis.getX(), axis.getY(), axis.getZ()), angle);

    ruedas = vehicle->getWheelTransformWS(1);
    
    wheelUR->setPosition(glm::vec3(ruedas.getOrigin().getX(),ruedas.getOrigin().getY()+0.1,ruedas.getOrigin().getZ()));
    // wheelUR->setRotation(irr::core::vector3df(ruedas.getRotation().getX(),ruedas.getRotation().getY(),ruedas.getRotation().getZ()));
    wheelUR->setRotation(glm::vec3(axis.getX(), axis.getY(), axis.getZ()), angle);
    ruedas = vehicle->getWheelTransformWS(2);

    wheelDL->setPosition(glm::vec3(ruedas.getOrigin().getX(),ruedas.getOrigin().getY()+0.1,ruedas.getOrigin().getZ()));
    // wheelDL->setRotation(irr::core::vector3df(ruedas.getRotation().getX(),ruedas.getRotation().getY(),ruedas.getRotation().getZ()));
    wheelDL->setRotation(glm::vec3(axis.getX(), axis.getY(), axis.getZ()), angle);
    ruedas = vehicle->getWheelTransformWS(3);

    wheelDR->setPosition(glm::vec3(ruedas.getOrigin().getX(),ruedas.getOrigin().getY()+0.1,ruedas.getOrigin().getZ()));
    // wheelDR->setRotation(irr::core::vector3df(ruedas.getRotation().getX(),ruedas.getRotation().getY(),ruedas.getRotation().getZ()));
    wheelDR->setRotation(glm::vec3(axis.getX(), axis.getY(), axis.getZ()), angle);
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

void Jugador::movement(Baseplayer* enemigo){

    // Parametros mando
    bool controller = false;
    const float* axes = nullptr;
    const unsigned char* buttons = nullptr;
    const char* name = nullptr;

	bool out = false;

    if(glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(ITEngine::getInstancia()->getWindow(), GLFW_TRUE);
    }
    // Comprobamos si se conecta un mando
    if(glfwJoystickPresent(GLFW_JOYSTICK_1) == 1){
        // Contador para los ejes
        int axesCount;
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

        // Contador para los botones
        int buttonsCount;
        buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonsCount);

        // Guardamos el nombre
        name = glfwGetJoystickName(GLFW_JOYSTICK_1);

        // Indicamos que el controlador/pad esta activo
        controller = true;

        newState = buttons[0];
    }
        

    // Salto del personaje
    if(((glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && pantalla == 't') || (newState == GLFW_RELEASE && oldState == GLFW_PRESS && pantalla == 'm')) && pressed==false && salto > 0){

            pressed = true;
            
            aEngine->PlayEvent("event:/SFX/Coche/salto_coche");
        
            bodyCollideChassis->applyCentralImpulse(btVector3(0,15500,0));
 
                
        if(salto == 1){
            doblesalto(controller, buttons, axes);
        }
        
        salto --;          
        timer = glfwGetTime();
        timer2=glfwGetTime();

    }
    else if(glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_SPACE) == GLFW_RELEASE){

        pressed = false;

    }

    // Reiniciamos estados de la X
    oldState = newState;

    // Comprobamos movimiento del jugador (W,A,S,D)
    out = checkMovement(controller, buttons, axes);
    //Uso de poderes
    if((((glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_P) == GLFW_PRESS) && pantalla == 't' ) || ((controller && GLFW_PRESS == buttons[3]) && pantalla == 'm')) || (poderes->getActivo())){
        checked = false;
        
        if(poderes->getText()=="NitroUp"){
            poderes->activePower(this);
            checked = true;
        }
        else if(checked == false){
            poderes->activePower(enemigo);
        }
    }

    poderes->updateHUDPowers(pantalla);

    vehicle->setSteeringValue(btScalar(steeringValue), 0);
    vehicle->setSteeringValue(btScalar(steeringValue), 1);

    int cont = 0;
    for(unsigned int i = 0; i < vehicle->getNumWheels(); i++){
        if(vehicle->getWheelInfo(i).m_raycastInfo.m_isInContact){
            cont++;
        }
    }
 
    if(cont == 4 && glfwGetTime() - timer2 >= 0.7){
        contact = true;
        
    }else{
        contact = false;
        engineForce = 0;
    }

    if(!powerNitro){

        // Velocidad del jugador normal
            vehicle->applyEngineForce( engineForce +  vNitro, 2);
            vehicle->setBrake( brakeForce +  vNitro, 2);
            vehicle->applyEngineForce( engineForce +  vNitro, 3);
            vehicle->setBrake( brakeForce +  vNitro, 3);
    }else{

        // Velocidad del jugador con el poder del nitro
            vehicle->applyEngineForce( engineForce +  vMaxNitro, 2);
            vehicle->setBrake( brakeForce +  vNitro, 2);
            vehicle->applyEngineForce( engineForce +  vMaxNitro, 3);
            vehicle->setBrake( brakeForce +  vNitro, 3);
    }

    // Nitro
    if(((glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_N) == GLFW_PRESS && pantalla == 't') || ((controller && GLFW_PRESS == buttons[1]) && pantalla == 'm')) && vNitro < 500){
       
        if( cargas > 0){
            if(!aEngine->IsEventPlaying("event:/SFX/Coche/iniciar_nitro"))
                aEngine->PlayEvent("event:/SFX/Coche/iniciar_nitro");
                
                vNitro =  vMaxNitro;
            
                cargas -= 1;
                UpdateHud();
        }else{
            if(!aEngine->IsEventPlaying("event:/SFX/Coche/clicknitro"))
                aEngine->PlayEvent("event:/SFX/Coche/clicknitro");
        }
        out = true;
    }

    // Decrecemos velocidad del coche mientras este en uso el nitro
    if( vNitro >0){
            vNitro -= 20;

        if( vNitro<0)
                vNitro = 0;
    }

    // DEBUG

    // CAMBIAR A MODO DEBUG    
    newState2 = glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_M);

    if(newState2 == GLFW_RELEASE && oldState2 == GLFW_PRESS && !ITEngine::getInstancia()->getIsDebugActive()){

        ITEngine::getInstancia()->setActiveHud("DebugHud");
        ITEngine::getInstancia()->setDebug(true);

    }else if(newState2 == GLFW_RELEASE && oldState2 == GLFW_PRESS && ITEngine::getInstancia()->getIsDebugActive()){

        if(!Options::getInstancia()->getCoop()){
            ITEngine::getInstancia()->setActiveHud("GameHud");
        }else{
            ITEngine::getInstancia()->setActiveHud("GameHudCoop");
        }

        ITEngine::getInstancia()->setDebug(false);

    }

    oldState2 = newState2;


    // OCULTAR LEYENDA
    newState3 = glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_Z);

    if(ITEngine::getInstancia()->getIsDebugActive()){
        if(newState3 == GLFW_RELEASE && oldState3 == GLFW_PRESS){
            if(erase == false){
                ITEngine::getInstancia()->getHud("DebugHud")->deleteElement("Leyenda");
                erase = true;
            }else{
                ITEngine::getInstancia()->getHud("DebugHud")->addElement("Leyenda", "media/Hud/Debug/Leyenda.png");
                ITEngine::getInstancia()->getHud("DebugHud")->scaleElement("Leyenda",0.5,0.5);
                ITEngine::getInstancia()->getHud("DebugHud")->traslateElement("Leyenda", -1.55, 0.6);
                erase = false;
            }
        }
    }

    oldState3 = newState3;

    // FIN DEBUG


    if(!out){
            vehicle->applyEngineForce ( 0 , 2 );
            vehicle->applyEngineForce ( 0 , 3 );
        
            vehicle->setSteeringValue ( 0, 0 );
            vehicle->setSteeringValue ( 0, 1 );	

            vehicle->setBrake(200, 2);
            vehicle->setBrake(200, 3);
    }


    if(contact && glfwGetTime() - timer >= 0.7&& salto<=1 ){

        setSalto(2);
        
    }  

}

bool Jugador::checkMovement(bool controller, const unsigned char* buttons, const float* axes){

    bool out = false;

    // Pulsa A
    if((glfwGetKey(ITEngine::getInstancia()->getWindow(), controles.at(3)) == GLFW_PRESS && pantalla == 't') || ((controller && (GLFW_PRESS == buttons[14] || 0.5f <= axes[0]) && pantalla == 'm'))){

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
        if((glfwGetKey(ITEngine::getInstancia()->getWindow(), controles.at(2)) == GLFW_PRESS && pantalla == 't') || ((controller && (GLFW_PRESS == buttons[12] || -0.5f >= axes[0]) && pantalla == 'm'))){
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
    if((glfwGetKey(ITEngine::getInstancia()->getWindow(), controles.at(0)) == GLFW_PRESS && pantalla == 't') || ((controller && -0.5f <= axes[5]) && pantalla == 'm')){
        if( vehicle->getCurrentSpeedKmHour() <  maxSpeed){             
             engineForce = 12000.0f;
             brakeForce = 0.0f;
        }
        out = true;
    }else{
        // Pulsa S
        if((glfwGetKey(ITEngine::getInstancia()->getWindow(), controles.at(1)) == GLFW_PRESS && pantalla == 't') || ((controller && -0.5f <= axes[2]) && pantalla == 'm')){
            if(vehicle->getCurrentSpeedKmHour() > -1*(maxSpeed/2)){ 
                 brakeForce = 0.0f;
                 engineForce = -15000.0f;
            }
            out = true;
        }
    }

    return out;

}


bool Jugador::doblesalto(bool controller, const unsigned char* buttons, const float* axes){

    if((glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_W) == GLFW_PRESS && pantalla == 't') || ((controller && -0.5f >= axes[1]) && pantalla == 'm')){
                bodyCollideChassis->applyCentralImpulse(btVector3(0,-16000,0));
                btVector3 n =  bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(0,0,2500));
                bodyCollideChassis->applyCentralImpulse(n);
                btVector3 m =  bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(4000,0,0));
                bodyCollideChassis->applyTorqueImpulse(m);
                salto --;
        return true;
    }

    if((glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_S) == GLFW_PRESS && pantalla == 't') || ((controller && 0.5f <= axes[1]) && pantalla == 'm')){
                bodyCollideChassis->applyCentralImpulse(btVector3(0,-15000,0));
                btVector3 n =  bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(0,0,-2500));
                bodyCollideChassis->applyCentralImpulse(n);
                btVector3 m =  bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(-4000,0,0));
                bodyCollideChassis->applyTorqueImpulse(m);
                salto --;
        return true;
    }

    if((glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_A) == GLFW_PRESS && pantalla == 't') || ((controller && -0.5f >= axes[0]) && pantalla == 'm')){
                bodyCollideChassis->applyCentralImpulse(btVector3(0,-15000,0));
                btVector3 n =  bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(5000,0,0));
                bodyCollideChassis->applyCentralImpulse(n);
                btVector3 m =  bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(0,0,-4000));
                bodyCollideChassis->applyTorqueImpulse(m);
                salto --;
                
        return true;
    }

    if((glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_D) == GLFW_PRESS && pantalla == 't') || ((controller && 0.5f <= axes[0]) && pantalla == 'm')){
                bodyCollideChassis->applyCentralImpulse(btVector3(0,-15000,0));
                btVector3 n =  bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(-3000,0,0));
                bodyCollideChassis->applyCentralImpulse(n);
                btVector3 m =  bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(0,0,4000));
                bodyCollideChassis->applyTorqueImpulse(m);
                salto --;
        return true;
    }

    if((glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && pantalla == 't' ) || ((controller && GLFW_PRESS == buttons[0]) && pantalla == 'm')){


                aEngine->PlayEvent("event:/SFX/Coche/salto_coche");

                bodyCollideChassis->applyCentralImpulse(btVector3(0,-5000,0));
                btVector3 n =  bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(0,0,0));
                bodyCollideChassis->applyCentralImpulse(n);
                btVector3 m =  bodyCollideChassis->getWorldTransform().getBasis()*(btVector3(0,0,0));
                bodyCollideChassis->applyTorqueImpulse(m);
                salto --;
        return true;
    }

    return false;
}

void Jugador::calculateSpeed(){

    speed= sqrt(pow(lastPos.x -  coche->getPosition().x, 2.0f) + pow( lastPos.z -  coche->getPosition().z, 2.0f));
    speed =  speed*10000 / (glfwGetTime() -  timerspeed);

    timerspeed = glfwGetTime();
    lastPos =  coche->getPosition();
    maxSpeedPercentage = speed / maxSpeed;

    if(maxSpeedPercentage > 1)	
        maxSpeedPercentage = 1;		

}
void Jugador::UpdateHud(){
    //--------------------------------------HUD del jugador dependiendo de si esta activo el multijugador------------------------------------

    if((Options::getInstancia()->getCoop() && pantalla == 't') || (!Options::getInstancia()->getCoop() && pantalla != 'c')){
    
        switch(cargas){
                
                case 0:
                        ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("Nitro","media/Hud/Nitro/Turbo0.png");
                break;

                case 1:
                        ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("Nitro","media/Hud/Nitro/Turbo1.png");
                break;

                case 2:
                        ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("Nitro","media/Hud/Nitro/Turbo2.png");
                break;

                case 3:
                        ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("Nitro","media/Hud/Nitro/Turbo3.png");
                break;
                case 4:
                        ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("Nitro","media/Hud/Nitro/Turbo4.png");
                break;
                case 5:
                        ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("Nitro","media/Hud/Nitro/Turbo4.png");
                break;
        }
    }

    if(Options::getInstancia()->getCoop() && pantalla == 'm'){

        switch(cargas){

                case 0:
                        ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("NitroCoop","media/Hud/Nitro/Turbo0.png");
                break;

                case 1:
                        ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("NitroCoop","media/Hud/Nitro/Turbo1.png");
                break;

                case 2:
                        ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("NitroCoop","media/Hud/Nitro/Turbo2.png");
                break;

                case 3:
                        ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("NitroCoop","media/Hud/Nitro/Turbo3.png");
                break;
                case 4:
                        ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("NitroCoop","media/Hud/Nitro/Turbo4.png");
                break;
                case 5:
                        ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("NitroCoop","media/Hud/Nitro/Turbo4.png");
                break;
        }
    }
}