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


int main(){

    /* 
    Explicacion mas detallada del codigo en el siguiente enlace:
        http://irrlicht.sourceforge.net/docu/example002.html
    */

    /*
    
    PASOS A REALIZAR SI NO SE INCLUYE EL INCLUDE "driverChoice.h"

    video::E_DRIVER_TYPE driverType;

    printf("Please select the driver you want for this example:\n"\
    " (a) OpenGL 1.5\n (b) Direct3D 9.0c\n (c) Direct3D 8.1\n"\
    " (d) Burning's Software Renderer\n (e) Software Renderer\n"\
    " (f) NullDevice\n (otherKey) exit\n\n");

    char i;
    cin >> i;

    switch(i)
    {
        case 'a': driverType = video::EDT_OPENGL;   break;
        case 'b': driverType = video::EDT_DIRECT3D9;break;
        case 'c': driverType = video::EDT_DIRECT3D8;break;
        case 'd': driverType = video::EDT_BURNINGSVIDEO;break;
        case 'e': driverType = video::EDT_SOFTWARE; break;
        case 'f': driverType = video::EDT_NULL;     break;
        default: return 1;
    }

    */

    // Al tener el include driverChoice.h podemos llamar a la funcion
    // driverChoiceConsole() para que nos haga la eleccion de drivers 
    E_DRIVER_TYPE driverType = driverChoiceConsole();
    if (driverType==EDT_COUNT)
        return 1;

    // Creamos el objeto principal para usar el motor
    IrrlichtDevice *device =
        createDevice(driverType, core::dimension2d<u32>(640, 480));

    // Si no podemos crearlo con el driver seleccionado devolvemos 1
    if (device == 0)
        return 1;

    // Cambiamos la ruta en la que nos coge los archivos
    device->getFileSystem()->changeWorkingDirectoryTo("../ejemplo2");

    // Obtenemos el puntero del driver y a la escena
    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();

    // Cargamos el zip con todo el mapeado
    device->getFileSystem()->addFileArchive("../ejemplo2/resources/map-20kdm2.pk3");

    // Obtenemos el mapa
    IAnimatedMesh* mesh = smgr->getMesh("20kdm2.bsp");

    ISceneNode* node = 0;

    // Mediante la tecnica Octree optimizamos la escena al dibujar solo lo que se esta mostrando
    if (mesh)
        node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
        //node = smgr->addMeshSceneNode(mesh->getMesh(0));

    // Inicializamos posicion de la camara al no ser creado el modelado en la posicion (0,0,0)
    if (node)
        node->setPosition(core::vector3df(-1300,-144,-1249));

    // Creamos una camara con los controles propios de un FPS
    // Existe otros tipos de camara como la de Maya (documentarse)
    smgr->addCameraSceneNodeFPS();

    // Ocultamos el cursor
    device->getCursorControl()->setVisible(false);

    int lastFPS = -1;

    // Creamos el bucle principal
    // Comprobamos que la ventana del juego esta siendo utilizada
    // Y que no estamos con otras tareas para que no se coma la CPU
    while(device->run())
    {
        if (device->isWindowActive())
        {
            driver->beginScene(true, true, video::SColor(255,200,200,200));
            smgr->drawAll();
            driver->endScene();

            int fps = driver->getFPS();

            if (lastFPS != fps)
            {
                stringw str = L"Irrlicht Engine - Quake 3 Map example [";
                str += driver->getName();
                str += "] FPS:";
                str += fps;

                device->setWindowCaption(str.c_str());
                lastFPS = fps;
            }
        }
        else
            device->yield();
    }

    device->drop();
    
    return 0;
}