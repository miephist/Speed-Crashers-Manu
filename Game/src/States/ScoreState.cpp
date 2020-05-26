#include "ScoreState.h"
#include "../Game/Game.h"

ScoreState::ScoreState(){

    Init();

}

ScoreState::~ScoreState(){
     
    ITEngine::getInstancia()->cleanHUD();
    
    ITEngine::getInstancia()->resetScene();

    delete Shader;
}

void ScoreState::Init(){

    oldState = GLFW_RELEASE;
    newState = -1;
    isPressed = 0;

    oldState2 = GLFW_RELEASE;
    newState2 = -1;

    actualOption = 0;
    entro = false;

    // Indicamos propiedades de OpenGL para el HUD
    ITEngine::getInstancia()->setHUDProperties();

    // Creamos los shaders
    Shader = ITEngine::getInstancia()->createShader("media/shaders/HUD/vertexShader.glsl", "media/shaders/HUD/fragmentShader.glsl");

    // Creamos la estructura del menu
    ITEngine::getInstancia()->newHud("PostgameMenu");
    ITEngine::getInstancia()->getActiveHud()->addElement("fondo", "media/GUI/PostGame/Postgame1.png");

    // Marcador Azul
    std::stringstream blue;

    blue << "media/GUI/Numbers/" << Options::getInstancia()->getFinalScoreBlue() << ".png";
    
    std::string stringB = blue.str();

    rutaB = new char[stringB.size()+1];
    std::strncpy(rutaB, stringB.c_str(), stringB.size()+1);


    ITEngine::getInstancia()->getActiveHud()->addElement("Score Blue", rutaB);
    ITEngine::getInstancia()->getActiveHud()->scaleElement("Score Blue",0.8,0.8);
    ITEngine::getInstancia()->getActiveHud()->traslateElement("Score Blue", -0.3, 0.35);


    // Marcador Rojo

    std::stringstream red;

    red << "media/GUI/Numbers/" << Options::getInstancia()->getFinalScoreRed() << ".png";
    
    std::string stringR = red.str();

    rutaR = new char[stringR.size()+1];
    std::strncpy(rutaR, stringR.c_str(), stringR.size()+1);

    ITEngine::getInstancia()->getActiveHud()->addElement("Score Red", rutaR);
    ITEngine::getInstancia()->getActiveHud()->scaleElement("Score Red",0.8,0.8);
    ITEngine::getInstancia()->getActiveHud()->traslateElement("Score Red", -0.65, 0.35);

    // Motor de audio
    if(!CAudioEngine::getInstancia()->IsEventPlaying("event:/Musica/arcade_music"))
        CAudioEngine::getInstancia()->PlayEvent("event:/Musica/arcade_music");

}

void ScoreState::Update(){

    // Updateamos sonidos
    CAudioEngine::getInstancia()->Update();

    // Dibujamos el menu
    Render();

    // Comprobamos las teclas
    CheckInputs();

}

void ScoreState::Render(){

    // Dibujarlo por pantalla
    ITEngine::getInstancia()->drawHudMenus(Shader);

}

void ScoreState::CheckInputs(){
    
     // Parametros mando
    bool controller = false;
    const float* axes = nullptr;
    const unsigned char* buttons = nullptr;
    const char* name = nullptr;

    // Cerramos el juego en caso de pulsar ESC
    if(glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(ITEngine::getInstancia()->getWindow(), GLFW_TRUE);
    }

    // Comprobamos si se conecta un mando
    if(glfwJoystickPresent(GLFW_JOYSTICK_1) == 1){
        // Contador para los ejes
        int axesCount;
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

        // Contador para los botones
        int buttonsCount;
        buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonsCount);

        // Guardamos el nombre
        name = glfwGetJoystickName(GLFW_JOYSTICK_1);

        // Indicamos que el controlador/pad esta activo
        controller = true;
    }

    // Averiguamos opcion del menu en la que nos encontramos
    if(glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS || (controller && (GLFW_PRESS == buttons[13] || 0.5f <= axes[1]))){
        if(!entro){
            if(actualOption <= 0)
                actualOption++;

            entro = true;
        }
    }else if(glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_UP) == GLFW_PRESS || (controller && (GLFW_PRESS == buttons[11] || -0.5f >= axes[1]))){
        if(!entro){
            if(actualOption > 0)
                actualOption--;

            entro = true;
        }
    }else{
        entro = false;
    }
    
    // Actualizamos estado tecla enter

    newState = glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_ENTER);
    
    if(controller == true)
        newState2 = buttons[0];

    if(newState == GLFW_RELEASE && oldState == GLFW_PRESS || (controller && newState2 == GLFW_RELEASE && oldState2 == GLFW_PRESS)){
        isPressed = 1;
    }

    oldState = newState;
    oldState2 = newState2;

    if(entro == true || isPressed == 1){
        switch(actualOption){
            // Reiniciamos partida
            case 0:
            {
                if(isPressed == 1){
                    // Borramos resultado
                    ITEngine::getInstancia()->getActiveHud()->deleteElement("Score Blue");
                    ITEngine::getInstancia()->getActiveHud()->deleteElement("Score Red");

                    Auxiliar::states actualState = Auxiliar::GameState;
                    Game::getInstancia()->changeState(actualState);
                }else{
                    ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/PostGame/Postgame1.png");   
                }
            }
            break;

            // Volvemos al menu principal
            case 1:
            {
                if(isPressed == 1){
                    // Borramos resultado
                    ITEngine::getInstancia()->getActiveHud()->deleteElement("Score Blue");
                    ITEngine::getInstancia()->getActiveHud()->deleteElement("Score Red");

                    Auxiliar::states actualState = Auxiliar::MenuState;
                    Game::getInstancia()->changeState(actualState);
                }else{
                    ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/PostGame/Postgame2.png");   
                }
            }
            break;
        }
    }
}