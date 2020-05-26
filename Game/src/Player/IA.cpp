#include "IA.h"

/////////////////////////////////////
//////      CONSTRUCTORES      //////
/////////////////////////////////////

IA::IA(int posx,int posz,int idNew,std::string name,char quien):Baseplayer(posx, posz, idNew,name){
    
    cuadrante = 0;
    salir = false;
    fuerzaG = 12000;
    btScalar GiroF = 0;
    
    //Creacion poderes
    poderes = new Powers();

    // Temporizadores
    marchaAtras = 0;
    repetir = 0;
    Tsalto = 0;
    PoderTimer = 0;
    CD = 0;

    //variables vareas
    arrive = 15;

    //Tipo
    who = quien;

    isEnemy = true;

    // Estados
    if(who == 'A'){
         Estado = Auxiliar::IAstate::ATAQUE;
         Estado2Ant = Auxiliar::IAstate::DEFAULT;
    }
    else if(who == 'D'){
         Estado = Auxiliar::IAstate::DEFENSA;
         Estado2Ant = Auxiliar::IAstate::DEFAULT;
    }
    else if(who == 'C'){
         Estado = Auxiliar::IAstate::DEFENSA;
         Estado2Ant = Auxiliar::IAstate::DEFAULT;
    }
   
    Estado2 = Auxiliar::IAstate::DEFAULT;

}

IA::~IA(){
 
} 

void IA::updateWheels(){
    
    Pelota *pelota = Pelota::getInstancia();

    btTransform ruedas= vehicle->getWheelTransformWS(0);

    wheelUL->setPosition(ruedas.getOrigin().getX(),ruedas.getOrigin().getY(),ruedas.getOrigin().getZ());
    wheelUL->setRotation(ruedas.getRotation().getX(),ruedas.getRotation().getY(),ruedas.getRotation().getZ(), ruedas.getRotation().getAngle());

    posWheelUL = btVector3(ruedas.getOrigin().getX(),ruedas.getOrigin().getY(),ruedas.getOrigin().getZ());


    ruedas = vehicle->getWheelTransformWS(1);
    
    wheelUR->setPosition(ruedas.getOrigin().getX(),ruedas.getOrigin().getY(),ruedas.getOrigin().getZ());
    wheelUR->setRotation(ruedas.getRotation().getX(),ruedas.getRotation().getY(),ruedas.getRotation().getZ(), ruedas.getRotation().getAngle());

    posWheelUR = btVector3(ruedas.getOrigin().getX(),ruedas.getOrigin().getY(),ruedas.getOrigin().getZ());
    
    
    ruedas = vehicle->getWheelTransformWS(2);

    wheelDL->setPosition(ruedas.getOrigin().getX(),ruedas.getOrigin().getY(),ruedas.getOrigin().getZ());
    wheelDL->setRotation(ruedas.getRotation().getX(),ruedas.getRotation().getY(),ruedas.getRotation().getZ(), ruedas.getRotation().getAngle());
    
    
    ruedas = vehicle->getWheelTransformWS(3);

    wheelDR->setPosition(ruedas.getOrigin().getX(),ruedas.getOrigin().getY(),ruedas.getOrigin().getZ());
    wheelDR->setRotation(ruedas.getRotation().getX(),ruedas.getRotation().getY(),ruedas.getRotation().getZ(), ruedas.getRotation().getAngle());

    // Updateamos angulo de la camara en funcion de las ruedas y del vehiculo una vez ya estas seteadas sus posiciones y rotaciones
    angle = atan2f(wheelUR->getPosition().x - vehicle->getRigidBody()->getCenterOfMassPosition().x() ,
             wheelUR->getPosition().z - vehicle->getRigidBody()->getCenterOfMassPosition().z() );
    angle += 225*M_PI/180;

    // Updatemos angulo de la camara en funcion de la pelota
    angleCamera = atan2f(pelota->getNode()->getPosition().x - vehicle->getRigidBody()->getCenterOfMassPosition().x(),
            pelota->getNode()->getPosition().z - vehicle->getRigidBody()->getCenterOfMassPosition().z() );
    angleCamera += 180 * M_PI/180;

    if(angle<0)
        angle=angle+360*M_PI/180;
    if(angleCamera<0)
        angleCamera=angleCamera+360*M_PI/180;
    
}

