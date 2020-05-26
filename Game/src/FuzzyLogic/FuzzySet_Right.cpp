#include "FuzzySet_Right.h"
#include <cassert>



double FuzzySet_Right::CalculateDOM(double val){
    
    if( ((derecha == 0.0) && (pico == val)) || ((izquierda == 0.0) && (pico == val)) ){
        return 1.0;
    }

    else if( (val <= pico) && (val > (pico - izquierda))){
        double grado = 1.0 / izquierda;

        return grado * (val - (pico - izquierda));
    }

    else if( (val > pico) && (val <= pico+derecha)){
        return 1.0;
    }
    
    else{
        return 0.0;
    }

}