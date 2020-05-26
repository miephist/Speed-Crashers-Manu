#pragma once
#include <iostream>

class TResource{

    public:

        virtual const char *getName()=0;
        virtual void setName(const char *newName)=0;

    protected:
        //nombre del recurso
        const char *name;

};