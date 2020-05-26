#include "Nitro.h"

/////////////////////////////////////
//////      CONSTRUCTORES      //////
/////////////////////////////////////

Nitro::Nitro(glm::vec3 posNitro, int idNitro){
	
	sleep = false;

    node = ITEngine::getInstancia()->createMesh("media/Elementos/Nitro/Nitro.obj", "media/Elementos/Nitro/nitro_diffuse.png");

    position = posNitro;
    scale = glm::vec3(3, 3, 3);

	node->setScale(scale.x, scale.y, scale.z);
	node->setPosition(position.x, position.y, position.z);

    node->getResource()->setNickname("Nitro");

    id = idNitro;

    node->getResource()->setID(id);

	collision = true;
}

btRigidBody* Nitro::InitCollide(glm::vec3 pos){

	PhysicsEngine *bullet = PhysicsEngine::getInstancia();
	std::vector<btRigidBody *> objects = bullet->getObjects();

    btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(btVector3(pos.x, pos.y, pos.z));

	btQuaternion quaternion;
	quaternion.setEulerZYX(node->getRotation().z* M_PI / 180, node->getRotation().y * M_PI / 180, node->getRotation().x* M_PI / 180);
	Transform.setRotation(quaternion);

	btDefaultMotionState *MotionState = new btDefaultMotionState(Transform);
	// Create the shape
	btVector3 HalfExtents(scale.x, scale.y * 0.6, scale.z);
	btCollisionShape *Shape = new btBoxShape(HalfExtents);

	// Add mass
	btVector3 LocalInertia;
    mass = 1;
	Shape->calculateLocalInertia(mass, LocalInertia);

	// Create the rigid body object
	rigidBody = new btRigidBody(mass, MotionState, Shape, LocalInertia);
	btTransform t;
	rigidBody->getMotionState()->getWorldTransform(t);
	
	// Store a pointer to the irrlicht node so we can update it later
	rigidBody->setUserPointer((void *)(node));
	if (mass != 0)
        rigidBody->setActivationState(DISABLE_DEACTIVATION);

	// Anyadimos el rigidbody al mundo
	bullet->getWorld()->addRigidBody(rigidBody);

    objects.push_back(rigidBody);

    bullet->setObjects(objects);
	

	return rigidBody;

}

/////////////////////////////////////
//////      DESTRUCTORES       //////
/////////////////////////////////////

Nitro::~Nitro(){
	delete rigidBody;
}


void Nitro::Delete(){

	CAudioEngine *aEngine = CAudioEngine::getInstancia();
	PhysicsEngine *bullet = PhysicsEngine::getInstancia();
	btDynamicsWorld *mundo = bullet->getWorld();
	std::vector<btRigidBody *> objects = bullet->getObjects();
	
	for (int i=0; i < objects.size(); i++)
	{

		ITResourceMesh *nodoActual = static_cast<ITResourceMesh *>(static_cast<btRigidBody *>(objects.at(i))->getUserPointer());

		if (nodoActual->getResource()->getID() == id)
		{
			btRigidBody *Object = objects.at(i);

			ITResourceMesh *Node = static_cast<ITResourceMesh *>(Object->getUserPointer());

			if (strcmp("Nitro", Node->getResource()->getNickname())==0){

				aEngine->PlayEvent("event:/SFX/Coche/ChoqueLeve");

				node->setVisible(false);
				    
				time = glfwGetTime();
				collision = false;

			}

			// Nos cargamos el objeto
			mundo->removeRigidBody(Object);

			// Vaciamos memoria
			delete Object->getMotionState();
			delete Object->getCollisionShape();
			delete Object;

			// Actualizamos vector de objetos
			objects.erase(objects.begin() + i);
			bullet->setObjects(objects);

			break;
		}
	}
}

/////////////////////////////////////
//////      GETTERS COMP       //////
/////////////////////////////////////


/////////////////////////////////////
//////       MECANICAS         //////
/////////////////////////////////////

void Nitro::respawn(){
	
		if(glfwGetTime() - time >= 5){
			if(collision == false){
				node->setVisible(true);
				node->setPosition(position.x, position.y, position.z);
				InitCollide(position);
				collision = true;
			}
		}
	
}


void Nitro::sleepCollide(){

	// Desactivamos sus colisiones y lo volvemos estatico

	rigidBody->setActivationState(ISLAND_SLEEPING);
    rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);

}

void Nitro::awakeCollide(){

	// Reanudamos sus colisiones y que deje de ser un objeto estatico
	
	rigidBody->setActivationState(ACTIVE_TAG);
	rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() & ~btCollisionObject::CF_STATIC_OBJECT);

}