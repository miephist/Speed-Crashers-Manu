#include <iostream>
#include <irrlicht/irrlicht.h>
#include <irrlicht/driverChoice.h>

using namespace std;
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui; 

class MyEventReceiver : public IEventReceiver
{
public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

        return false;
    }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }
    
    MyEventReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

int main(){

    // Al tener el include driverChoice.h podemos llamar a la funcion
    // driverChoiceConsole() para que nos haga la eleccion de drivers 
    E_DRIVER_TYPE driverType=driverChoiceConsole();
    if (driverType==EDT_COUNT)
        return 1;

    // create device
    MyEventReceiver receiver;

    // Creamos el objeto principal para usar el motor
    IrrlichtDevice* device = createDevice(driverType,
            core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);
    
    // Si no podemos crearlo con el driver seleccionado devolvemos 1
    if (device == 0)
        return 1;

    // Cambiamos la ruta en la que nos coge los archivos
    device->getFileSystem()->changeWorkingDirectoryTo("../ejemplo4");

    // Obtenemos el puntero del driver y a la escena
    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();

    // Creamos un cubo para la escena (podemos crear otra forma geometrica)
    ISceneNode* node = smgr->addCubeSceneNode();
    if (node)
    {
        node->setPosition(vector3df(0,0,30));
        node->setMaterialTexture(0, driver->getTexture("../ejemplo4/resources/wall.bmp"));
        node->setMaterialFlag(EMF_LIGHTING, false);
    }

    // Creamos otro cubo que ira dando vueltas alrededor nuestro
    ISceneNode* n = smgr->addCubeSceneNode();
    if (n)
    {
        n->setMaterialTexture(0, driver->getTexture("../ejemplo4/resources/t351sml.jpg"));
        n->setMaterialFlag(EMF_LIGHTING, false);
        ISceneNodeAnimator* anim =
            smgr->createFlyCircleAnimator(vector3df(0,0,30), 20.0f);
        if (anim)
        {
            n->addAnimator(anim);
            anim->drop();
        }
    }

    // Creamos un ninja que ira andando horizontalmente al fondo de la escena
    IAnimatedMeshSceneNode* anms =
        smgr->addAnimatedMeshSceneNode(smgr->getMesh("../ejemplo4/resources/ninja.b3d"));

    if (anms)
    {
        ISceneNodeAnimator* anim =
            smgr->createFlyStraightAnimator(vector3df(100,0,60),
            vector3df(-100,0,60), 3500, true);
        if (anim)
        {
            anms->addAnimator(anim);
            anim->drop();
        }

        anms->setMaterialFlag(EMF_LIGHTING, false);

        anms->setFrameLoop(0, 13);
        anms->setAnimationSpeed(15);
        //anms->setMD2Animation(scene::EMAT_RUN);

        anms->setScale(vector3df(2.f,2.f,2.f));
        anms->setRotation(vector3df(0,-90,0));
        //anms->setMaterialTexture(0, driver->getTexture("../../media/sydney.bmp"));
    }

    // Creamos la camara
    smgr->addCameraSceneNodeFPS();

    // Inicializamos la posicion de la camara
    vector3df nodePositionCamera = node->getPosition();
    nodePositionCamera.Y = nodePositionCamera.Y + 5.0f;
    nodePositionCamera.Z = nodePositionCamera.Z - 20.0f;
    smgr->getActiveCamera()->setPosition(nodePositionCamera);

    // Ocultamos el cursor
    device->getCursorControl()->setVisible(false);

    int lastFPS = -1;

    // In order to do framerate independent movement, we have to know
    // how long it was since the last frame
    u32 then = device->getTimer()->getTime();

    // This is the movemen speed in units per second.
    const f32 MOVEMENT_SPEED = 5.f;

    while(device->run())
    {
        // Work out a frame delta time.
        const u32 now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;

        vector3df nodePosition = node->getPosition();

        if(receiver.IsKeyDown(KEY_KEY_W)){
            nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime;

            // Actualizamos posicion de la camara en Z
            nodePositionCamera.Z = nodePosition.Z - 20.0f;
        }else if(receiver.IsKeyDown(KEY_KEY_S)){
            nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime;
            
            // Actualizamos posicion de la camara en Z
            nodePositionCamera.Z = nodePosition.Z - 20.0f;
        }

        if(receiver.IsKeyDown(KEY_KEY_A)){
            nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;

            // Actualizamos posicion de la camara en Y
            nodePositionCamera.X = nodePosition.X;
        }else if(receiver.IsKeyDown(KEY_KEY_D)){
            nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;

            // Actualizamos posicion de la camara en Y
            nodePositionCamera.X = nodePosition.X;
        }

        node->setPosition(nodePosition);
        smgr->getActiveCamera()->setPosition(nodePositionCamera);

        driver->beginScene(true, true, SColor(255,113,113,133));

        smgr->drawAll(); // draw the 3d scene
        //device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)

        driver->endScene();

        int fps = driver->getFPS();

        if (lastFPS != fps)
        {
            stringw tmp(L"Movement Example - Irrlicht Engine [");
            tmp += driver->getName();
            tmp += L"] fps: ";
            tmp += fps;

            device->setWindowCaption(tmp.c_str());
            lastFPS = fps;
        }
    }

    device->drop();

    return 0;
}