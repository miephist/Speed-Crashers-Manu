#pragma once
#include "../Engines/PhysicsEngine.h"
#include "../Player/Jugador.h"
#include "../Engines/structs.h"
#include "../Engines/AudioEngine.h"

class Nitro{

    private:
        
        /////////////////////////////////////
        //////    Variables Básicas    //////
        /////////////////////////////////////
        ITResourceMesh* node;
        glm::vec3 scale;
        glm::vec3 position;

        // Bullet
        btScalar mass;
        btRigidBody *rigidBody;

        int id;
        bool collision;
        bool sleep;   //Si se han desactivado las colisiones es true
        int time;

        /////////////////////////////////////
        //////        Vectores         //////
        /////////////////////////////////////


    public:

        /////////////////////////////////////
        //////   New   /  Delete       //////
        /////////////////////////////////////

        Nitro(glm::vec3 posNitro, int idNitro);
        ~Nitro();

        void Delete();

        /////////////////////////////////////
        //////   Setters   /  Getters  //////
        /////////////////////////////////////
        bool getSleep() {return sleep;};
        int getID(){return id;};
        int getTime(){return time;};
        bool getCollision(){return collision;};
        ITResourceMesh* getNode(){return node;};

        /////////////////////////////////////
        //////         Basicas         //////
        /////////////////////////////////////   

        btRigidBody* InitCollide(glm::vec3 pos);    
        void respawn();  
        void sleepCollide();
        void awakeCollide();

};