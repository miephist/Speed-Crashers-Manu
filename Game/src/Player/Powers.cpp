#include "Powers.h"
#include "Jugador.h"
#include "IA.h"

Powers::Powers(){
 
    srand(time(NULL));
 
    idP = rand()%4;
    CD = 0; // Cooldown para que pueda utilizar el jugador uno de los poderes
    CDP = 0; // Cooldown del propio poder una vez se ha utilizado

    // Controles del jugador con el mareo
    powerControls.push_back(GLFW_KEY_S);
    powerControls.push_back(GLFW_KEY_W);
    powerControls.push_back(GLFW_KEY_D);
    powerControls.push_back(GLFW_KEY_A);

    // Controles del jugador sin mareo
    playerControls.push_back(GLFW_KEY_W);
    playerControls.push_back(GLFW_KEY_S);
    playerControls.push_back(GLFW_KEY_A);
    playerControls.push_back(GLFW_KEY_D);

    cargas = 0;
    // Bool para saber si el poder esta siendo utilizado o no
    activo=false;

    // Instancia del sonido
    aEngine = CAudioEngine::getInstancia();

    // Texto por pantalla
    text = "Cooldown";
}
 
Powers::~Powers(){

}
 
void Powers::activePower(Baseplayer* player){
    
    if(glfwGetTime() - CD >= 10
    || glfwGetTime() - CDP >= 5 && activo == true){
        switch (idP){
            case 0:
                Congelar();
                if(activo){
                 aEngine->PlayEvent("event:/SFX/Powers/Congelar");
                 
                }
            break;
    
            case 1:
               Maxnitro(player);
               if(activo){
                aEngine->PlayEvent("event:/SFX/Powers/maxnitroIn");
                
               }
            break;
    
            case 2:
                Marear(player);
                if(activo){
                    aEngine->PlayEvent("event:/SFX/Powers/Marear");
                   
                }   
            break;

            case 3:
                NitroUp(player);
                if(activo){
                    aEngine->PlayEvent("event:/SFX/Powers/maxnitroIn");
                }
    
            default:
                break;
        }
    }
}

void Powers::updateHUDPowers(char pantalla){
    
    if(glfwGetTime() - CD >= 10){
        switch (idP){
            case 0:
                setTextPower("Congelado");
                
            break;
    
            case 1:
                setTextPower("MaxNitro");
            break;
    
            case 2:
                setTextPower("Mareado");
            break;
            
            case 3:
                setTextPower("NitroUp");
            break;
        }
    }

    if(!ITEngine::getInstancia()->getIsDebugActive()){

        if((Options::getInstancia()->getCoop() && pantalla == 't') || (!Options::getInstancia()->getCoop() && pantalla != 'c')){
            ITEngine::getInstancia()->setActiveHud("GameHud");
            if(getText()=="Congelado"){
                ITEngine::getInstancia()->getActiveHud()->changeTextureElement("Power","media/Hud/Poderes/Poder Freeze.png");
            }else if(getText()=="Mareado"){
                ITEngine::getInstancia()->getActiveHud()->changeTextureElement("Power","media/Hud/Poderes/Poder Mareo.png");
            }else if(getText()=="MaxNitro"){
                ITEngine::getInstancia()->getActiveHud()->changeTextureElement("Power","media/Hud/Poderes/Poder Nitro.png");
            }else if(getText()=="Cooldown"){
                ITEngine::getInstancia()->getActiveHud()->changeTextureElement("Power","media/Hud/Poderes/Cooldown.png");
            }else if(getText()=="NitroUp"){
                ITEngine::getInstancia()->getActiveHud()->changeTextureElement("Power","media/Hud/Poderes/NitroUp.png");
            }
        }
        if(Options::getInstancia()->getCoop() && pantalla == 'm'){
            ITEngine::getInstancia()->setActiveHud("GameHudCoop");
            if(getText()=="Congelado"){
                ITEngine::getInstancia()->getActiveHud()->changeTextureElement("PowerCoop","media/Hud/Poderes/Poder Freeze.png");
            }else if(getText()=="Mareado"){
                ITEngine::getInstancia()->getActiveHud()->changeTextureElement("PowerCoop","media/Hud/Poderes/Poder Mareo.png");
            }else if(getText()=="MaxNitro"){
                ITEngine::getInstancia()->getActiveHud()->changeTextureElement("PowerCoop","media/Hud/Poderes/Poder Nitro.png");
            }else if(getText()=="Cooldown"){
                ITEngine::getInstancia()->getActiveHud()->changeTextureElement("PowerCoop","media/Hud/Poderes/Cooldown.png");
            }else if(getText()=="NitroUp"){
                ITEngine::getInstancia()->getActiveHud()->changeTextureElement("PowerCoop","media/Hud/Poderes/NitroUp.png");
            }
        }
    }

}

