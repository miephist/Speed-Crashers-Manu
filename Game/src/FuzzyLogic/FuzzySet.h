#pragma once

#include <string>
#include <cassert>
#include <iostream>



class FuzzySet{

    private:

        //Valor de "membership" de cada valor
        double valorDOM;

        //Maximo de cada uno member
        double MaxValorDOM;

    public:
        //Antes de iniciar constructor asignamos variables
        FuzzySet(double RepVal):valorDOM(0.0), MaxValorDOM(RepVal){}

        virtual double CalculateDOM(double val)= 0;

        //Calcula el valor del membership, al ser un OR coge el maximo
        void OR_DOM(double val) {if (val > valorDOM) valorDOM = val;};

        void ClearDOM() {valorDOM = 0.0;};

        //Getters --- Setters

        double getMaxValorDOM() {return MaxValorDOM;};
        double getValorDOM() {return valorDOM;};
        void SetDOM(double val) {valorDOM = val;};

        
};
