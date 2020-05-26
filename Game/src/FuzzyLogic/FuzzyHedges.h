#pragma once

#include "FzSet.h"
#include "FuzzyTerm.h"
#include <math.h>


class FzVery : public FuzzyTerm{

    private:

        FuzzySet& set;


    public:

        FzVery(FzSet& ft):set(ft.set){}
      
        FuzzyTerm* Clone()const{return new FzVery(*this);};
        double GetDOM(){return set.getMaxValorDOM() * set.getValorDOM();};
        void ClearDOM(){set.ClearDOM();};
        void ORDOM(double val){set.OR_DOM(val * val);};

};


class FzFairly : public FuzzyTerm{

     private:

        FuzzySet& set;


    public:

        FzFairly(FzSet& ft):set(ft.set){}
      
        FuzzyTerm* Clone()const{return new FzFairly(*this);};
        double GetDOM(){return sqrt(set.getValorDOM());};
        void ClearDOM(){set.ClearDOM();};
        void ORDOM(double val){set.OR_DOM(sqrt(val));};

};