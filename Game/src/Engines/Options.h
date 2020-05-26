#pragma once
#include <vector>
#include "structs.h"

struct optionsMatch {

    // Modo de juego (|1 vs 1|, |2 vs 2|, |3 vs 3|)
    int numIAs;

    // Temporizador de la partida (1 3 5 min)
    int time;

    // Coche elegido
    const char* carName;
    const char* texBlue;
    const char* texRed;

    //Tamanyo escenario
    int enemyForward; // Z maxima del enemigo
    int widthGoal; // Anchura porteria
    int widthMax; //X máxima
    int defensa, ataque, centro;

};

struct optionsGame {

    // Apartado Graficos
    int resolution[2];

    // Apartado Camara
    float zoom, angle;

    // Opcion para iniciar pantalla compartida
    bool coop;

};

class Options{

    public:

        // Getters
        static Options* getInstancia();
        int getTimer()                      {return confMatch.time;};
        int getNumIAs()                     {return confMatch.numIAs;};
        const char* getCarName()            {return confMatch.carName;};
        const char* getBlueTex()            {return confMatch.texBlue;};
        const char* getRedTex()             {return confMatch.texRed;};
        int getForwardScenario()            {return confMatch.enemyForward;};
        int getWidthGoal()                  {return confMatch.widthGoal;}; 
        int getWidthMax()                   {return confMatch.widthMax;};
        unsigned int getFinalScoreBlue()    {return blueGoals;};
        unsigned int getFinalScoreRed()     {return redGoals;};     
        bool getCoop()                      {return confGame.coop;};
        float getStartTimer()               {return startTimer;};
        float getZoom()                     {return confGame.zoom;};
        float getAngle()                    {return confGame.angle;};

        // Setters
        void setTimer(int time);
        void setMode(int mode);
        void setCar(int character);
        void setResolution(int width, int height);
        void setFinalScore(unsigned int b, unsigned int r);
        void setCoop(bool multi)                                 {confGame.coop = multi;};
        void setStartTimer(float timer)                          {startTimer = timer;};
        void setZoom(float newZoom)                              {confGame.zoom = newZoom;};
        void setAngle(float newAngle)                            {confGame.angle = newAngle;};

    private:

        // Constructor && Destructor
        Options();
        ~Options();

        //Instancia
        static Options* instancia;

        // Struct con la configuracion del partido
        optionsMatch confMatch;

        // Struct con la configuracion del juego
        optionsGame confGame;

        // Resultado final partido
        unsigned int blueGoals;
        unsigned int redGoals;

        // Temporizador para cuenta atras
        float startTimer;

};