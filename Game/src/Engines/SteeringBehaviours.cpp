#include "SteeringBehaviours.h"
using std::string;
using std::vector;

SteeringBehaviours::SteeringBehaviours(IA* enemy){

  enemigo = enemy;

}
SteeringBehaviours::~SteeringBehaviours(){
}

//Dado un target, devuelve una fuerza en la dirección del target
vec2f SteeringBehaviours::Seek(vec2f location, vec2f target){

    float maxSpeed = 0.5;

    vec2f desired;

    // No esta cerca de las paredes
    desired.x = target.x - location.x;
    desired.y = target.y - location.y;
    //desired.normalize();

    return desired;
}




