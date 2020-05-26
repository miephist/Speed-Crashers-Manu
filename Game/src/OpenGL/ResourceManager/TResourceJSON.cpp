#include "TResourceJSON.h"

TResourceJSON::TResourceJSON(){

}

TResourceJSON::~TResourceJSON(){
    
}


void TResourceJSON::loadJSON(std::string file){

    // Conversión de file a const char*
    char * writable = new char[file.size() + 1];
    std::copy(file.begin(), file.end(), writable);
    writable[file.size()] = '\0';



    try{
        // Abrimos el archivo
        std::ifstream i;
        i.open(writable);
        i >> j;
        i.close();
    }catch(std::ifstream::failure e){
        std::cerr << "Error: no se ha podido abrir el fichero: " << writable << std::endl;
        exit(0);
    }
}

const char *TResourceJSON::getName(){
    return name;
}

void TResourceJSON::setName(const char *newName){
    name = newName;
}

