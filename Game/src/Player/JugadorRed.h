#pragma once

#include "Baseplayer.h"
//#include "AudioEngine.h"

class JugadorRed : public Baseplayer{

    private:

        //people playerRed;
        std::vector<int> controles;
        bool creado=false;


    public:

        JugadorRed(glm::vec3, int posx, int posz, int idNew,std::string name);
        ~JugadorRed();

        void updateWheels();
        void movement();
        void movementServer();
        bool checkMovement();
        bool doblesalto();
        void calculateSpeed();

        void setControles(std::vector<int> newControles)     {controles = newControles;};
        std::vector<int> getControls()                       {return  controles;};


};