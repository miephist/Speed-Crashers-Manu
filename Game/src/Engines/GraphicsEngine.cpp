#include "GraphicsEngine.h"

GraphicsEngine *GraphicsEngine::instancia = nullptr;

GraphicsEngine::GraphicsEngine(){
    
    // Inicializamos GLFW para el temporizador
    if(!glfwInit()){
    }

    // Creamos el dispositivo
    device = irr::createDevice(irr::video::EDT_OPENGL, // Drivers
            irr::core::dimension2d<irr::u32>(1280, 720), // Tamanyo ventana
            16, // Bits
            false, // Pantalla completa
            false, // Buffer
            false, // Vsync
            0); // Recibidor de eventos

    if(!device)

    // Indicamos nombre de la ventana
    device->setWindowCaption(L"Speed Crashers");

    device->setResizable(false);

    // Le indicamos localización de los resources
    device->getFileSystem()->changeWorkingDirectoryTo("media");

    // Inicializamos los demas parametros
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    interface = device->getGUIEnvironment();
    
}

GraphicsEngine::~GraphicsEngine(){

    instancia = nullptr;
}

void GraphicsEngine::createText(irr::gui::IGUIStaticText *newTextUI, irr::core::stringw newText){

    textoUI = newTextUI;
    text = newText;

}

void GraphicsEngine::addText(irr::core::stringw newText){

    text += newText;
    textoUI->setText(text.c_str());

}

void GraphicsEngine::setCampo(){

    // Creamos el campo para la escena
    irr::scene::ISceneNode *campo = smgr->addMeshSceneNode(smgr->getMesh("Campo_muro2.obj"));

    if(campo){
        campo->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        campo->setMaterialTexture(0, driver->getTexture("cubetexture.png"));
    }
}

GraphicsEngine *GraphicsEngine::getInstancia(){

    if(instancia == nullptr)
        instancia = new GraphicsEngine();

    return instancia;

}

irr::IrrlichtDevice *GraphicsEngine::getDevice(){

    return device;

}

irr::video::IVideoDriver *GraphicsEngine::getDriver(){

    return driver;

}

irr::scene::ISceneManager *GraphicsEngine::getScene(){

    return smgr;

}

irr::gui::IGUIEnvironment* GraphicsEngine::getInterface(){

    return interface;

}

void GraphicsEngine::eraseText(){

    text = "";

}

void GraphicsEngine::engineClear(){

    smgr->clear();
}