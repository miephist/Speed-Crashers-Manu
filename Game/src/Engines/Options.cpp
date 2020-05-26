#include "Options.h"

Options *Options::instancia = nullptr;

Options::Options(){

    // Default values
    confMatch.time = 60;
    confMatch.numIAs = 1;
    confMatch.carName = "media/Coches/Rocketo/Rocketo.obj";
    confMatch.texBlue = "media/Coches/Rocketo/rocketo_diffuse_blue.png";
    confMatch.texRed = "media/Coches/Rocketo/rocketo_diffuse_red.png";

    // Valores que van en funcion del campo
    confMatch.enemyForward = 144;
    confMatch.widthGoal = 27;
    confMatch.widthMax = 87;

    confMatch.ataque = -72;
    confMatch.centro = 36;
    confMatch.defensa = 72;

    confGame.resolution[0] = 1024;
    confGame.resolution[1] = 680;
    confGame.zoom = 0;
    confGame.angle = 0;
    confGame.coop = false;


    // Resultado que se utilizara en el postgame
    blueGoals = 0;
    redGoals = 0;

    // Contador para cuenta atras
    startTimer = 0.0;

}

Options::~Options(){

    instancia = nullptr;

}


Options *Options::getInstancia(){

    if(instancia == nullptr)
        instancia = new Options();

    return instancia;

}

void Options::setTimer(int time){

    switch(time){
        case 2: confMatch.time = 60; break;
        case 6: confMatch.time = 120; break;
        case 7: confMatch.time = 300; break;
    }
}

void Options::setMode(int mode){

    switch(mode){
        case 1: confMatch.numIAs = 1; break;
        case 4: confMatch.numIAs = 3; break;
        case 5: confMatch.numIAs = 5; break;
    }
}

void Options::setCar(int character){

    // En funcion del personaje elegido cargara un coche u otro
    switch(character){
        case 1: confMatch.carName = "media/Coches/Rocketo/Rocketo2.obj"; 
                confMatch.texBlue = "media/Coches/Rocketo/rocketo_diffuse_blue.png"; 
                confMatch.texRed = "media/Coches/Rocketo/rocketo_diffuse_red.png"; break;

        case 2: confMatch.carName = "media/Coches/Classic/Classic.obj";
                confMatch.texBlue = "media/Coches/Classic/classic_diffuse_blue.png";
                confMatch.texRed = "media/Coches/Classic/classic_diffuse_red.png"; break;

        case 3: confMatch.carName = "media/Coches/Deportivo/Deportivo.obj";
                confMatch.texBlue = "media/Coches/Deportivo/deportivo_diffuse_blue.png";
                confMatch.texRed = "media/Coches/Deportivo/deportivo_diffuse_red.png"; break;

        case 4: confMatch.carName = "media/Coches/Futurista/Futurista.obj";
                confMatch.texBlue = "media/Coches/Rocketo/rocketo_diffuse_blue.png";
                confMatch.texRed = "media/Coches/Rocketo/rocketo_diffuse_red.png"; break;
    }    
}

void Options::setResolution(int width, int height){

    // Cambiamos nuevas resoluciones
    confGame.resolution[0] = width;
    confGame.resolution[1] = height;

    ITEngine::getInstancia()->resizeWindow(width, height);

}

void Options::setFinalScore(unsigned int b, unsigned int r){

    blueGoals = b;
    redGoals = r;

}