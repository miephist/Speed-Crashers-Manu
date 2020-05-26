#pragma once
#include "../Engines/structs.h"
#include "../States/GameState.h"
#include "../States/MenuState.h"
#include "../States/GameStateRed.h"
#include "../States/ScoreState.h"
#include "../States/InitState.h"

class Game{

    public:

        // Destructor
        ~Game();

        void Init();
        void Update();
        void Render();
        void Clear();

        void changeState(Auxiliar::states newState);

        /** Metodo para saber si la ventana esta abierta
         * \return true: esta abierta
         * \return false: no esta abierta, fin de ejecución del juego
         */
        bool windowOpen();

        static Game* getInstancia();

    private:

        // Constructor
        Game();

        // Instancia
        static Game* instancia;

        // Estado actual
        Auxiliar::states actualState;

        // Booleano ventana
        bool window;
    
        // Estados
        MenuState* menuState;
        GameState* gameState;
        GameStateRed* gameStateRed;
        ScoreState* scoreState;
        InitState* initState;

};