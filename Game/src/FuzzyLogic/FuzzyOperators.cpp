#include "FuzzyOperators.h"
#include <limits>


FzAND::FzAND(const FzAND& fa){

    std::vector<FuzzyTerm*>::const_iterator ct = fa.terms.begin();

    for (ct; ct != fa.terms.end(); ++ct){

        terms.push_back((*ct)->Clone());

    }

}

FzAND::FzAND(FuzzyTerm& term1, FuzzyTerm& term2){

    terms.push_back(term1.Clone());
    terms.push_back(term2.Clone());
}

FzAND::FzAND(FuzzyTerm& term1, FuzzyTerm& term2, FuzzyTerm& term3){
    
    terms.push_back(term1.Clone());
    terms.push_back(term2.Clone());
    terms.push_back(term3.Clone());

}

FzAND::FzAND(FuzzyTerm& term1, FuzzyTerm& term2, FuzzyTerm& term3, FuzzyTerm& term4){
    
    terms.push_back(term1.Clone());
    terms.push_back(term2.Clone());
    terms.push_back(term3.Clone());
    terms.push_back(term4.Clone());

}

FzAND::~FzAND(){
    
    std::vector<FuzzyTerm*>::iterator ct = terms.begin();
    for(ct; ct != terms.end(); ++ct){

        delete *ct;

    }

}
//Coge el minimo because AND
double FzAND::GetDOM(){
    //Valor maximo que puede tener un double
    double minimo = (std::numeric_limits<double>::max)();

    std::vector<FuzzyTerm*>::iterator ct = terms.begin();
    for(ct; ct != terms.end(); ++ct){
        
        if((*ct)->GetDOM() < minimo){
            minimo = (*ct)->GetDOM();
        }

    }

    return minimo;

}

void FzAND::ORDOM(double val){

    std::vector<FuzzyTerm*>::iterator ct = terms.begin();
    for(ct; ct != terms.end(); ++ct){
        (*ct)->ORDOM(val);
    }

}

void FzAND::ClearDOM(){

    std::vector<FuzzyTerm*>::iterator ct = terms.begin();
    for(ct; ct != terms.end(); ++ct){
        (*ct)->ClearDOM();
    }
}




//**************************CON EL OR******************************/


FzOR::FzOR(const FzOR& fa){

     std::vector<FuzzyTerm*>::const_iterator ct = fa.terms.begin();

    for (ct; ct != fa.terms.end(); ++ct){

        terms.push_back((*ct)->Clone());

    }

}

FzOR::FzOR(FuzzyTerm& term1, FuzzyTerm& term2){

    terms.push_back(term1.Clone());
    terms.push_back(term2.Clone());


}

FzOR::FzOR(FuzzyTerm& term1, FuzzyTerm& term2, FuzzyTerm& term3){
    
    terms.push_back(term1.Clone());
    terms.push_back(term2.Clone());
    terms.push_back(term3.Clone());
    
}

FzOR::FzOR(FuzzyTerm& term1, FuzzyTerm& term2, FuzzyTerm& term3, FuzzyTerm& term4){
    
    terms.push_back(term1.Clone());
    terms.push_back(term2.Clone());
    terms.push_back(term3.Clone());
    terms.push_back(term4.Clone());

}

FzOR::~FzOR(){

    std::vector<FuzzyTerm*>::iterator ct = terms.begin();
    for(ct; ct != terms.end(); ++ct){

        delete *ct;

    }

}
//coge los maximos al ser OR
double FzOR::GetDOM(){
    //Valor minimo que puede tener un double
    double maximo = (std::numeric_limits<double>::min)();

    std::vector<FuzzyTerm*>::iterator ct = terms.begin();
    for(ct; ct != terms.end(); ++ct){
        
        if((*ct)->GetDOM() > maximo){
            maximo = (*ct)->GetDOM();
        }

    }

    return maximo;

    
}

void FzOR::ORDOM(double val){
     std::vector<FuzzyTerm*>::iterator ct = terms.begin();
    for(ct; ct != terms.end(); ++ct){
        (*ct)->ORDOM(val);
    }

}
void FzOR::ClearDOM(){
    std::vector<FuzzyTerm*>::iterator ct = terms.begin();
    for(ct; ct != terms.end(); ++ct){
        (*ct)->ClearDOM();
    }
}