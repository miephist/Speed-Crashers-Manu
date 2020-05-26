#include "MenuState.h"
#include "../Game/Game.h"
#include <iomanip>
MenuState::MenuState(){

    Init();
    //camara
    glm::vec3 pos=glm::vec3(-50.0f,130.0f,-280.0f);
    glm::vec3 tar=glm::vec3(-50.0f,120.0f,0.0f);
    viewport v;
    v.near = 0.1f;
    v.far = 1000.0f;
    v.fov = 60.0f;
    v.ratio = 1.77777777f;
    ITEngine::getInstancia()->createCamera(pos, tar, v);


    //pnjs
    act=0;

    std::string ruta=std::string("media/Animaciones/RENE_IDLE_24FPS_OBJ_Seq/RENE_IDLE_24FPS.");
    std::string ext=std::string(".obj");
    int ini=32;
    int fin=81;


    const char* text="media/Animaciones/RENE_IDLE_24FPS_OBJ_Seq/Rene_Nuevos_UV_lambert3SG_BaseColor.png";
    pnjAct.push_back(ITEngine::getInstancia()->createAnimation(ruta,ext,ini,fin, text));
    pnjAct.at(0)->setVisible(false);
    pnjAct.at(0)->setScale(glm::vec3(1.2f,1.2f,1.2f));
    pnjAct.at(0)->setPosition(glm::vec3(0.f,-20.f,-50.f));

 
    ruta=std::string("media/Animaciones/RATH_IDLE_24FPS_OBJ_Seq/RATH_IDLE_24FPS.");
    ext=std::string(".obj");
    
    ini=48;
    fin=96;

    const char* text2="media/Animaciones/RATH_IDLE_24FPS_OBJ_Seq/rath_animation_initialShadingGroup_BaseColor.png";
    pnjAct.push_back(ITEngine::getInstancia()->createAnimation(ruta,ext,ini,fin, text2));                  
    pnjAct.at(1)->setVisible(false);

    //milo
    ruta=std::string("media/Animaciones/Milo/milo-juego-");
    ext=std::string(".obj");
    
    ini=0;
    fin=1;

    const char* text3="media/Animaciones/Milo/milo_uv_BaseColor.png";
    pnjAct.push_back(ITEngine::getInstancia()->createAnimation(ruta,ext,ini,fin, text3));                  
    pnjAct.at(2)->setVisible(false);
    pnjAct.at(2)->setScale(glm::vec3(1.2f,1.2f,1.2f));
    pnjAct.at(2)->setPosition(glm::vec3(0.f,-20.f,-50.f));

    //k-pucha
    ruta=std::string("media/Animaciones/k-pucha/k-pucha_juego");
    ext=std::string(".obj");
    
    ini=0;
    fin=1;

    const char* text4="media/Animaciones/k-pucha/k-pucha_BaseColor.png";
    pnjAct.push_back(ITEngine::getInstancia()->createAnimation(ruta,ext,ini,fin, text4));                  
    pnjAct.at(3)->setVisible(false);
    pnjAct.at(3)->setScale(glm::vec3(1.2f,1.2f,1.2f));
    pnjAct.at(3)->setPosition(glm::vec3(0.f,-20.f,-50.f));
}

MenuState::~MenuState(){

    multiplayer = false;
     
    ITEngine::getInstancia()->cleanHUD();
    

    delete Shader;
    delete shaderModelo;
}


void MenuState::changePnj(int selec){
    pnjAct.at(act)->setVisible(false);
    //pnjAct.at(act)->reset();
    pnjAct.at(selec)->setVisible(true);
    act=selec;
}

void MenuState::noPnj(){
    for(int z=0;z<pnjAct.size();z++){
        pnjAct.at(z)->setVisible(false);
    }
}


