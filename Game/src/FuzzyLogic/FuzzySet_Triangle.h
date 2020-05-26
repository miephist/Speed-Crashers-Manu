#pragma once

#include "FuzzySet.h"


class FuzzySet_Triangle : public FuzzySet{

    private:

        double pico;
        double izquierda;
        double derecha;

    public:

        FuzzySet_Triangle(double mid, double left, double right):
        FuzzySet(mid), pico(mid), izquierda(left), derecha(right){}

        double CalculateDOM(double val);

};