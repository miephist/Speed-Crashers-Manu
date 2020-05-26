#include "FuzzyVariable.h"
#include "FuzzyOperators.h"
#include "FuzzySet_Triangle.h"
#include "FuzzySet_Right.h"
#include "FuzzySet_Left.h"
#include "FzSet.h"
#include <cassert>
#include <algorithm>

FuzzyVariable::~FuzzyVariable(){
    MemberSets::iterator it = mSets.begin();
    for(it; it != mSets.end(); ++it){
        delete it->second;
    }
}

//Se fuziffica el crisp  value aqui.
void FuzzyVariable::Fuzzify(double val){

    MemberSets::iterator cr = mSets.begin();
    for(cr; cr != mSets.end(); ++cr){
        cr->second->SetDOM(cr->second->CalculateDOM(val));
    }

}

double FuzzyVariable::DeFuzzify(){
    /**
     * Formula
     * Sumatorio de Valor Representativo * membership /
     * Sumatorio membership
    */


    double numerador = 0.0; //arriba
    double denominador = 0.0; //abajo

    double resultado = 0.0;

    MemberSets::iterator cr = mSets.begin();
    for(cr; cr != mSets.end(); ++cr){
        
        denominador += cr->second->getValorDOM();

       /* std::cout << "ValorDom: "<<cr->second->getValorDOM()<<std::endl;
        std::cout << "Nombre: "<<cr->first<<std::endl;

        std::cout << "MaxValorDom: "<<cr->second->getMaxValorDOM()<<std::endl;*/

        numerador += (cr->second->getValorDOM() * cr->second->getMaxValorDOM());

    }
    resultado = numerador/denominador;

    return resultado;

}
//Metemos una forma triangular
FzSet FuzzyVariable::AddTriangleSet(std::string name, double minimo, double pico, double maximo){

    mSets[name] = new FuzzySet_Triangle(pico,pico-minimo,maximo-pico);

    //Se ajusta si hace falta
    AdjustRange(minimo,maximo);

    return FzSet(*mSets[name]);
}

FzSet FuzzyVariable::AddLeftSet(std::string name, double minimo, double pico, double maximo){

    mSets[name] = new FuzzySet_Left(pico,pico-minimo,maximo-pico);
    
    AdjustRange(minimo,maximo);

    return FzSet(*mSets[name]);
}

FzSet FuzzyVariable::AddRightSet(std::string name, double minimo, double pico, double maximo){
   
    mSets[name] = new FuzzySet_Right(pico,pico-minimo,maximo-pico);
   
    
    AdjustRange(minimo,maximo);

    return FzSet(*mSets[name]);
}

void FuzzyVariable::AdjustRange(double minimo, double maximo){

    if(minimo < MinRange) MinRange = minimo;
    if(maximo > MaxRange) MaxRange = maximo;

}

