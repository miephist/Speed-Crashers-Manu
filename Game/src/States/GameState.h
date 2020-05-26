#pragma once
#include "../Engines/structs.h"
//#include "Facade.h"
#include "../Engines/AudioEngine.h"
#include "../Game/Camera.h"
#include "../Player/Nitro.h"
#include "../Player/Jugador.h"
#include "../Engines/TriggerSystem.h"
#include "../Player/IA.h"
#include "../Engines/SteeringBehaviours.h"
#include "../Game/Team.h"
#include "../Engines/Options.h"
#include "../FuzzyLogic/FuzzyModule.h"

class GameState{

    public:

        // Constructor
        GameState();
        ~GameState();

        void Init();
        void Update();
        void Render(int TDeltaTime);
        void UpdateRender(btRigidBody *TObject);
    
        //Zona IA
        
        void UpdateIA(IA* ia, SteeringBehaviours* movements); //Encargado del comportamiento de la IA
        std::vector<double> FuzzyNitroso(IA* ia);
        double FuzzyUsing(IA* ia);
        void FuzzyUpdate(IA* ia, SteeringBehaviours* movements);
        double FuzzyEstado(double pos, IA* ia);
        std::vector<double> FuzzyDefensa(IA* ia);
        std::vector<double> FuzzyAtacar(IA* ia);
        std::vector<double> FuzzyDefender(IA* ia);
        
        void ResetarPoderes(IA* ia,double pos);


        void setWindowFPS(); //FPS en pantalla

        void setGear();   //Detección de uso de mando o teclado

        void setCoopHud();  //Cambio de hud

        void countDown(char x); //Cuenta atras de inicio de partida

        //Timers de la partida tanto para individual como pantalla partida
        void timerGame();
        void timerGameCoop();

        //cosas de nitros
        void checkRespawns();
        std::vector<Nitro*> getNitros();

        // Lineas Debug
        void setLinesEscenario();
        void setTextEscenario();
        void obtainActualIA();

        //Cosas vareas
        int random;
        int randB;
        int randR;
        bool change;

        // Cuenta atras
        bool cuentaAtras;
        bool cuentaAtras2;

    private:

        // Temporizador partida
        int timer;
        int then;
        int atack;

        int minutos;
        int decenas;
        int unidades;
        double temporizadorDecenas;

        int newMinutos;
        int newDecenas;
        int newUnidades;

        //Coop
        int minutos2;
        int decenas2;
        int unidades2;
        double temporizadorDecenas2;

        int newMinutos2;
        int newDecenas2;
        int newUnidades2;

        //Cambio de hud coop
        int z;
        
        //Fuzzy
        
        

        // Cambio a la pantalla de carga
        int carga;

        bool window;
        double nbFrames;
        double lastTime;

        // Shaders
        ITShader* shader;
        ITShader* shaderHud;
        ITShader* shaderSkybox;
        ITShader* shaderDebug;

        // Nitros
        std::vector<Nitro*> nitros;
        btRigidBody *rigidNitro;

        // Jugador
        Jugador *Coche;
        std::vector<Jugador*> coop;

        // Sistema de colisiones
        TriggerSystem *collide;

        // Equipos
        Team *red;
        Team *blue;

        // IA
        int mitadSup;
        int mitadInf;
        int mitad;
        int ran;
        int mareoTimer;
        bool ataque;
        bool molestar;
        std::vector<IA*> ia;
        std::vector<SteeringBehaviours*> movements;
        int position;

        // OpenGL
        std::vector<Camera*> cameras;

        //voz
        int voz ;

        // DEBUG
        int newState;
        int oldState;
        int actualIA;

        // TEXTO
        ITShader* shaderText;
        TResourceText* tPosIA;
        TResourceText* tCargasIA;
        TResourceText* tPowersIA;
        TResourceText* tStatesIA;

};