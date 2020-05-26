#pragma once
#include "../Engines/structs.h"
#include "../Engines/AudioEngine.h"
#include "../Game/Pelota.h"
#include "../Player/Baseplayer.h"
//#include "IA.h"
//#include "Jugador.h"
/*class Jugador;

class IA;*/
class Baseplayer;
 
class Powers{
 
    private:
 
        int idP;
        int CD;
        int CDP;
        int cargas;
        bool activo;
        std::string text;
        std::vector<int> powerControls;
        std::vector<int> playerControls;
        CAudioEngine *aEngine;
 
    public:
 
        /////////////////////////////////////
        //////   New   /  Delete       //////
        /////////////////////////////////////
 
        Powers();
        ~Powers();
 
        void activePower(Baseplayer* player);  //Poder activo del jugador y si es posible su uso
        void updateHUDPowers(char pantalla);    //Cambio del hud de los poderes del jugador
 
        void Congelar();                        //Poder de parar la pelota
        void Marear(Baseplayer* player);        //Cambio de controles tanto IA como jugador
        void Maxnitro(Baseplayer* player);      //Aumenta velocidad tanto IA como jugador
        void NitroUp(Baseplayer* player);       //Recarga superior del nitro al mismo jugador
 
        void ResetMareo(Baseplayer* jugador);
        void Reset();

        void setTextPower(std::string actualPower);

        bool getActivo(){return activo;};
        int getCD(){return CD;};
        int getCDP(){return CDP;};
        std::string getText(){return text;};
 
        int getPowerID(){return idP;};
 
};