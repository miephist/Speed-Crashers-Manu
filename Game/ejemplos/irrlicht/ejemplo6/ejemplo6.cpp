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

    // Al tener el include driverChoice.h podemos llamar a la funcion
    // driverChoiceConsole() para que nos haga la eleccion de drivers 
    E_DRIVER_TYPE driverType=driverChoiceConsole();
    if (driverType==EDT_COUNT)
        return 1;

    // Creamos el objeto principal para usar el motor
    IrrlichtDevice *device = createDevice(driverType,
        core::dimension2d<u32>(512, 384));

    // Si no podemos crearlo con el driver seleccionado devolvemos 1
    if (device == 0)
        return 1;

    device->setWindowCaption(L"Irrlicht Engine - 2D Graphics Demo");

    // Cambiamos la ruta en la que nos coge los archivos
    device->getFileSystem()->changeWorkingDirectoryTo("../ejemplo6");

    // Creamos el driver
    IVideoDriver* driver = device->getVideoDriver();

    // Cargamos la imagen del menu con el color de la posicion (0,0)
    ITexture* images = driver->getTexture("../ejemplo6/resources/2ddemo.png");
    driver->makeColorKeyTexture(images, core::position2d<s32>(0,0));

    // Cargamos el texto con dos fuentes diferentes siendo la primera por defecto
    // y la segunda cargando una imagen
    IGUIFont* font = device->getGUIEnvironment()->getBuiltInFont();
    IGUIFont* font2 =
        device->getGUIEnvironment()->getFont("../ejemplo6/resources/fonthaettenschweiler.bmp");

    // Creamos la posicion inicial de los dos demonios voladores
    rect<s32> imp1(349,15,385,78);
    rect<s32> imp2(387,15,423,78);

    // Render 2D para los materiales
    driver->getMaterial2D().TextureLayer[0].BilinearFilter=true;
    driver->getMaterial2D().AntiAliasing=EAAM_FULL_BASIC;

    // Dibujamos todos los materiales 2D (no habria problema en añadir objetos 3D)
    while(device->run() && driver)
    {
        if (device->isWindowActive())
        {
            u32 time = device->getTimer()->getTime();

            driver->beginScene(true, true, video::SColor(255,120,102,136));

            // Dibujamos el sprite 2D del mapa
            driver->draw2DImage(images, core::position2d<s32>(50,50),
                core::rect<s32>(0,0,342,224), 0,
                SColor(255,255,255,255), true);

            // Dibujamos el primer demonio volador
            driver->draw2DImage(images, core::position2d<s32>(164,125),
                (time/500 % 2) ? imp1 : imp2, 0,
                SColor(255,255,255,255), true);

            // Dibujamos el segundo demonio volador con un bucle de parpadeo de color
            driver->draw2DImage(images, core::position2d<s32>(270,105),
                (time/500 % 2) ? imp1 : imp2, 0,
                SColor(255,(time) % 255,255,255), true);

             // Dibujamos un texto estatico
            if (font)
                font->draw(L"This demo shows that Irrlicht is also capable of drawing 2D graphics.",
                    rect<s32>(130,10,300,50),
                    SColor(255,255,255,255));

            // Dibujamos un texto con un bucle de parpadeo de color
            if (font2)
                font2->draw(L"Also mixing with 3d graphics is possible.",
                    rect<s32>(130,20,300,60),
                    SColor(255,time % 255,time % 255,255));

            // Dibujamos el logo de Irrlicht
            driver->enableMaterial2D();
            driver->draw2DImage(images, core::rect<s32>(10,10,108,48),
                core::rect<s32>(354,87,442,118));
            driver->enableMaterial2D(false);

            // Dibujamos el hover de donde este apuntando el raton
            core::position2d<s32> m = device->getCursorControl()->getPosition();
            driver->draw2DRectangle(video::SColor(100,255,255,255),
                core::rect<s32>(m.X-20, m.Y-20, m.X+20, m.Y+20));

            driver->endScene();
        }
    }

    device->drop();    

    return 0;
}