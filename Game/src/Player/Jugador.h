#pragma once
#include "Powers.h"

#include "Baseplayer.h"

class Jugador : public Baseplayer{

    private:
        //people *player; // Player contiene las variables tanto de Jugador como de IA, Revisar ../Engines/structs.h
        std::vector<int> controles;
        Powers* poderes;
        double timer;
        double timer2;
        double timerspeed;
        bool pressed;
        bool checked;
        char pantalla; // m = mando, t = teclado

        // Joystick
        int newState;
        int oldState;

        int newState2;
        int oldState2;

        int newState3;
        int oldState3;

        // Saber si se ha borrado la leyenda
        bool erase;
        
        ITPivote* targeto;

        //Variables de movement
        PhysicsEngine *bullet;
        CAudioEngine *aEngine;
        Pelota *pelota;
       
    public:

        /////////////////////////////////////
        //////   New   /  Delete       //////
        /////////////////////////////////////

        Jugador(int posx, int posz,int idNew,std::string name,char pant);
        ~Jugador();

        void updateWheels();
        void movement(Baseplayer* enemigo); //Zona del momiviento, uso de poderes, uso del nitro, salto ...
        bool checkMovement(bool controller, const unsigned char* buttons, const float* axes); //Comprobador de movimiento
        bool doblesalto(bool controller, const unsigned char* buttons, const float* axes);  //Doble salto con impulso hacia cualquier lado
        void calculateSpeed();
        void UpdateHud();   //Hud del jugador
        void setPantalla(char y)                                        {pantalla = y;};
        char getPantalla()                                              {return pantalla;};
        

        void setControles(std::vector<int> newControles)                {controles = newControles;};
        std::vector<int> getControls()                                  {return  controles;};
        Powers* getPowers()                                             {return poderes;};
        ITPivote* getPivote(){return targeto;};

};