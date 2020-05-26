#pragma once

#include "FuzzySet.h"


class FuzzySet_Left : public FuzzySet{

    private:

        //Valores que determinan la forma
        double pico;
        double derecha;
        double izquierda;


    public:

        FuzzySet_Left(double peak, double left, double right):
        FuzzySet( ((peak - left) + right) / 2), pico(peak), derecha(right), izquierda(left){}


        double CalculateDOM(double val);
};


