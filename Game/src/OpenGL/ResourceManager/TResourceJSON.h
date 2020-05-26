#pragma once
#include <iostream>
#include <fstream>
#include "TResource.h"
#include <include/json.hpp>

class TResourceJSON : public TResource{

    public:

        // Constructor and destructor
        TResourceJSON();
        ~TResourceJSON();

        void loadJSON(std::string file); 
        nlohmann::json getJSON(){return j;};

        const char *getName() override;
        void setName(const char *newName) override;

    private:
        nlohmann::json j;

};