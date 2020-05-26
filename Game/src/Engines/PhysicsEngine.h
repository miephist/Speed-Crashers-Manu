#pragma once
#include <vector>
#include "structs.h"

class PhysicsEngine{

public:

    // Destructor
    ~PhysicsEngine();

    // Getters
    static PhysicsEngine* getInstancia();
    btDynamicsWorld* getWorld();
    std::vector<btRigidBody *> getObjects();

    // Setters
    void setWorld(const char *ruta);
    void setObjects(std::vector<btRigidBody *> obj);
    void removeObject();

private:
    // Constructor
    PhysicsEngine();

    //Instancia
    static PhysicsEngine* instancia;

    // Parametros bullet
    btBroadphaseInterface *phaseColl;
    btDefaultCollisionConfiguration *confCollision;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;
    btDynamicsWorld *world;
    btBulletWorldImporter *fileLoader;

    // Lista de objectos a colisionar
    std::vector<btRigidBody *> objects;

};