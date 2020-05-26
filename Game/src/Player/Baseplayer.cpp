#include "Baseplayer.h"

Baseplayer::Baseplayer(int posx, int posz,int idNew, std::string name){
    
    // Equipo
    equipo = "";

    //-------------------------------------------------------------Zona COCHE-----------------------------------------------------------------------
    // Modificar parametros coche en funcion del que sea
    switch (Options::getInstancia()->getNumIAs()){
        // 1 vs 1
        case 1:
           {
                // Id distinta a la del jugador
                if(idNew != 10)
                    coche = ITEngine::getInstancia()->createMesh(Options::getInstancia()->getCarName(), Options::getInstancia()->getRedTex());
                else
                    coche = ITEngine::getInstancia()->createMesh(Options::getInstancia()->getCarName(), Options::getInstancia()->getBlueTex());
                
           }
        break;

        // 2 vs 2
        case 3:
           {
                // Id distinta a la del jugador
                if(idNew != 10 && idNew != 13)
                    coche = ITEngine::getInstancia()->createMesh(Options::getInstancia()->getCarName(), Options::getInstancia()->getRedTex());
                else
                    coche = ITEngine::getInstancia()->createMesh(Options::getInstancia()->getCarName(), Options::getInstancia()->getBlueTex());
                
           }
        break;

        // 3 vs 3
        case 5:
           {
                // Id distinta a la del jugador
                if(idNew != 10 && idNew != 14 && idNew != 15)
                    coche = ITEngine::getInstancia()->createMesh(Options::getInstancia()->getCarName(), Options::getInstancia()->getRedTex());
                else
                    coche = ITEngine::getInstancia()->createMesh(Options::getInstancia()->getCarName(), Options::getInstancia()->getBlueTex());
                
           }
        break;
    }

    coche->setPosition(glm::vec3(posx, -29.5, posz));
    coche->setScale(glm::vec3(1,1,0.89));

    initPos = coche->getPosition();

    if(name.compare("Jugador") == 0){
        coche->getResource()->setNickname("Jugador");
    }else if(name.compare("JugadorIA") == 0){
        coche->getResource()->setNickname("JugadorIA");
    }else if(name.compare("JugadorRed") == 0){
        coche->getResource()->setNickname("JugadorRed");
    }

    salto = 2;

    // IA
    pos.x = posx;
    pos.y = posz;
    //----------------------------------------------------------Fin Zona Coche--------------------------------------
    //----------------------------------------------------------Zona RUEDAS-----------------------------------------

    // Rueda superior izquierda
    wheelUL = ITEngine::getInstancia()->createMesh("media/Coches/Ruedas/Wheel.obj", "media/Coches/Ruedas/tire.png");
    wheelUL->setScale(glm::vec3(0.9,0.9,0.9));

    // Rueda superior derecha
    wheelUR = ITEngine::getInstancia()->createMesh("media/Coches/Ruedas/Wheel.obj", "media/Coches/Ruedas/tire.png");
    wheelUR->setScale(glm::vec3(0.9,0.9,0.9));

    // Rueda inferior izquierda
    wheelDL = ITEngine::getInstancia()->createMesh("media/Coches/Ruedas/Wheel.obj", "media/Coches/Ruedas/tire.png");
    wheelDL->setScale(glm::vec3(0.9,0.9,0.9));

    // Rueda inferior derecha
    wheelDR = ITEngine::getInstancia()->createMesh("media/Coches/Ruedas/Wheel.obj", "media/Coches/Ruedas/tire.png");
    wheelDR->setScale(glm::vec3(0.9,0.9,0.9));
     //----------------------------------------------------------Fin Zona RUEDAS-----------------------------------------

    // Variable para la camara
    angle = 0.0f;
    lastAngle = M_PI;
    angleRotationCamera = 3.0f; // Velocidad a la que la camara vuelve a su lugar si se descoloca
    cameraHeight = 0.0f;
    relativePelotaHeight = 0.0f;

    // Inicializamos variables del nitro
    cargas = 0;
    vNitro = 0;
    vMaxNitro = 5000;

    //variables para calcular la velocidad
    lastPos = glm::vec3(0.0f, 0.0f, 0.0f);
    timer = 0.0f;
    maxSpeed = 200.0f;		
	maxSpeedPercentage = 0.0f;
    speed = 0.0f;
    steeringValue = 0.0f;
    brakeForce = 0.0f;
    engineForce = 0.0f;
    powerNitro = false;

    contact = false;

    ////std::cout << "CREADO JUGADOR" << std::endl;
    
    id = idNew;
    coche->getResource()->setID(id);

}

