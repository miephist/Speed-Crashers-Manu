// Fichero de pruebas para SFML, Irrlicht y C++

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


enum
{
    // I use this ISceneNode ID to indicate a scene node that is
    // not pickable by getSceneNodeAndCollisionPointFromRay()
    ID_IsNotPickable = 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be picked by ray selection.
    IDFlag_IsPickable = 1 << 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be highlighted.  In this example, the
    // homonids can be highlighted, but the level mesh can't.
    IDFlag_IsHighlightable = 1 << 1
};

int main(){

    // Al tener el include driverChoice.h podemos llamar a la funcion
    // driverChoiceConsole() para que nos haga la eleccion de drivers 
    E_DRIVER_TYPE driverType=driverChoiceConsole();
    if (driverType==EDT_COUNT)
        return 1;

    // Creamos el objeto principal para usar el motor
    IrrlichtDevice *device =
        createDevice(driverType, dimension2d<u32>(640, 480), 16, false);

    // Si no podemos crearlo con el driver seleccionado devolvemos 1
    if (device == 0)
        return 1;

    // Cambiamos la ruta en la que nos coge los archivos
    device->getFileSystem()->changeWorkingDirectoryTo("../ejemplo7");

    // Cargamos el driver y la escena
    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();

    // Cargamos el zip con todo el mapeado
    device->getFileSystem()->addFileArchive("../ejemplo7/resources/map-20kdm2.pk3");

    // Obtenemos el mapa
    IAnimatedMesh* q3levelmesh = smgr->getMesh("20kdm2.bsp");
    IMeshSceneNode* q3node = 0;

    // La malla de Quake es seleccionable pero no se resalta
    if (q3levelmesh)
        q3node = smgr->addOctreeSceneNode(q3levelmesh->getMesh(0), 0, IDFlag_IsPickable);
    
    // Creamos un selector de triangulos
    scene::ITriangleSelector* selector = 0;

    // Al pasar por encima de cualquier elemento del mapa
    // se nos resaltara un triangulo    
    if (q3node)
    {
        q3node->setPosition(vector3df(-1350,-130,-1400));

        selector = smgr->createOctreeTriangleSelector(
                q3node->getMesh(), q3node, 128);
        q3node->setTriangleSelector(selector);
        // We're not done with this selector yet, so don't drop it.
    }

    // Set a jump speed of 3 units per second, which gives a fairly realistic jump
    // when used with the gravity of (0, -10, 0) in the collision response animator.
    ICameraSceneNode* camera =
        smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, ID_IsNotPickable, 0, 0, true, 3.f);
    camera->setPosition(vector3df(50,50,-60));
    camera->setTarget(vector3df(-70,30,-60));

    // Anyadimos las colisiones con gravedad (0, -10, 0)
    if (selector)
    {
        ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
            selector, // Selector de triángulos que especifica todas las colisiones posibles del mapa
            camera, // El objeto (nodo de la escena) es que afectado por la colision
            vector3df(30,50,30), // Especifica el tamanyo del objeto
            vector3df(0,-10,0), // Direccion y velocidad de la gravedad, poner a (0,0,0) para desactivarla
            vector3df(0,30,0)); // Traslacion del objeto para dar perspectiva de humano (por eso lo trasladamos 30 posiciones en el eje Y)
        selector->drop(); // As soon as we're done with the selector, drop it.
        camera->addAnimator(anim);
        anim->drop();  // And likewise, drop the animator when we're done referring to it.
    }

    ISceneNode* elementos = 0;
    // Creamos un cubo para la escena (podemos crear otra forma geometrica)
    // Creamos un cubo para la escena (podemos crear otra forma geometrica)
    ISceneNode* coche = smgr->addCubeSceneNode(10.0f, 0, ID_IsNotPickable, vector3df(0,0,0), 
    vector3df(0,0,0), vector3df(2.0f, 6.0f, 2.0f));
    if (coche)
    {
        coche->setPosition(vector3df(0,0,30));
        coche->setMaterialTexture(0, driver->getTexture("../ejemplo4/resources/wall.bmp"));
        coche->setMaterialFlag(EMF_LIGHTING, false);

    }
    
    selector = smgr->createTriangleSelectorFromBoundingBox(coche);
    coche -> setTriangleSelector(selector);
    

    // Anyadimos las colisiones con gravedad (0, -10, 0)
    if (selector)
    {
        ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
            selector, // Selector de triángulos que especifica todas las colisiones posibles del mapa
            camera, // El objeto (nodo de la escena) es que afectado por la colision
            vector3df(20,40,20), // Especifica el tamanyo del objeto
            vector3df(0,0,0), // Direccion y velocidad de la gravedad, poner a (0,0,0) para desactivarla
            vector3df(0,0,0)); // Traslacion del objeto para dar perspectiva de humano (por eso lo trasladamos 30 posiciones en el eje Y)
        selector->drop(); // As soon as we're done with the selector, drop it.
        camera->addAnimator(anim);
        anim->drop();  // And likewise, drop the animator when we're done referring to it.
    }


    // Creamos un cubo para la escena (podemos crear otra forma geometrica)
    elementos = smgr->addCubeSceneNode(10.0f, 0, ID_IsNotPickable, vector3df(0,0,0), 
    vector3df(0,0,0), vector3df(2.0f, 6.0f, 2.0f));
    if (elementos)
    {
        elementos->setPosition(vector3df(0,0,100));
        elementos->setMaterialTexture(0, driver->getTexture("../ejemplo4/resources/wall.bmp"));
        elementos->setMaterialFlag(EMF_LIGHTING, false);

    }
    
    selector = smgr->createTriangleSelectorFromBoundingBox(elementos);
    elementos -> setTriangleSelector(selector);
    selector->drop();

    // Anyadimos las colisiones con gravedad (0, -10, 0)
    if (selector)
    {
        ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
            selector, // Selector de triángulos que especifica todas las colisiones posibles del mapa
            camera, // El objeto (nodo de la escena) es que afectado por la colision
            vector3df(20,40,20), // Especifica el tamanyo del objeto
            vector3df(0,0,0), // Direccion y velocidad de la gravedad, poner a (0,0,0) para desactivarla
            vector3df(0,0,0)); // Traslacion del objeto para dar perspectiva de humano (por eso lo trasladamos 30 posiciones en el eje Y)
        selector->drop(); // As soon as we're done with the selector, drop it.
        camera->addAnimator(anim);
        anim->drop();  // And likewise, drop the animator when we're done referring to it.
    }

    device->getCursorControl()->setVisible(false);

    // Remember which scene node is highlighted
    ISceneNode* highlightedSceneNode = 0;
    ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
    int lastFPS = -1;

    while(device->run())
    if (device->isWindowActive())
    {
        driver->beginScene(true, true, 0);
        smgr->drawAll();        

        // We're all done drawing, so end the scene.
        driver->endScene();

        int fps = driver->getFPS();

        if (lastFPS != fps)
        {
            core::stringw str = L"Collision detection example - Irrlicht Engine [";
            str += driver->getName();
            str += "] FPS:";
            str += fps;

            device->setWindowCaption(str.c_str());
            lastFPS = fps;
        }
    }

    device->drop();

    return 0;

}