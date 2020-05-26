#include "Game.h"

Game *Game::instancia = nullptr;

Game::Game(){

    Init();

}

Game::~Game(){

    instancia = nullptr;

    glfwDestroyWindow(ITEngine::getInstancia()->getWindow());
}


Game *Game::getInstancia(){

    if(instancia == nullptr)
        instancia = new Game();

    return instancia;

}

void Game::Init(){

    // Inputs para la ventana
    glfwSetInputMode(ITEngine::getInstancia()->getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
    // Ocultamos cursor
    glfwSetInputMode(ITEngine::getInstancia()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    actualState = Auxiliar::InitState;

    initState = new InitState();

    Options::getInstancia();

}


void Game::Update(){

    switch(actualState){
        // Cargamos Pantalla inicial de carga
        case Auxiliar::states::InitState:
                initState->Update();
                break;
        // Cargamos Menu principal
        case Auxiliar::states::MenuState:
                menuState->Update();
                break;
        // Cargamos Nivel 
        case Auxiliar::states::GameState: 
                gameState->Update();
                break;
        // Cargamos Multijugador en linea (no implementado)
        case Auxiliar::states::GameStateRed:
                gameStateRed->Update();
                break;
        // Pantalla PostGame
        case Auxiliar::states::ScoreState:
                scoreState->Update();
                break;
    }
}

void Game::Render(){

    // Intercambiamos buffers
    glfwSwapBuffers(ITEngine::getInstancia()->getWindow());
    // Comprueba los eventos
    glfwPollEvents();

}

void Game::Clear(){

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


bool Game::windowOpen(){

    return glfwWindowShouldClose(ITEngine::getInstancia()->getWindow());

}


void Game::changeState(Auxiliar::states newState){

    switch(newState){
        // Cargamos Menu principal (falta por implementar)
        case Auxiliar::states::MenuState: // Limpiar el nivel
        {
            // Pasamos del juego al menu principal
            if(actualState == Auxiliar::states::GameState){
                // Limpiar el juego
                delete gameState;
                // Iniciar el menu
                menuState = new MenuState();
            
            // Pasamos del menu de score al menu principal
            }else if(actualState == Auxiliar::states::ScoreState){
                // Limpiamos el score
                delete scoreState;
                // Iniciamos el menu
                ITEngine::getInstancia()->resetScene();
                menuState = new MenuState();

            }else if(actualState == Auxiliar::states::InitState){
                // Limpiamos pantalla de carga
                delete initState;

                // Iniciamos el menu
                ITEngine::getInstancia()->resetScene();
                menuState = new MenuState();
            }
        }
        break;
        // Cargamos Nivel 
        case Auxiliar::states::GameState:
        {
                // Pasamos del menu principal al juego
                if(actualState == Auxiliar::states::MenuState){
                    delete menuState;

                    // Reseteamos la escena y creamos la partida
                    ITEngine::getInstancia()->resetScene();
                    gameState = new GameState();

                // Pasamos del menu de score al partido
                }else if(actualState == Auxiliar::states::ScoreState){
                    // Limpiamos el score
                    delete scoreState;

                    // Reseteamos la escena y creamos la partida
                    ITEngine::getInstancia()->resetScene();
                    gameState = new GameState();

                }
                break;
        }
        // Nivel Multijugador
        case Auxiliar::states::GameStateRed:
                delete menuState;
                // Creamos la partida en red
                gameStateRed = new GameStateRed();
                break;
        // Pantalla de resultado
        case Auxiliar::states::ScoreState:
                delete gameState;
                // volvemos al menu principal
                ITEngine::getInstancia()->resetScene();
                scoreState = new ScoreState();
                break;
    }
    actualState = newState;
}