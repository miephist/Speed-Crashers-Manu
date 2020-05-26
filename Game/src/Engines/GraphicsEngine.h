#pragma once
#include "structs.h"

class GraphicsEngine{

public:

    // Destructor
    ~GraphicsEngine();

    // Setters
    void setCampo();

    // Getters
    irr::IrrlichtDevice* getDevice();
    irr::video::IVideoDriver* getDriver();
    irr::scene::ISceneManager* getScene();
    irr::gui::IGUIEnvironment* getInterface();

    void createText(irr::gui::IGUIStaticText *newTextUI, irr::core::stringw newText);
    void addText(irr::core::stringw newText);
    void eraseText();
    void engineClear();

    static GraphicsEngine* getInstancia();

private:
    // Constructor
    GraphicsEngine();

    //Instancia
    static GraphicsEngine* instancia;

    // Parametros dispositivo
    irr::IrrlichtDevice* device;
    irr::video::IVideoDriver* driver;
    irr::scene::ISceneManager* smgr;
    irr::gui::IGUIEnvironment* interface;

    // Texto para la interfaz
    irr::gui::IGUIStaticText *textoUI;
    irr::core::stringw text;
};