void Powers::Congelar(){

    Pelota *pelota = Pelota::getInstancia();

    
    
    if(!activo){

        pelota->getBody()->setLinearFactor(btVector3(0,0,0));
        pelota->getBody()->setAngularFactor(btVector3(0,0,0));

        pelota->getBody()->setLinearVelocity(btVector3(0,0,0));
        pelota->getBody()->setAngularVelocity(btVector3(0,0,0));

        activo=true;
        
        Reset();

       

    }else{

        pelota->getBody()->setLinearFactor(btVector3(1,1,1));
        pelota->getBody()->setAngularFactor(btVector3(1,1,1));

        activo=false;

        idP = rand()%4;

        setTextPower("Cooldown");
     

    }
}

void Powers::Marear(Baseplayer* player){

    if(!activo){
        //Comprobamos si el baseplayer es un jugador o una IA
        if(strcmp(player->getCoche()->getResource()->getNickname(),"Jugador")==0){
           
            playerControls = dynamic_cast<Jugador*>(player)->getControls();
            
            dynamic_cast<Jugador*>(player)->setControles(powerControls);

        }
        else if(strcmp(player->getCoche()->getResource()->getNickname(),"JugadorIA")==0){
            dynamic_cast<IA*>(player)->AfectedM();
            dynamic_cast<IA*>(player)->setEstado2(Auxiliar::IAstate::POWERM);
         
           
           
            
            dynamic_cast<IA*>(player)->setPowerTimer();
        }
        activo=true;

        Reset();
        

        

    }else{
        //Comprobamos si el baseplayer es un jugador o una IA
        if(player->getCoche()->getResource()->getNickname() == "Jugador"){
        dynamic_cast<Jugador*>(player)->setControles(playerControls);
        }
        activo=false;

        idP = rand()%4;

        setTextPower("Cooldown");

    }   
}
 
void Powers::Maxnitro(Baseplayer* player){
    //Comprobamos si el baseplayer es un jugador o una IA
    if(!activo){
        if(strcmp(player->getCoche()->getResource()->getNickname(),"Jugador")==0){
            dynamic_cast<Jugador*>(player)->setPowerNitro(true);
        }
        else if(strcmp(player->getCoche()->getResource()->getNickname(),"JugadorIA")==0){
            dynamic_cast<IA*>(player)->setEstado2(Auxiliar::IAstate::POWERN);
             dynamic_cast<IA*>(player)->setVnitro(5000);
            dynamic_cast<IA*>(player)->setPowerTimer();
        }
        activo=true;

        Reset();

       

    }else{

        player->setPowerNitro(false);

        activo = false;

        idP = rand()%4;

        setTextPower("Cooldown");

        
    }
}
void Powers::NitroUp(Baseplayer* jugador){
    if(!activo){
        if(strcmp(jugador->getCoche()->getResource()->getNickname(), "Jugador") == 0){
            
            jugador->setCargas(5);
            dynamic_cast<Jugador*>(jugador)->UpdateHud();
            activo = true;
            Reset();
        }
    }else{

        idP = rand()%4;

        activo = false;

        setTextPower("Cooldown");
    }
}
void Powers::ResetMareo(Baseplayer* jugador){
        //Resetar controles del jugador.
        if(strcmp(jugador->getCoche()->getResource()->getNickname(), "Jugador") == 0)
            dynamic_cast<Jugador*>(jugador)->setControles(playerControls);
        
}
 
void Powers::Reset(){
    
    // Actualizamos ambos temporizadores
    CD =  glfwGetTime();
    CDP = glfwGetTime();
 
}

void Powers::setTextPower(std::string actualPower){

    text = actualPower;

}

