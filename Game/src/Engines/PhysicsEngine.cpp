#include "PhysicsEngine.h"

PhysicsEngine *PhysicsEngine::instancia = nullptr;

PhysicsEngine::PhysicsEngine(){

    // Indicamos tamaño del mundo
    phaseColl = new btAxisSweep3(btVector3(-1000, -1000, -1000), btVector3(1000, 1000, 1000));

    // Configura la deteccion de colisiones en bullet
    confCollision = new btDefaultCollisionConfiguration();

    dispatcher = new btCollisionDispatcher(confCollision);

    solver = new btSequentialImpulseConstraintSolver();

    world = new btDiscreteDynamicsWorld(dispatcher, phaseColl, solver, confCollision);

    fileLoader = new btBulletWorldImporter(world);

}

PhysicsEngine::~PhysicsEngine(){


    for(int i = world->getNumCollisionObjects() - 14; i >= 0; i--) {
		btCollisionObject* obj = world->getCollisionObjectArray()[i];
        btCollisionShape* shape = obj->getCollisionShape();
		if (obj) {
			world->removeCollisionObject(obj);
			delete obj;
            delete shape;
		}
	}

    delete fileLoader;
    delete world;
    delete solver;
    delete dispatcher;
    delete confCollision;
    delete phaseColl;
    
    objects.clear();

    instancia = nullptr;
    
}

void PhysicsEngine::setWorld(const char *ruta){

    fileLoader->loadFile(ruta);
    world->setGravity(btVector3(0, -15, 0));

}

void PhysicsEngine::setObjects(std::vector<btRigidBody *> obj){
	
    objects = obj;

}

void PhysicsEngine::removeObject(){
    
    objects.clear();

}

PhysicsEngine *PhysicsEngine::getInstancia(){

    if(instancia == nullptr)
        instancia = new PhysicsEngine();

    return instancia;

}

btDynamicsWorld *PhysicsEngine::getWorld(){

    return world;

}

std::vector<btRigidBody *> PhysicsEngine::getObjects(){
	
    return objects;

}