#pragma once

#include "FuzzyTerm.h"
#include "FuzzySet.h"

class FzAND;

class FzSet : public FuzzyTerm{

    private:

        friend class FzVery;
        friend class FzFairly;

        FuzzySet& set;

    public:

        FzSet(FuzzySet& fs):set(fs){}

        FuzzyTerm* Clone()const{return new FzSet(*this);};
        double GetDOM() {return set.getValorDOM();};
        void ClearDOM(){set.ClearDOM();};
        void ORDOM(double val){set.OR_DOM(val);};

};
