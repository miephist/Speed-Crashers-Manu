#pragma once

//clase abstracta
class FuzzyTerm{

    public:

        virtual ~FuzzyTerm(){}

        //constructor virtual
        virtual FuzzyTerm* Clone()const = 0;

        //Recupera el valor de membership
        virtual double GetDOM()= 0;

        //resetea el valor
        virtual void ClearDOM()=0;

        //updatea el DOM
        virtual void ORDOM(double val)=0;

};