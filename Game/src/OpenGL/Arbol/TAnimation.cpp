#include "TAnimation.h"

TAnimation::TAnimation(std::vector<TMesh*> mallas){

    
    currentIndex=0;

    frames= mallas.size();
    meshes=mallas;

}

TAnimation::~TAnimation(){
    for(int z=0;z<meshes.size();z++){
        delete meshes.at(z);
    }
    meshes.clear();

}

void TAnimation::beginDraw(int pasada){

    if(pasada==2){
        // reproduccion en bucle y reinicio de animaciones
        meshes.at(currentIndex*0.4)->beginDraw(pasada);
        
        currentIndex++;
        if(currentIndex>=frames*2.5)
        currentIndex=0;

    }
}
