#pragma once
#include "Powers.h"

#include "Baseplayer.h"

class IA : public Baseplayer{

    private:

       Powers* poderes;
       float marchaAtras;
       float repetir;
       float Tsalto;
       bool salir;
       double PoderTimer;
       double CD;
       int arrive;
       bool isEnemy; // Para distinguir si la IA es enemigo o aliada
       char who; //Que tipo de IA es, D defensora, A atacante, C mezcla

       btVector3 posWheelUL;
       btVector3 posWheelUR;

    public:

       
        Auxiliar::IAstate Estado;
        Auxiliar::IAstate Estado2;
        Auxiliar::IAstate Estado2Ant; //anterior
        
        int cuadrante;
        btScalar fuerzaG;
        btScalar GiroF;
        /////////////////////////////////////
        //////   New   /  Delete       //////
        /////////////////////////////////////

        IA(int posx, int posz,int idNew,std::string name,char quien);
        ~IA();
         void updateWheels();
         void behaviour(vec2f desired, double speed); //Zona de movimiento e interpretacion de los comportamientos
         void MarchaAtras();
         void UpdateP();                           //Update de la posicion en un vector2f
         void UsePowers(Baseplayer* player); //Uso de los poderes dependiendo del tipo
         void AfectedM();                   //Afectado por el poder de mareo
         void updateDebugHud();             // Actualizamos el hud del debug de la ia
        /////////////////////////////////////
        //////   Setters   /  Getters  //////
        /////////////////////////////////////

        void setId(int x)                           { id=x;};
        void setSalto(int x)                        { salto=x;};
        void setPowerTimer()                        {PoderTimer = glfwGetTime();};
        void setCD()                                {CD = glfwGetTime();};
        void setWho(char a)                         {who=a;};
        void setVnitro (float b)                    {vNitro=b;};
        void setFuerza(btScalar b)                  {fuerzaG=b;};
        void setGiro(btScalar b)                    {GiroF=b;};
        void setEnemy(bool b)                       {isEnemy = b;};
        void jump(); 

        void setEstado(Auxiliar::IAstate a)         {Estado = a; };
        void setEstado2(Auxiliar::IAstate a)        {Estado2 = a; };
        void setEstado2Ant(Auxiliar::IAstate a)     {Estado2Ant = a; };
        Auxiliar::IAstate getEstado()               { return Estado;};
        Auxiliar::IAstate getEstado2()              { return Estado2;};
        Auxiliar::IAstate getEstado2Ant()           { return Estado2Ant;};
        double getPoderTimer()                      { return PoderTimer;};
        double getCD()                              { return CD;};
        float getVmax()                             { return vMaxNitro;};
        char getWho()                               { return who;};
        btScalar getFuerza()                        { return fuerzaG;};
        btScalar getGiro()                          { return GiroF;};
        Powers* getPoderes()                        { return poderes;};
        float getRepetir()                          { return repetir;};
        bool getIsEnemy()                           { return isEnemy;};

        
        /////////////////////////////////////
        //////         Basicas         //////
        /////////////////////////////////////

        

};