#pragma once

#include <map>
#include <iostream>
#include <string>

class FuzzySet;
class FzSet;
class FuzzyModule;

class FuzzyVariable{

    private:

        typedef std::map<std::string, FuzzySet*> MemberSets;

        //no Permitimos copia
        FuzzyVariable(const FuzzyVariable&);
        FuzzyVariable& operator=(const FuzzyVariable&);

        //Mapa del set
        MemberSets mSets;

        //Minimo y maximo
        double MinRange;
        double MaxRange;

        void AdjustRange(double min, double max);

        ~FuzzyVariable();

        //Clase amiga, permite acceder a privates y protecteds
        friend class FuzzyModule;

    public:

        FuzzyVariable():MinRange(0.0),MaxRange(0.0){}

        /**
         * Creacion de los distintos tipos añadiendoles su membership
         * y sus min max etc.
        */
       FzSet AddLeftSet(std::string name, double minimo, double pico, double maximo);

       FzSet AddRightSet(std::string name, double minimo, double pico, double maximo);

       FzSet AddTriangleSet(std::string name, double minimo, double pico, double maximo);

       // Fuzzicamos un valor
       void Fuzzify(double val);

       //defuzificamos MAXAV
       double DeFuzzify();

       
};