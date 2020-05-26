#include "InitState.h"
#include "../Game/Game.h"

InitState::InitState(){

    Init();

}

InitState::~InitState(){
     
    ITEngine::getInstancia()->cleanHUD();
    
}

void InitState::Init(){

    // Indicamos propiedades de OpenGL para el HUD
    ITEngine::getInstancia()->setHUDProperties();

    // Creamos los shaders
    Shader = ITEngine::getInstancia()->createShader("media/shaders/HUD/vertexShader.glsl", "media/shaders/HUD/fragmentShader.glsl");

    // Creamos la estructura del menu
    ITEngine::getInstancia()->newHud("InitMenu");
    ITEngine::getInstancia()->getActiveHud()->addElement("fondo", "media/GUI/Init/Init.png");

    carga = 0;

}

void InitState::Update(){

    // Dibujamos el menu
    Render();

    carga++;

    if(carga == 3){
        Auxiliar::states actualState = Auxiliar::MenuState;
        Game::getInstancia()->changeState(actualState);
    }
}

void InitState::Render(){

    // Dibujarlo por pantalla
    ITEngine::getInstancia()->drawHudMenus(Shader);

}