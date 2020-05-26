#include "FuzzySet_Left.h"
#include <cassert>


double FuzzySet_Left::CalculateDOM(double val){
    //comprobacion de que los laterales son 0
    if(( (derecha == 0.0) && (pico == val) )|| ((izquierda == 0) && (pico == val))){
        return 1.0;
    }


    else if( (val>=pico) && (val < pico + derecha)){
        double grado = 1.0 / -derecha;
        return grado * (val - pico) + 1.0;
    }

    else if( (val < pico) && (val>= pico - izquierda)){
        return 1.0;
    }
    else{
        return 0.0;
    }

}