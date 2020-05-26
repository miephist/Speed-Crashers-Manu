
#include <stdarg.h>
#include <cassert>

#include "FuzzyModule.h"

    FuzzyModule::~FuzzyModule(){
        VarMap::iterator cv = map_Variables.begin();
        for (cv; cv != map_Variables.end(); ++cv){
            delete cv->second;
        }

        std::vector<FuzzyRule*>::iterator cr = rules.begin();
        for(cr; cr != rules.end(); ++cr){
            delete *cr;
        }
    }
    void FuzzyModule::AddRule(FuzzyTerm& antecedente, FuzzyTerm& consecuencia){
      
        rules.push_back(new FuzzyRule(antecedente, consecuencia));

    }

     FuzzyVariable& FuzzyModule::CreateFLV(const std::string& Name){
         
         map_Variables[Name] = new FuzzyVariable();
         return *map_Variables[Name];

     }

     void FuzzyModule::Fuzzify(const std::string& NameFLV, double val){

         map_Variables[NameFLV]->Fuzzify(val);

     }

     double FuzzyModule::DeFuzzify(const std::string& key){

         //Reseteamos los DOOMS de las consecuencias de todas las reglas
         SetConfsToZero();

         //Reglas
         std::vector<FuzzyRule*>::iterator cr = rules.begin();
         for(cr; cr != rules.end(); ++cr){
             (*cr)->Calculate();
         }

         //Ahora las resultantes

         return map_Variables[key]->DeFuzzify();

    }   

    