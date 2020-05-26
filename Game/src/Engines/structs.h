#pragma once
// Includes Irrlicht
#include "../../include/irrlicht/irrlicht.h"
#include "../../include/irrlicht/driverChoice.h"

// Includes Bullet
#include "bullet/btBulletCollisionCommon.h"
#include "bullet/btBulletDynamicsCommon.h"
#include "bullet/BulletWorldImporter/btBulletWorldImporter.h"

//#include "../include/bullet/btBulletCollisionCommon.h"
//#include "../include/bullet/btBulletDynamicsCommon.h"
//#include "../include/bullet/BulletWorldImporter/btBulletWorldImporter.h"

// Includes FMOD
//#include "mathvector"
#include "glm/vec3.hpp"
#include "../../include/fmod/fmod.h"
#include "../../include/fmod/fmod_studio.h"
#include "../../include/fmod/fmod_errors.h"

// Includes SDL
#include "SDL/SDL.h"

// Includes Raknet
#include "../../include/raknet/RakPeerInterface.h"
#include "../../include/raknet/MessageIdentifiers.h"
#include "../../include/raknet/RakNetStatistics.h"
#include "../../include/raknet/RakNetTypes.h"
#include "../../include/raknet/NetworkIDManager.h"
#include "../../include/raknet/NetworkIDObject.h"
#include "../../include/raknet/BitStream.h"
#include "../../include/raknet/RakSleep.h"
#include "../../include/raknet/PacketLogger.h"

// Includes IA
#include "../Engines/Vector2d.h"
#include "../Engines/vec2.h"

// Includes OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <GL/gl.h>
#include "../OpenGL/Interfaces/ITEngine.h"

// Includes Extra
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <math.h>
#include <ctime>
#include <stdio.h>
#include <iomanip>

struct people {
        /////////////////////////////////////
        //////    Variables Básicas    //////
        /////////////////////////////////////
        
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

        //variable para saber si estan las ruedas en contacto con el suelo
        //(true si coche estabilizado)
        bool contact;

        std::vector<irr::EKEY_CODE> controles;          // Controles del jugador


        int id;                                         // Variable de control de Jugador
        bool powerNitro;                                // Cambiar su velocidad por la maxima
    
};

struct elements { 

        irr::scene::ISceneNode *node;
        btScalar mass;
        irr::core::vector3df scale;
        irr::core::vector3df position;
        btRigidBody *rigidBody;

        int id;


};
#pragma pack(push, 1)
struct packet {
unsigned char typeId; 




};
#pragma pack(pop)

class Auxiliar{

    public:
        //Estados de la IA
         enum IAstate {
            ATAQUE,
            DEFENSA,
            UTILIZAR_N,
            UTILIZAR_P,
            DEFENSA_L,
            DEFENSA_A,
            NITRO,
            DEFAULT,
            POWERN,
            POWERM,
            USING_P,
            JUMP,
            NONE
         };
         //Estados del Juego
        enum states{
            InitState,
            MenuState,
            GameState,
            GameStateRed,
            ScoreState
        };
        //Botones menu
        enum buttons{
            ID_BUTTON_PLAY,
            ID_BUTTON_OPTIONS,
            ID_BUTTON_MULTIPLAYER,
            ID_BUTTON_MULTIPLAYER_SERVER,
            ID_BUTTON_MULTIPLAYER_CLIENT,
            ID_BUTTON_BACK_MULTIPLAYER,
            ID_BUTTON_BACK,
            ID_BUTTON_QUIT,
            ID_SCROLLBAR_ZOOM,
            ID_SCROLLBAR_ANGLE
        };
        //Mensajes Online
        enum GameMessages{
	        ID_GAME_MESSAGE_1=ID_USER_PACKET_ENUM+1,
            ID_REFRESH_SERVER,
            ID_REFRESH_SERVER2,
            ID_REFRESH_CLIENT,
            ID_REFRESH_CLIENT2,
            ID_WAITING_PLAYER,
            ID_WAITING_PLAYER2,
            ID_SPAWN_PLAYER_CLIENT,
            ID_SPAWN_PLAYER_SERVER,
            ID_START_GAME
        };

    private:

};