#include "Game/Game.h"

int main(){

    // Inicializamos el juego
    Game *game = Game::getInstancia();

    while(!game->windowOpen()){

        game->Clear();

        game->Update();

        game->Render();

    }

    delete game;

    return 0;

}