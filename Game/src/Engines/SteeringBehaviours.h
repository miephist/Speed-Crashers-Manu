#pragma once
#include "PhysicsEngine.h"
#include "../Game/Pelota.h"
#include "structs.h"
#include "../Player/Jugador.h"
#include "../Player/IA.h"

const double WRad    = 1.2; //Radio del wander behaviour
const double WanderDist   = 2.0; // distancia del wanderC
const double WanderJ = 80.0;
const double WSeek  = 20;   


class SteeringBehaviours {
    
    private:

        //Fuerza total de los modos elegidos
        Vector2d fuerzaT;

        //Puntero al dueño
        IA* enemigo;

        //Enemigo - (tambien se pondra compis) - Pelota
        Pelota* bola;

        //Target actual
        Vector2d target;
        
public:
    SteeringBehaviours(IA* enemy);
    ~SteeringBehaviours();
    vec2f Seek(vec2f location, vec2f target);
};