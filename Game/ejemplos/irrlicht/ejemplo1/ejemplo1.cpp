/*

    En este ejemplo podemos ver las siguientes cosas:
        - Crear primera escena.
        - Carga de modelado.
        - Anyadir animacion al modelado.
        - Texto simple a la escena.

*/

#include <irrlicht/irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

 
 int main(){
 
    /* 
    Explicacion mas detallada del codigo en el siguiente enlace:
        http://irrlicht.sourceforge.net/docu/example001.html
    */

    // Creamos el objeto principal para usar el motor
    IrrlichtDevice *device =
        createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
            false, false, false, 0);

    // Si no es creado devolvemos uno
    if (!device)
        return 1;

    // Cambiamos la ruta en la que nos coge los archivos
    device->getFileSystem()->changeWorkingDirectoryTo("../ejemplo1");

    // Le damos un titulo a la ventana que se nos abrira
    device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo"); 

    // Obtenemos el puntero del driver, la escena y el entorno grafico del usuario
    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();   

    // Mostramos por pantalla un texto
    guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
        rect<s32>(10,10,260,22), true); 

    // Cargamos el modelado/malla
    IAnimatedMesh* mesh = smgr->getMesh("../ejemplo1/resources/sydney.md2");
    if (!mesh)
    {
        device->drop();
        return 1;
    }

    // Le damos una animacion al modelo
    IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );

    if (node)
    {
        // Desactivamos la luz al no tener iluminacion global
        node->setMaterialFlag(EMF_LIGHTING, false);
        // Realizamos un bucle de la animacion
        node->setMD2Animation(scene::EMAT_STAND);
        // Anyadimos la textura al modelado
        node->setMaterialTexture( 0, driver->getTexture("../ejemplo1/resources/sydney.bmp") );
    }

    // Situamos la camara en el escenario
    smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

    // Ejecutamos el juego hasta que se cierre la ventana o se pulse ALT+F4
    while(device->run())
    {

        // Dibujamos todo por pantalla
        driver->beginScene(true, true, SColor(255,100,101,140));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }

        device->drop();

    return 0;

 }