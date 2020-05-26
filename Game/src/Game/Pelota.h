#pragma once
#include "../Engines/PhysicsEngine.h"
#include "../Engines/structs.h"
#include "../Engines/vec2.h"

class Pelota{

    private:

        ITResourceMesh* node;
        btRigidBody *rigidBody;
        btScalar mass;
        glm::vec3 scale;
        glm::vec3 position;

        btCollisionShape *Shape;
        btDefaultMotionState *MotionState;

        btVector3 Inertia;

        //Instancia
        static Pelota* instancia;

        int id;

        // IA
        vec2f pos;

    public:

        /////////////////////////////////////
        //////   New   /  Delete       //////
        /////////////////////////////////////

        Pelota();
        ~Pelota();

        static Pelota* getInstancia();

        void InitCollide(btDynamicsWorld *world);
        ITResourceMesh* getNode()                   { return node;};
        btRigidBody* getBody()                      { return rigidBody;};
        vec2f getPos()                              { return pos;};

};