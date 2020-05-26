#pragma once
#include "../Engines/PhysicsEngine.h"
#include "../Game/Camera.h"
#include "../Game/Pelota.h"
#include "../Engines/structs.h"
#include "../Engines/AudioEngine.h"
#include "../Engines/vec2.h"
#include "../Engines/Options.h"
//#include "../Player/Powers.h"
#include <iostream>

class Baseplayer {

    protected:

        //Powers* poderes;

        vec2f pos;
        std:: string equipo;
        /////////////////////////////////////
        //////    Variables Básicas    //////
        /////////////////////////////////////

        // Motor Grafico
        ITResourceMesh* coche;
        ITResourceMesh* wheelUL;
	    ITResourceMesh* wheelUR;
        ITResourceMesh* wheelDL;
        ITResourceMesh* wheelDR;

        glm::vec3 initPos;
        glm::vec3 lastPos;

        // Bullet
        btRaycastVehicle* vehicle;
        btDefaultMotionState *motionStateCar;
        btCollisionShape *formCollide;
        btScalar mass;
        btRigidBody *bodyCollideChassis;
        btCompoundShape* centerGravity;

        //Velocidad calculada del coche
        float speed;
        float maxSpeed;
        float maxSpeedPercentage;
        float timer;

        // Velocidad del nitro
        float vNitro;

        // Salto
        bool jump1 = true;
        int salto;

        // Velocidad maxima del nitro
        float vMaxNitro;                                // Velocidad máxima del nitro

        // Cargas del nitro
        int cargas;                                     // Cargas actuales del nitro

        // Porcentaje de rotacion
        float maxSpeedRotation;
        float rotationPercentage;

        // Angulo para la rotacion del vehiculo
        float angle;
        float angleRotationCamera;
        btScalar steeringValue;
        btScalar engineForce;
        btScalar brakeForce;
        float angleCamera;
        float lastAngle;
        float relativePelotaHeight;
        float cameraHeight;

        //(true si coche estabilizado)
        bool contact;
        


        int id;                                         // Variable de control de Jugador
        bool powerNitro;                                // Cambiar su velocidad por la maxima

        Baseplayer(int posx,int posz, int idNew, std::string name);
    

    public:

        ~Baseplayer();

        void InitCollide(btDynamicsWorld *world);
        void addWheels(btRaycastVehicle* vehicle,btRaycastVehicle::btVehicleTuning tuning);
        void setCargas();


        virtual void updateWheels()=0;



        /////////////////////////////////////
        //////   Setters   /  Getters  //////
        /////////////////////////////////////


        void setId(int x)                           {  id=x;};
        void setTeam(std::string a)                 { equipo=a;};
        //void setPower(int x)                        {  power=x;};
        void setSalto(int x)                        {  salto=x;};
        void setLastAngle(float x)                  {  lastAngle=x;};
        void setPos(vec2f newPos)                   { pos = newPos;};
        void setCargas(int x)                       { cargas = x;};

        ITResourceMesh* getCoche()                  { return  coche;};
        std::string getTeam()                       { return equipo;};
        float getAngle()                            { return  angle;};
        float getAngleCamera()                      { return  angleCamera;}; 
        float getLastAngle()                        { return  lastAngle;};
        float getCameraHeight()                     { return  cameraHeight;};
        float getVelNitro()                         { return  vNitro;};
        int getSalto()                              { return  salto;};  
        int getCargas()                             { return  cargas;};  
        bool getContact()                           { return  contact;};
        vec2f getPos()                              { return  pos;};
        float getSpeed()                            { return  speed;};
        btRaycastVehicle* getVehicle()              { return  vehicle;};
        
        void setVnitro(float n)                     { vNitro=n;};
        void setSteering(btScalar st)               { steeringValue=st;};
        void setEngineF(btScalar st)                { engineForce=st;};
        void setBrakeForce(btScalar st)             { brakeForce=st;};
        btScalar getbrakeForce()                    { return brakeForce;};
        btScalar getSteering()                      { return steeringValue;};
        btScalar getEngineF()                       { return engineForce;};
        btRigidBody* getBody()                      { return bodyCollideChassis;};


        void setPowerNitro(bool newBool)            {  powerNitro = newBool;};


};