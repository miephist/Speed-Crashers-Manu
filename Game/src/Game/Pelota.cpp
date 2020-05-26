#include "Pelota.h"

Pelota *Pelota::instancia = nullptr;

Pelota::Pelota(){

    node = ITEngine::getInstancia()->createMesh("media/Elementos/Pelota/Pelota.obj", "media/Elementos/Pelota/pelota_diffuse.png");

    scale = glm::vec3(3, 3, 3);
    position = glm::vec3(0,-24.5,0);

	node->setScale(scale);
	node->setPosition(position.x, position.y, position.z);

	pos.x = node->getPosition().x;
	pos.y = node->getPosition().z;

    node->getResource()->setNickname("Pelota");

    id = 6;
    node->getResource()->setID(id);

}

Pelota::~Pelota(){

	delete MotionState;
	delete Shape;
	delete rigidBody;
	
	instancia = nullptr;

}

Pelota *Pelota::getInstancia(){

    if(instancia == nullptr)
        instancia = new Pelota();

    return instancia;

}

void Pelota::InitCollide(btDynamicsWorld *world){

    PhysicsEngine *bullet = PhysicsEngine::getInstancia();

    btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(btVector3(position.x, position.y, position.z));

	Transform.setRotation(Transform.getRotation());

	btQuaternion quaternion;
	quaternion.setEulerZYX(node->getRotation().z* M_PI / 180, node->getRotation().y * M_PI / 180, node->getRotation().x* M_PI / 180);
	Transform.setRotation(quaternion);
	

	MotionState = new btDefaultMotionState(Transform);

	// Create the shape
	Shape = new btSphereShape(3.0f);

	// Add mass
	Inertia = btVector3(0,0,0);
    mass = 2.5;
	Shape->calculateLocalInertia(mass, Inertia);

	// Create the rigid body object
	rigidBody = new btRigidBody(mass, MotionState, Shape, Inertia);
	btTransform t;
	rigidBody->getMotionState()->getWorldTransform(t);
	
	// Store a pointer to the irrlicht node so we can update it later
	rigidBody->setUserPointer((void *)(node));
	if (mass != 0)
        rigidBody->setActivationState(DISABLE_DEACTIVATION);

    world->addRigidBody(rigidBody);

	// Actualizamos los objetos colisionables de la lista
	std::vector<btRigidBody *> objects = bullet->getObjects();

    objects.push_back(rigidBody);

	bullet->setObjects(objects);

}