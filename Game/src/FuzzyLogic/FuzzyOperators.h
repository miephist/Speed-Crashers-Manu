#pragma once

#include <vector>
#include <cassert>
#include "FuzzyTerm.h"

class FzAND : public FuzzyTerm{

    private:

        std::vector<FuzzyTerm*> terms;

    public:

        ~FzAND();

        //copia
        FzAND(const FzAND& fa);

        //constructores con varios terminos hasta 4
        FzAND(FuzzyTerm& term1, FuzzyTerm& term2);
        FzAND(FuzzyTerm& term1, FuzzyTerm& term2, FuzzyTerm& term3);
        FzAND(FuzzyTerm& term1, FuzzyTerm& term2, FuzzyTerm& term3, FuzzyTerm& term4);

        //virtual constructor
        FuzzyTerm* Clone()const{return new FzAND(*this);};

        double GetDOM();
        void ClearDOM();
        void ORDOM(double val);

};

class FzOR : public FuzzyTerm{

    private:

        std::vector<FuzzyTerm*> terms;

    public:

        ~FzOR();

        //copia
        FzOR(const FzOR& fa);

        //constructores con varios terminos hasta 4
        FzOR(FuzzyTerm& term1, FuzzyTerm& term2);
        FzOR(FuzzyTerm& term1, FuzzyTerm& term2, FuzzyTerm& term3);
        FzOR(FuzzyTerm& term1, FuzzyTerm& term2, FuzzyTerm& term3, FuzzyTerm& term4);

        //virtual constructor
        FuzzyTerm* Clone()const{return new FzOR(*this);};

        double GetDOM();
        void ClearDOM();
        void ORDOM(double val);

};