void IA::MarchaAtras(){
     
    if(glfwGetTime() - repetir > 5){
                marchaAtras = glfwGetTime();
                repetir = glfwGetTime();
                salir = true;
    }
    if(glfwGetTime() - marchaAtras < 2 && salir == true){
            
                fuerzaG = -9000;
                GiroF = GiroF * -1;
    }
    else{
        salir = false;
    }
    vehicle->setSteeringValue(GiroF,0);
    vehicle->setSteeringValue(GiroF,1);
    vehicle->applyEngineForce(fuerzaG + vNitro, 2);
    vehicle->applyEngineForce(fuerzaG + vNitro, 3);
}

void IA::behaviour(vec2f desired, double speed){
    
    // Obtenemos el vector steering
    vec2f steer;
    
    int fuerzaG2=0;
    
    btTransform chassisTransform = vehicle->getChassisWorldTransform();

    float x = (((posWheelUL.getX() + posWheelUR.getX())/2) - coche->getPosition().x) * 10;
    float mitadX = (posWheelUL.getX() + posWheelUR.getX())/2;

    float z = (((posWheelUL.getZ() + posWheelUR.getZ())/2) - coche->getPosition().z) * 10;
    float mitadZ = (posWheelUL.getZ() + posWheelUR.getZ())/2;

    float sumaX = x + mitadX;
    float sumaZ = z + mitadZ;

    //---------------- Para cuando se use Seek -------------------------------------------//
    // Obtenemos el vector velocity (vector director del coche)
    vec2f velocity(vehicle->getForwardVector().getX(), vehicle->getForwardVector().getZ());            

    //ITEngine::getInstancia()->setColorDebug(glm::vec4(1.0,0.0,0.0,0.0));
    //ITEngine::getInstancia()->setVertexDebug(coche->getPosition().x, coche->getPosition().y, coche->getPosition().z, sumaX, coche->getPosition().y, sumaZ);
    //ITEngine::getInstancia()->setVertexDebug(mitadX, coche->getPosition().y, mitadZ, mitadX + desired.x, Pelota::getInstancia()->getNode()->getPosition().y, mitadZ + desired.y);

    /*
    std::cout << "IA: " << coche->getPosition().x << ", " << coche->getPosition().y << ", " << coche->getPosition().z << std::endl;
    std::cout << "Mitad: " << (posWheelUL.getX() + posWheelUR.getX())/2 << ", " << (posWheelUL.getZ() + posWheelUR.getZ())/2 << std::endl;
    std::cout << "Operacion: " << (((posWheelUL.getX() + posWheelUR.getX())/2) - coche->getPosition().x) * 10 << ", " << (((posWheelUL.getZ() + posWheelUR.getZ())/2) - coche->getPosition().z) * 10 << std::endl;
    */

   if(Estado2 == Auxiliar::IAstate::UTILIZAR_N){
       cargas--;
       vNitro = vMaxNitro;
       Estado2 = Auxiliar::IAstate::POWERN;
   }
   if(Estado2==Auxiliar::IAstate::POWERN && vNitro>0){
        vNitro -= 20;
        if(vNitro <=0){
            vNitro = 0;
            Estado2 = Auxiliar::IAstate::DEFAULT;
        }
    }


    desired.normalize();

    // Obtenemos el steering a aplicar
    GiroF = btScalar(steer.cross(desired,velocity));
    //std::cout<<"Velocidad: "<<(1-(speed+12.5)/100)<<std::endl;
    double velosidad = (1-(speed+12.5)/100);
    
    if(velosidad <= 0.5){
        velosidad = 0.5;
    }
    if(velosidad > 1){
        velosidad = 1;
    }
    if(velosidad > 0 && velosidad <1){
        velosidad = velosidad;
    }
    else{
        velosidad = 0.5;
    }
    fuerzaG = 12000 * velosidad;
    //Poder nitro de la IA tipo C
   /* if(Estado2==Auxiliar::IAstate::POWERN && glfwGetTime() - PoderTimer>= 5){
        vNitro=0;
        Estado2=Estado2Ant;
    }


    

    switch(Estado){
        //-------------------------------ZONA ATAQUE-----------------------------------------------
        case Auxiliar::IAstate::ATAQUE:
        { 
          
           // Si choca en la pared inicializamos temporizador
            if(wall == true && glfwGetTime() - repetir > 5){
                marchaAtras = glfwGetTime();
                repetir = glfwGetTime();
                salir = true;
            }

          // Lo sacamos de la pared
            if(glfwGetTime() - marchaAtras < 2 && salir == true)
            {
                fuerzaG = -9000;
                GiroF = GiroF * -1;
            }else{
               
                salir = false;
                fuerzaG = fuerzaG + vNitro;
            }
         
        }
        break;
        //-------------------------------Fin ZONA ATAQUE-----------------------------------------------
        //-------------------------------ZONA DEFENSA-----------------------------------------------
        case Auxiliar::IAstate::DEFENSA:
        {
            if(wall == true && glfwGetTime() - repetir > 5){
                marchaAtras = glfwGetTime();
                repetir = glfwGetTime();
                salir = true;
            }
            if(glfwGetTime() - marchaAtras < 2 && salir == true)
            {
                fuerzaG = -9000;
                GiroF = GiroF * -1;
            }else{
              
                salir = false;
                fuerzaG = fuerzaG + vNitro;
            }
            
            
            
        }
        break;
        //-------------------------------Fin ZONA DEFENSA-----------------------------------------------
        //-------------------------------ZONA COMPORTAMIENTOS DE ESPERA--------------------------------
        case Auxiliar::IAstate::NONE:
        {
            if(who=='A' && Estado2==Auxiliar::IAstate::UTILIZAR_P){

            }
            else if(who=='D'){
                
                if(Estado2==Auxiliar::IAstate::DEFENSA_L){
                
                    if(equipo=="red"){
                        if(abs(coche->getPosition().x )>= 1 && abs(coche->getPosition().z)>= 180){
                            fuerzaG = 0;
                        }
                    }
                    else{
                        if(abs(coche->getPosition().x )>= 1 && coche->getPosition().z<= -180){
                            fuerzaG = 0;
                        }
                    }
                    if(fuerzaG == 0){
                        Estado2=Auxiliar::IAstate::DEFENSA_A;
                    }
                }
                else if(Estado2==Auxiliar::IAstate::DEFENSA_A){
                    if(equipo=="red"){
                        fuerzaG = 0;
                    }
                    else{
                        
                    }
                }

            }
            
        }
        break;
        //-------------------------------Fin ZONA COMPORTAMIENTOS DE ESPERA--------------------------------
    }

    if(Estado2 == Auxiliar::IAstate::NITRO){ //IR NITRO

        Estado2 = Auxiliar::IAstate::DEFAULT;
       
    }

    if(Estado2 == Auxiliar::IAstate::UTILIZAR_N && cargas>=1){
        cargas--;
        vNitro = vMaxNitro;
        Estado2 = Auxiliar::IAstate::DEFAULT;
    }*/

    // Aplicamos fuerzas y steering

    vehicle->setSteeringValue(GiroF,0);
    vehicle->setSteeringValue(GiroF,1);
    vehicle->applyEngineForce(fuerzaG + vNitro, 2);
    vehicle->applyEngineForce(fuerzaG + vNitro, 3);
    
}              
void IA::AfectedM(){

    Estado2 = Auxiliar::IAstate::POWERM;
    GiroF = -abs(GiroF);
    fuerzaG = -abs(fuerzaG);

    vehicle->setSteeringValue(GiroF,0);
    vehicle->setSteeringValue(GiroF,1);
    vehicle->applyEngineForce(fuerzaG + vNitro, 2);
    vehicle->applyEngineForce(fuerzaG + vNitro, 3);

}
void IA::UsePowers(Baseplayer* player){

    switch (who)
    {
        case 'A':
        {
            if(glfwGetTime() - poderes->getCD() >=10){
                setPowerTimer();
                poderes->Marear(player);
            }

        }
            break;
        case 'D':
        {
            if(glfwGetTime() - poderes->getCD() >=10){
                std::cout<<"Congelo "<<std::endl;
                poderes->Congelar();
            }
        }
            break;
        case 'C':
        {
            if(glfwGetTime() - poderes->getCD() >=10){
                poderes->Maxnitro(player);
            }
        }
            break;
        default:
            break;
    }


}