void MenuState::Init(){

    // Tecla Enter
    oldState = GLFW_RELEASE;
    newState = -1;
    isPressed = 0;

    oldState2 = GLFW_RELEASE;
    newState2 = -1;

    actualMenu = 0;
    lastMenu = actualMenu;
    actualOption = 0;
    numOptions = 3;
    entro = false;

    multiplayer = false;

    carga = 0;
    cont = 0;
    actualMode = 1;
    actualTimer = 2;

    // Indicamos propiedades de OpenGL para el HUD
    ITEngine::getInstancia()->setHUDProperties();

    // Creamos los shaders
    Shader = ITEngine::getInstancia()->createShader("media/shaders/HUD/vertexShader.glsl", "media/shaders/HUD/fragmentShader.glsl");
    shaderModelo = ITEngine::getInstancia()->createShader("media/shaders/vertexShader.glsl", "media/shaders/fragmentShader.glsl");

    // Creamos la estructura del menu
    ITEngine::getInstancia()->newHud("MainMenu");
    ITEngine::getInstancia()->getActiveHud()->addElement("fondo", "media/GUI/Start/Play.png");

    // Inicializamos juego con menu principal
    startMenu();

    // Motor de audio
    if(!CAudioEngine::getInstancia()->IsEventPlaying("event:/Musica/arcade_music"))
        CAudioEngine::getInstancia()->PlayEvent("event:/Musica/arcade_music");

}

void MenuState::Update(){

    // Updateamos sonidos
    CAudioEngine::getInstancia()->Update();

    if(multiplayer == true && isServer == true){
        Server::getInstancia()->Update();
    }else if(multiplayer == true && isServer == false){
        Client::getInstancia()->Update();
    }

    // Dibujamos el menu
    Render();

    // Comprobamos las teclas
    if(carga == 0){
        CheckInputs();
    }else{
    // Necesitamos esperarnos 3 iteraciones para el dibujado
        carga++;
        if(carga == 3){
            Auxiliar::states actualState = Auxiliar::GameState;
            Game::getInstancia()->changeState(actualState);
        }
    }
}

