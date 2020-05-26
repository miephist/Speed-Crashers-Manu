#pragma once

#include <vector>
#include "FuzzySet.h"
#include "FuzzyOperators.h"

class FuzzyRule{

    private:

        //Antecedentes
        FuzzyTerm* antecedente;
        
        //Consecuencia
        FuzzyTerm* consecuencia;
        
    public:

        FuzzyRule(FuzzyTerm& ant, FuzzyTerm& con):antecedente(ant.Clone()),consecuencia(con.Clone()){}

        ~FuzzyRule(){delete antecedente; delete consecuencia;};

        void SetZero(){consecuencia->ClearDOM();};

        void Calculate()
        {
            consecuencia->ORDOM(antecedente->GetDOM());
        }
};