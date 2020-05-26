#pragma once

#include "FuzzySet.h"


class FuzzySet_Right : public FuzzySet{

    private:

        //Valores que dan forma
        double pico;
        double izquierda;
        double derecha;

    public:

        FuzzySet_Right(double peak, double left, double right):
        FuzzySet( ((peak + right) + peak) / 2), pico(peak), izquierda(left), derecha(right) {}
        
        double CalculateDOM(double val);
};