#pragma once
#include "PhysicsEngine.h"
#include "../Player/Nitro.h"
#include "structs.h"
#include "AudioEngine.h"
#include "../Game/Team.h"


class TriggerSystem{

    public:

        TriggerSystem();
        //~TriggerSystem();

        void checkCollides(std::vector<Nitro*> nitros, Team* blue, Team* red);
        void collideNitro(Baseplayer *coche, std::vector<Nitro*> nitros);
        void marcarGol(Team *blue, Team *red);

    private:

        // Colisiones
        const btCollisionObject *firstCollide;
        const btCollisionObject *secondCollide;

        // Objetos colisionados
        ITResourceMesh *firstNode;
        ITResourceMesh *secondNode;

        // Remover o no colisiones
        bool organizar;

        btRigidBody *rigidNitro;

};