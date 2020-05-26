#pragma once


#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "FuzzySet.h"
#include "FuzzyVariable.h"
#include "FuzzyRule.h"
#include "FuzzyOperators.h"
#include "FzSet.h"
#include "FuzzyHedges.h"


class FuzzyModule
{
    private:
    
    typedef std::map<std::string, FuzzyVariable*> VarMap;

    //Mapa de todas las variables del fuzzy que este modulo usa
    VarMap map_Variables;

    //vector que contiene las reglas del fuzzy
    std::vector<FuzzyRule*> rules;

    //Zeros en el dominio de cada regla consecuente.
    inline void SetConfsToZero();

    public:

    enum DefuzzifyType{max_av};
    ~FuzzyModule();
    
    //nueva variable del fuzzy y referencia a ella
    FuzzyVariable& CreateFLV(const std::string& Name);

    //añadir regla al modulo actual
    void AddRule(FuzzyTerm& antecedente, FuzzyTerm& consecuencia);

    //metodo que llama al modulo Fuzzi de la FLV
    void Fuzzify(const std::string& NameFLV, double val);
    
    //Devuelve el "crisp value", defuzzificamos
    double DeFuzzify(const std::string& key);

};


inline void FuzzyModule::SetConfsToZero(){
    std::vector<FuzzyRule*>::iterator cr = rules.begin();
    for(cr; cr != rules.end(); ++cr){
        (*cr)->SetZero();
    }
}