void IA::jump(){
    if(salto>1){
        bodyCollideChassis->applyCentralImpulse(btVector3(0,15500,0));
        salto--;
    }
    else{
        Estado2= Auxiliar::IAstate::DEFAULT;
    }
}

/////////////////////////////////////
//////      DESTRUCTORES       //////
/////////////////////////////////////

void IA::UpdateP(){
    pos.x = coche->getPosition().x;
    pos.y = coche->getPosition().z;
}


/////////////////////////////////////
//////       MECANICAS         //////
/////////////////////////////////////

void IA::updateDebugHud(){

    // Actualizamos cargas
    switch(cargas){

        case 0:
            ITEngine::getInstancia()->getHud("DebugHud")->changeTextureElement("NitroIA","media/Hud/Debug/Nitro/Turbo0.png");
        break;

        case 1:
            ITEngine::getInstancia()->getHud("DebugHud")->changeTextureElement("NitroIA","media/Hud/Debug/Nitro/Turbo1.png");
        break;

        case 2:
            ITEngine::getInstancia()->getHud("DebugHud")->changeTextureElement("NitroIA","media/Hud/Debug/Nitro/Turbo2.png");
        break;

        case 3:
            ITEngine::getInstancia()->getHud("DebugHud")->changeTextureElement("NitroIA","media/Hud/Debug/Nitro/Turbo3.png");
        break;

    }

    // Actualizamos zona del campo

    float z = Options::getInstancia()->getForwardScenario();

    if(coche->getPosition().z > -z && coche->getPosition().z < -z/3){
        ITEngine::getInstancia()->getHud("DebugHud")->changeTextureElement("ZonaIA","media/Hud/Debug/Zonas/Semaforo Rojo.png");
    }else if(coche->getPosition().z > -z/3 && coche->getPosition().z < z/3){
        ITEngine::getInstancia()->getHud("DebugHud")->changeTextureElement("ZonaIA","media/Hud/Debug/Zonas/Semaforo Amarillo.png");
    }else if(coche->getPosition().z > z/3 && coche->getPosition().z < z){
        ITEngine::getInstancia()->getHud("DebugHud")->changeTextureElement("ZonaIA","media/Hud/Debug/Zonas/Semaforo Verde.png");
    }

    // Actualizamos poderes

    if(Estado2 == Auxiliar::IAstate::USING_P){
        switch(who){
            
            case 'A':
                ITEngine::getInstancia()->getHud("DebugHud")->changeTextureElement("PoderIA", "media/Hud/Debug/Poderes/inversion.png");
            break;

            case 'C':
                ITEngine::getInstancia()->getHud("DebugHud")->changeTextureElement("PoderIA", "media/Hud/Debug/Poderes/nitro2.png");
            break;

            case 'D':
                ITEngine::getInstancia()->getHud("DebugHud")->changeTextureElement("PoderIA", "media/Hud/Debug/Poderes/freeze.png");
            break;

        }
    }else{
        ITEngine::getInstancia()->getHud("DebugHud")->changeTextureElement("PoderIA", "media/Hud/Debug/Poderes/Cooldown.png");
    }

    // Actualizamos estado de la IA

    switch(Estado){

        case Auxiliar::IAstate::ATAQUE:
            ITEngine::getInstancia()->getHud("DebugHud")->changeTextureElement("EstadoIA","media/Hud/Debug/Estados/Ataque.png");
        break;

        case Auxiliar::IAstate::DEFENSA:
            ITEngine::getInstancia()->getHud("DebugHud")->changeTextureElement("EstadoIA","media/Hud/Debug/Estados/Defensa.png");
        break;

    }
}