void MenuState::CheckInputs(){

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
            if(actualMenu !=4){
                if(actualOption < numOptions)
                    actualOption++;
                else if(actualOption == numOptions)
                    actualOption = 0;
            }else{
                if(cont == 0){
                    cont++;
                    actualOption = actualMode;
                }else if(cont == 1){
                    cont++;
                    actualOption = actualTimer;
                }else{
                    cont = 0;
                    actualOption = 0;
                }
            }

            entro = true;
        }
    }else if(glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_UP) == GLFW_PRESS || (controller && (GLFW_PRESS == buttons[11] || -0.5f >= axes[1]))){
        if(!entro){
            if(actualMenu !=4){
                if(actualOption > 0)
                    actualOption--;
                else if(actualOption == 0)
                    actualOption = numOptions;
            }else{
                if(cont == 0){
                    cont = 2;
                    actualOption = actualTimer;
                }else if(cont == 1){
                    cont--;
                    actualOption = 0;
                }else if(cont == 2){
                    cont--;
                    actualOption = actualMode;
                } 
            }

            entro = true;
        }
    }else if(glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS || (controller && 0.5f <= axes[0])){
        // Menu opciones modo y timer
        if(!entro && actualMenu == 4){
            if(actualOption == 0)
                actualOption = 3;
            else if(actualOption == 1)
                actualOption = 4;
            else if(actualOption == 2)
                actualOption = 6;
            else if(actualOption == 3)
                actualOption = 0;
            else if(actualOption >= 4 && actualOption <= 7){
                actualOption++;
                if(actualOption == 6){
                    mode = true;
                    actualOption = 8;
                }
            }

            entro = true;
            derecha = true;
        // Menu opciones graficas y sonidos
        }else if(!entro && (actualMenu == 5 || actualMenu == 6 || actualMenu == 7)){
            if(actualOption < numOptions)
                actualOption++;
            else if(actualOption == numOptions)
                actualOption = 0;

            derecha = true;
            entro = true;
        }
    }else if(glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS || (controller && -0.5f >= axes[0])){
        // Menu opciones modo y timer
        if(!entro && actualMenu == 4){
            if(actualOption == 0)    
                actualOption = 3;
            else if(actualOption == 1)
                actualOption = 5;
            else if(actualOption == 2)
                actualOption = 7;
            else if(actualOption == 3)
                actualOption = 0;
            else if(actualOption >= 4 && actualOption <= 7){
                actualOption--;
                if(actualOption == 3){
                    mode = true;
                    actualOption = 1;
                }else if(actualOption == 5){
                    mode = true;
                    actualOption = 2;
                }
            }
                
            entro = true;
            izquierda = true;
        // Menu opciones graficas y sonidos
        }else if(!entro && (actualMenu == 5 || actualMenu == 6 || actualMenu == 7)){
            if(actualOption > 0)
                actualOption--;
            else if(actualOption == 0)
                actualOption = numOptions;

            izquierda = true;
            entro = true;
        } 
    }else{
        entro = false;
        derecha = false;
        izquierda = false;
    }

    // Si hemos cambiado de menu entonces reseteamos el enter
    if(actualMenu != lastMenu){
        isPressed = -1;
        lastMenu = actualMenu;
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

    // En caso de que se haya pulsado enter
    if(entro == true || isPressed == 1){
        if(!CAudioEngine::getInstancia()->IsEventPlaying("event:/SFX/Interfaz/Boton_menu"))
        CAudioEngine::getInstancia()->PlayEvent("event:/SFX/Interfaz/Boton_menu");
        // Switch menus
        switch(actualMenu){
            // Menu principal
            case 0:
            
                // Switch opciones menu
                switch(actualOption){
                    case 0:
                    { 
                        if(isPressed == 1){
                            // Seleccion de personaje
                            actualMenu = 3;
                            actualOption = 0;
                            numOptions = 5;
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Rath.png"); 
                            changePnj(1);

                            if(CAudioEngine::getInstancia()->IsEventPlaying("event:/Voces/Personaje2/SinPiedad"))
                                CAudioEngine::getInstancia()->StopEvent("event:/Voces/Personaje2/SinPiedad",true);
                             CAudioEngine::getInstancia()->PlayEvent("event:/Voces/Personaje3/MejorHago");
                            

                        }else{
                            // Cambiar textura
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Start/Play.png");   
                        }
                    }
                    break;

                    case 1: 
                    {
                        if(isPressed == 1){
                            // Seteamos pantalla partida
                            Options::getInstancia()->setCoop(true);
                            // Seleccion de personaje
                            actualMenu = 3;
                            actualOption = 0;
                            numOptions = 5;
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Rath.png");

                            ITEngine::getInstancia()->getActiveHud()->addElement("Multiplayer", "media/GUI/Multiplayer/Multiplayer mode.png");
                            ITEngine::getInstancia()->getActiveHud()->traslateElement("Multiplayer", -0.6, 0.55);
                        }else{
                            // Cambiar textura
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Start/Multiplayer.png");
                        } 
                    }
                    break;

                    case 2:
                    {
                        if(isPressed == 1){
                            // Menu de opciones
                            actualMenu = 2;
                            actualOption = 0;
                            optionsMenu(); 
                        }else{
                            // Cambiar textura
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Start/Options.png");
                        }
                    }
                    break;

                    case 3: 
                    {
                        if(isPressed == 1){
                            // Salir
                            glfwSetWindowShouldClose(ITEngine::getInstancia()->getWindow(), GLFW_TRUE); 
                        }else{
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Start/Exit.png");
                        }
                    }
                    break;
                }
            break;

            // Menu multijugador
            case 1:
            break;

            // Menu opciones
            case 2:
                switch(actualOption){
                    // Graficos
                    case 0:
                    { 
                        if(isPressed == 1){
                            // Ir dentro del recuadro de las opciones graficas para poder cambiarlas
                            actualMenu = 5;
                            actualOption = 0;
                            numOptions = 2;

                            // Circulos para la seleccion de opciones
                            ITEngine::getInstancia()->getActiveHud()->addElement("circleResolution", "media/GUI/Select/Settings/Seleccion.png");
                            ITEngine::getInstancia()->getActiveHud()->scaleElement("circleResolution", 0.7, 0.7);
                            ITEngine::getInstancia()->getActiveHud()->traslateElement("circleResolution", -0.1, 0.05);

                        }else{
                            // Cambiar textura
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Options/Graphics.png");
                        }
                    }
                    break;

                    // Sonidos
                    case 1: 
                    {
                        if(isPressed == 1){
                            // Ir dentro del recuadro de las opciones sonoras para poder cambiarlas
                            actualMenu = 6;
                            actualOption = 0;
                            numOptions = 1;

                            // Circulos para la seleccion de opciones
                            ITEngine::getInstancia()->getActiveHud()->addElement("circleSound", "media/GUI/Select/Settings/Seleccion.png");
                            ITEngine::getInstancia()->getActiveHud()->scaleElement("circleSound", 0.7, 0.7);
                            ITEngine::getInstancia()->getActiveHud()->traslateElement("circleSound", -0.1, 0);
                        }else{
                            // Cambiar textura
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Options/Sounds.png");
                        } 
                    }
                    break;

                    // Camara
                    case 2:
                    {
                        if(isPressed == 1){
                            // Ir dentro del recuadro de las opciones sonoras para poder cambiarlas
                            actualMenu = 7;
                            actualOption = 0;
                            numOptions = 5;

                            // Circulos para la seleccion de opciones
                            ITEngine::getInstancia()->getActiveHud()->addElement("circleCamera", "media/GUI/Select/Settings/Seleccion.png");
                            ITEngine::getInstancia()->getActiveHud()->scaleElement("circleCamera", 0.7, 0.7);
                            ITEngine::getInstancia()->getActiveHud()->traslateElement("circleCamera", -0.1, 0.05);
                        }else{
                            // Cambiar textura
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Options/Camera.png");
                        }
                    }
                    break;

                    // Volver
                    case 3:
                    { 
                        if(isPressed == 1){
                            // Volver al menu principal
                            actualMenu = 0;
                            actualOption = 2;
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Start/Options.png");

                        }else{
                            // Cambiar textura
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Options/Return.png");
                        }
                    }
                    break;
                }
            break;

            //Menu seleccion personajes
            case 3:
                switch(actualOption){
                    //Primer personaje
                    case 0:
                    {
                        if(isPressed == 1){
                            // Seteamos coche en funcion del personaje
                            Options::getInstancia()->setCar(1);
                            // ¿Pantalla de carga?
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Loading Controls.png"); 
                            // Iniciamos modo offline contra IA
                            carga++;
                            ITEngine::getInstancia()->resetScene();
                        }else{
                            // Cambiar textura
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Rath.png");
                            changePnj(1);
                             if(CAudioEngine::getInstancia()->IsEventPlaying("event:/Voces/Personaje2/SinPiedad"))
                                CAudioEngine::getInstancia()->StopEvent("event:/Voces/Personaje2/SinPiedad",true);
                                
                            CAudioEngine::getInstancia()->PlayEvent("event:/Voces/Personaje3/MejorHago");

                        }
                    }
                    break;

                    //Segundo personaje
                    case 1:
                    {
                        if(isPressed == 1){
                            // Seteamos coche en funcion del personaje
                            Options::getInstancia()->setCar(2);
                            // ¿Pantalla de carga?
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Loading Controls.png"); 
                            // Iniciamos modo offline contra IA
                            carga++;
                            ITEngine::getInstancia()->resetScene();
                        }else{
                            // Cambiar textura
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Rene.png");
                            changePnj(0);

                             if(CAudioEngine::getInstancia()->IsEventPlaying("event:/Voces/Personaje3/MejorHago"))
                                CAudioEngine::getInstancia()->StopEvent("event:/Voces/Personaje3/MejorHago",true);
                                
                            CAudioEngine::getInstancia()->PlayEvent("event:/Voces/Personaje2/SinPiedad");

                        }
                    }
                    break;

                    //Tercer personaje
                    case 2:
                    {
                        if(isPressed == 1){
                            // Seteamos coche en funcion del personaje
                            Options::getInstancia()->setCar(3);
                            // ¿Pantalla de carga?
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Loading Controls.png"); 
                            // Iniciamos modo offline contra IA
                            carga++;
                            ITEngine::getInstancia()->resetScene();
                        }else{
                            // Cambiar textura
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/KPucha.png");
                            changePnj(3);
                        }
                    }
                    break;
                    
                    //Cuarto personaje
                    case 3:
                    {
                        if(isPressed == 1){
                            // Seteamos coche en funcion del personaje
                            Options::getInstancia()->setCar(4);
                            // ¿Pantalla de carga?
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Loading Controls.png"); 
                            // Iniciamos modo offline contra IA
                            carga++;
                            ITEngine::getInstancia()->resetScene();
                        }else{
                            // Cambiar textura
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Milo.png");
                            changePnj(2);
                        }
                    }
                    break;

                    //Configuracion partido
                    case 4:
                    {
                        if(isPressed == 1){

                            actualMenu = 4;
                            actualOption = 0;
                            numOptions = 2;

                            // Para recolocar los circulos en caso de haber aplicado previamente algo
                            float sumMode = 0;
                            float sumTimer = 0;
                            
                            // Reseteamos valores
                            if(actualMode == 4)
                                sumMode = 0.5;
                            else if(actualMode == 5)
                                sumMode = 1.0;

                            if(actualTimer == 6)
                                sumTimer = 0.5;
                            else if(actualTimer == 7)
                                sumTimer = 1.0;

                            mode = false;

                            // Ocultamos animacion
                            noPnj();

                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Settings/Default.png");

                            // Circulos para la seleccion de opciones
                            ITEngine::getInstancia()->getActiveHud()->addElement("circleMode", "media/GUI/Select/Settings/Seleccion.png");
                            ITEngine::getInstancia()->getActiveHud()->scaleElement("circleMode", 0.7, 0.7);
                            ITEngine::getInstancia()->getActiveHud()->traslateElement("circleMode", -0.7 + sumMode, -0.10);

                            ITEngine::getInstancia()->getActiveHud()->addElement("circleTimer", "media/GUI/Select/Settings/Seleccion.png");
                            ITEngine::getInstancia()->getActiveHud()->scaleElement("circleTimer", 0.7, 0.7);
                            ITEngine::getInstancia()->getActiveHud()->traslateElement("circleTimer", -0.7 + sumTimer, -0.525);

                        }else{
                            // Cambiar textura
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Options.png");
                        }
                    }
                    break;

                    //Volver al menu principal
                    case 5:
                    {
                        if(isPressed == 1){

                            actualMenu = 0;
                            numOptions = 3;

                            if(Options::getInstancia()->getCoop()){
                                actualOption = 1;
                                Options::getInstancia()->setCoop(false);
                                ITEngine::getInstancia()->getActiveHud()->deleteElement("Multiplayer");
                                ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Start/Multiplayer.png"); 
                            }else{
                                actualOption = 0;
                                ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Start/Play.png"); 
                            }

                            noPnj();

                        }else{
                            // Cambiar textura
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Return.png");
                        }
                    }
                    break;
                }
            break;

            // Menu settings partido
            case 4:
                // Switch opciones menu
                switch(actualOption){
                    // Return
                    case 0:
                    { 
                        if(isPressed == 1){
                            
                            actualMenu = 3;
                            actualOption = 4;
                            numOptions = 5;

                            // Eliminamos los circulos
                            ITEngine::getInstancia()->getActiveHud()->deleteElement("circleMode");
                            ITEngine::getInstancia()->getActiveHud()->deleteElement("circleTimer");

                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Options.png");
                        }else{
                            // Cambiar textura
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Settings/Default.png"); 
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("circleTimer", "media/GUI/Select/Settings/Seleccion.png");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("circleMode", "media/GUI/Select/Settings/Seleccion.png");
                        }
                    }
                    break;

                    // First Mode
                    case 1:
                    { 
                        if(isPressed != 1){
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Settings/Select.png");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("circleMode", "media/GUI/Select/Settings/Seleccion Resaltada.png");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("circleTimer", "media/GUI/Select/Settings/Seleccion.png");

                            if(mode == true){
                                mode = false;
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleMode", -0.5, 0);
                            }
                        }

                        actualMode = actualOption;
                    }
                    break;

                    // First Timer
                    case 2:
                    { 
                        if(isPressed != 1){
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Settings/Select.png");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("circleMode", "media/GUI/Select/Settings/Seleccion.png");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("circleTimer", "media/GUI/Select/Settings/Seleccion Resaltada.png");

                            if(mode == true){
                                mode = false;
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleTimer", -0.5, 0);
                            }
                        }

                        actualTimer = actualOption;
                    }
                    break;

                    // Apply
                    case 3:
                    { 
                        if(isPressed == 1){
                            
                            // Aplicamos cambios elegidos
                            Options::getInstancia()->setMode(actualMode);
                            Options::getInstancia()->setTimer(actualTimer);

                            actualMenu = 3;
                            actualOption = 4;
                            numOptions = 5;

                            // Eliminamos los circulos
                            ITEngine::getInstancia()->getActiveHud()->deleteElement("circleMode");
                            ITEngine::getInstancia()->getActiveHud()->deleteElement("circleTimer");

                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Options.png");

                        }else{
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Settings/Apply.png");
                        }
                    }
                    break;

                    // Second Option Mode
                    case 4:
                    { 
                        if(isPressed != 1){

                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Settings/Select.png");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("circleMode", "media/GUI/Select/Settings/Seleccion Resaltada.png");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("circleTimer", "media/GUI/Select/Settings/Seleccion.png");

                            if(derecha == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleMode", 0.49, 0);
                            else if(izquierda == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleMode", -0.49, 0);

                            derecha = false;
                            izquierda = false;
                        }

                        actualMode = actualOption;
                    }
                    break;

                    // Third Option Mode
                    case 5:
                    { 
                        if(isPressed != 1){

                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Settings/Select.png");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("circleMode", "media/GUI/Select/Settings/Seleccion Resaltada.png");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("circleTimer", "media/GUI/Select/Settings/Seleccion.png");

                            if(derecha == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleMode", 0.5, 0);
                            else if(izquierda == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleMode", 0.99, 0);

                            derecha = false;
                            izquierda = false;
                        }

                        actualMode = actualOption;
                    }
                    break;

                    // Second Option Timer
                    case 6:
                    { 
                        if(isPressed != 1){

                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Settings/Select.png");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("circleMode", "media/GUI/Select/Settings/Seleccion.png");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("circleTimer", "media/GUI/Select/Settings/Seleccion Resaltada.png");

                            if(derecha == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleTimer", 0.49, 0);
                            else if(izquierda == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleTimer", -0.49, 0);

                            derecha = false;
                            izquierda = false;
                        }

                        actualTimer = actualOption;
                    }
                    break;

                    // Third Option Timer
                    case 7:
                    { 
                        if(isPressed != 1){

                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Select/Settings/Select.png");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("circleMode", "media/GUI/Select/Settings/Seleccion.png");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("circleTimer", "media/GUI/Select/Settings/Seleccion Resaltada.png");

                            if(derecha == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleTimer", 0.5, 0);
                            else if(izquierda == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleTimer", 0.99, 0);

                            derecha = false;
                            izquierda = false;
                        }

                        actualTimer = actualOption;
                    }
                    break;

                    // Vuelve circulos a posicion inicial
                    case 8:
                    { 
                        if(isPressed != 1){
                            if(derecha == true && mode == true){
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleMode", -0.99, 0);
                                mode = false;
                                actualOption = 1;
                            }else{
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleTimer", -0.99, 0);
                                actualOption = 2;
                            }

                            derecha = false;
                            izquierda = false;
                        }
                    }
                    break;
                }
            break;


            // Menu settings graficos
            case 5:
                // Switch opciones menu
                switch(actualOption){
                    // Resolucion presentacion
                    case 0:
                    { 
                        if(isPressed == 1){
                            actualMenu = 2;
                            actualOption = 0;
                            numOptions = 3;
                            
                            Options::getInstancia()->setResolution(1024, 680);
                            ITEngine::getInstancia()->getActiveHud()->deleteElement("circleResolution");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Options/Graphics.png");
                            
                        }else{
                            // Cambiar textura
                            if(derecha == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleResolution", -0.8, 0);
                            else if(izquierda == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleResolution", -0.4, 0);
                        
                            derecha = false;
                            izquierda = false;
                        }
                    }
                    break;

                    // Resolucion HD
                    case 1:
                    { 
                        if(isPressed == 1){
                            actualMenu = 2;
                            actualOption = 0;
                            numOptions = 3;

                            Options::getInstancia()->setResolution(1280, 720);
                            ITEngine::getInstancia()->getActiveHud()->deleteElement("circleResolution");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Options/Graphics.png");
                            
                        }else{
                            // Cambiar textura
                            if(derecha == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleResolution", 0.4, 0);
                            else if(izquierda == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleResolution", -0.4, 0);
                        
                            derecha = false;
                            izquierda = false;
                        }
                    }
                    break;

                    // Resolucion FHD
                    case 2:
                    { 
                        if(isPressed == 1){
                            actualMenu = 2;
                            actualOption = 0;
                            numOptions = 3;

                            Options::getInstancia()->setResolution(1920, 1080);
                            ITEngine::getInstancia()->getActiveHud()->deleteElement("circleResolution");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Options/Graphics.png");
                            
                        }else{
                            // Cambiar textura
                            if(derecha == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleResolution", 0.4, 0);
                            else if(izquierda == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleResolution", 0.8, 0);
                        
                            derecha = false;
                            izquierda = false;
                        }
                    }
                    break;
                }
            break;

            // Menu settings sonidos
            case 6:
                // Switch opciones menu
                switch(actualOption){
                    // Mutear
                    case 0:
                    { 
                        if(isPressed == 1){
                            actualMenu = 2;
                            actualOption = 1;
                            numOptions = 3;
                            
                            CAudioEngine::getInstancia()->Mute();
                            ITEngine::getInstancia()->getActiveHud()->deleteElement("circleSound");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Options/Sounds.png");
                            
                        }else{
                            // Cambiar textura
                            if(derecha == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleSound", -0.5, 0);
                            else if(izquierda == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleSound", -0.5, 0);
                        
                            derecha = false;
                            izquierda = false;
                        }
                    }
                    break;

                    // Desmutear
                    case 1:
                    { 
                        if(isPressed == 1){
                            actualMenu = 2;
                            actualOption = 1;
                            numOptions = 3;

                            CAudioEngine::getInstancia()->Unmute();
                            ITEngine::getInstancia()->getActiveHud()->deleteElement("circleSound");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Options/Sounds.png");
                            
                        }else{
                            // Cambiar textura
                            if(derecha == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleSound", 0.6, 0);
                            else if(izquierda == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleSound", 0.6, 0);
                        
                            derecha = false;
                            izquierda = false;
                        }
                    }
                    break;
                }
            break;

            // Menu settings camara
            case 7:
                // Switch opciones menu
                switch(actualOption){
                    // Zoom cercano
                    case 0:
                    { 
                        if(isPressed == 1){
                            actualMenu = 2;
                            actualOption = 2;
                            numOptions = 3;
                            
                            Options::getInstancia()->setZoom(-2.0f);
                            ITEngine::getInstancia()->getActiveHud()->deleteElement("circleCamera");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Options/Camera.png");
                            
                        }else{
                            // Cambiar textura
                            if(derecha == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleCamera", -0.8, 0.7);
                            else if(izquierda == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleCamera", -0.4, 0);
                        
                            derecha = false;
                            izquierda = false;
                        }
                    }
                    break;

                    // Default
                    case 1:
                    { 
                        if(isPressed == 1){
                            actualMenu = 2;
                            actualOption = 2;
                            numOptions = 3;

                            Options::getInstancia()->setZoom(0.0f);
                            ITEngine::getInstancia()->getActiveHud()->deleteElement("circleCamera");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Options/Camera.png");
                            
                        }else{
                            // Cambiar textura
                            if(derecha == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleCamera", 0.4, 0);
                            else if(izquierda == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleCamera", -0.4, 0);
                        
                            derecha = false;
                            izquierda = false;
                        }
                    }
                    break;

                    // Zoom lejano
                    case 2:
                    { 
                        if(isPressed == 1){
                            actualMenu = 2;
                            actualOption = 2;
                            numOptions = 3;

                            Options::getInstancia()->setZoom(5.0f);
                            ITEngine::getInstancia()->getActiveHud()->deleteElement("circleCamera");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Options/Camera.png");
                            
                        }else{
                            // Cambiar textura
                            if(derecha == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleCamera", 0.4, 0);
                            else if(izquierda == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleCamera", 0.8, 0.7);
                        
                            derecha = false;
                            izquierda = false;
                        }
                    }
                    break;

                    // Angulo cercano
                    case 3:
                    { 
                        if(isPressed == 1){
                            actualMenu = 2;
                            actualOption = 2;
                            numOptions = 3;

                            Options::getInstancia()->setAngle(-1.0f);
                            ITEngine::getInstancia()->getActiveHud()->deleteElement("circleCamera");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Options/Camera.png");
                            
                        }else{
                            // Cambiar textura
                            if(derecha == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleCamera", -0.8, -0.7);
                            if(izquierda == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleCamera", -0.4, 0);

                            derecha = false;
                            izquierda = false;
                        }
                    }
                    break;

                    // Angulo default
                    case 4:
                    { 
                        if(isPressed == 1){
                            actualMenu = 2;
                            actualOption = 2;
                            numOptions = 3;

                            Options::getInstancia()->setAngle(0.0f);
                            ITEngine::getInstancia()->getActiveHud()->deleteElement("circleCamera");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Options/Camera.png");
                            
                        }else{
                            // Cambiar textura
                            if(derecha == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleCamera", 0.4, 0);
                            else if(izquierda == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleCamera", -0.4, 0);
                        
                            derecha = false;
                            izquierda = false;
                        }
                    }
                    break;

                    // Angulo default
                    case 5:
                    { 
                        if(isPressed == 1){
                            actualMenu = 2;
                            actualOption = 2;
                            numOptions = 3;

                            Options::getInstancia()->setAngle(1.0f);
                            ITEngine::getInstancia()->getActiveHud()->deleteElement("circleCamera");
                            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Options/Camera.png");
                            
                        }else{
                            // Cambiar textura
                            if(derecha == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleCamera", 0.4, 0);
                            else if(izquierda == true)
                                ITEngine::getInstancia()->getActiveHud()->traslateElement("circleCamera", 0.8, -0.7);
                        
                            derecha = false;
                            izquierda = false;
                        }
                    }
                    break;
                }
            break;
        }
    }
}

void MenuState::Render(){

    // Dibujarlo por pantalla

    ITEngine::getInstancia()->drawHudMenus(Shader);

    ITEngine::getInstancia()->draw(shaderModelo); 

}

void MenuState::startMenu(){

    multiplayer = false;

    ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Start/Play.png");

}

void MenuState::optionsMenu(){

    multiplayer = false;

    ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Options/Graphics.png");

}

void MenuState::multiplayerMenu(){

    multiplayer = false;

    ITEngine::getInstancia()->getActiveHud()->changeTextureElement("fondo", "media/GUI/Multiplayer/Fondo Multiplayer.png");

}


void MenuState::lobbyMenu(bool isServer2){

    // Cliente - servidor
    if(isServer2 == true){
        // Creamos el servidor
	    Server::getInstancia();
        // Inicializamos el servidor
        Server::getInstancia()->Init();
    }else{
        // Creamos el cliente
        Client::getInstancia();
        // Inicializamos el cliente
        Client::getInstancia()->Init();
        // Seteamos IP
        Client::getInstancia()->setIP();
    }

    // Actualizamos variables para el update
    multiplayer = true;
    isServer = isServer2;
}


void MenuState::cleanMultiplayer(){

    if(isServer == true){
        delete Server::getInstancia();
    }else{
        delete Client::getInstancia();
    }

    multiplayer = false;

}