Baseplayer::~Baseplayer(){
    delete motionStateCar;
    delete centerGravity;
    delete formCollide;
    delete bodyCollideChassis;
    delete vehicle;
}


/////////////////////////////////////
//////        COLLIDE          //////
/////////////////////////////////////

void Baseplayer::InitCollide(btDynamicsWorld *world){

    PhysicsEngine *bullet = PhysicsEngine::getInstancia();

    // Initial position
    btTransform transfCar;
    transfCar.setIdentity();
    btVector3 posTranfCar = btVector3(initPos.x, initPos.y, initPos.z);

    btQuaternion quaternion;
	quaternion.setEulerZYX(coche->getRotation().z * M_PI / 180, coche->getRotation().y * M_PI / 180, coche->getRotation().x * M_PI / 180);
	transfCar.setRotation(quaternion);

    transfCar.setOrigin(posTranfCar);

    // Motion State
    motionStateCar = new btDefaultMotionState(transfCar);

    // Gravity
    btTransform transf;
    transf.setIdentity();
    transf.setOrigin(btVector3(0,1,0));
    centerGravity = new btCompoundShape();

    // Collision
    btVector3 collide(coche->getScale().x, coche->getScale().y, coche->getScale().z);
    formCollide = new btBoxShape(collide);

    // Mass of the car
    mass = 1000;
    btVector3 Inertia(0,0,0);
    formCollide->calculateLocalInertia(mass,Inertia);

    centerGravity->addChildShape(transf,formCollide);

    // Cuerpo del coche
    bodyCollideChassis = new btRigidBody(mass, motionStateCar, centerGravity, Inertia);
    bodyCollideChassis->setUserPointer((void *) coche);

    bodyCollideChassis->setDamping(0.3f, 0.3f);

    world->addRigidBody( bodyCollideChassis);
    // Ray coche
    btVehicleRaycaster* rayVehicle = new btDefaultVehicleRaycaster(world);
    btRaycastVehicle::btVehicleTuning tuning;

     vehicle = new btRaycastVehicle(tuning,  bodyCollideChassis, rayVehicle);

     bodyCollideChassis->setActivationState(DISABLE_DEACTIVATION);
     bodyCollideChassis->setGravity(btVector3(0,-20,0));
    
    world->addVehicle(vehicle);

    // Update collisionable objects in the list.
    std::vector<btRigidBody *> objects = bullet->getObjects();

    objects.push_back(bodyCollideChassis);

    bullet->setObjects(objects);

    // Create the wheels
    addWheels(vehicle, tuning);
}


void Baseplayer::addWheels(btRaycastVehicle* vehicle, btRaycastVehicle::btVehicleTuning tuning){


    btVector3 dirWheels(0, -1, 0);
    btVector3 rotWheels(-1, 0, 0);

    btScalar suspension(0.25);
    btScalar widthWheel(0.4);
    btScalar radiusWheel(0.5);
    btScalar heightChassis(0.5);

    btVector3 pointChassis(coche->getScale().x - radiusWheel, heightChassis,  coche->getScale().z - widthWheel);
    vehicle->setCoordinateSystem(0,1,2);

    // Front Wheel
    vehicle->addWheel(pointChassis * btVector3(2,1,2.8), dirWheels, rotWheels, suspension, radiusWheel, tuning, true);
    vehicle->addWheel(pointChassis * btVector3(-2,1,2.8), dirWheels, rotWheels, suspension, radiusWheel, tuning, true);
    
    // Ruedas traseras
    vehicle->addWheel(pointChassis * btVector3(2,1,-3), dirWheels, rotWheels, suspension, radiusWheel, tuning, false);
    vehicle->addWheel(pointChassis * btVector3(-2,1,-3), dirWheels, rotWheels, suspension, radiusWheel, tuning, false);

    for(int i=0; i <  vehicle->getNumWheels(); i++){
        
        btWheelInfo& wheel =  vehicle->getWheelInfo(i);
        wheel.m_suspensionStiffness = btScalar(10);
        wheel.m_wheelsDampingCompression = btScalar(0.3) * 2 * btSqrt(wheel.m_suspensionStiffness);
        wheel.m_wheelsDampingRelaxation = btScalar(0.5) * 2 * btSqrt(wheel.m_suspensionStiffness);
        wheel.m_frictionSlip = btScalar(10000.0f);
        wheel.m_rollInfluence = btScalar(0);
        wheel.m_maxSuspensionForce = 40000.0f;
        wheel.m_maxSuspensionTravelCm = 10000.0f;

    }
}

void Baseplayer::setCargas(){

    if( cargas < 3)
         cargas += 1;
}
