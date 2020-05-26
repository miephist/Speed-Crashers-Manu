#include "FuzzySet_Triangle.h"



double FuzzySet_Triangle::CalculateDOM(double val){
   
    if(( (derecha == 0.0) && (pico == val) )|| ((izquierda == 0) && (pico == val))){
        return 1.0;
    }


    else if( (val <= pico) && (val >= pico - izquierda)){
        double grado = 1.0 / izquierda;
        return grado * (val - (pico - izquierda));
    }

    else if( (val > pico) && (val < (pico + derecha))){
        double grado = 1.0 / -derecha;
        return grado * (val - pico) + 1.0;
    }
    else{
        return 0.0;
    }

}