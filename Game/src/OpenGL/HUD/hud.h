#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "elementoHud.h"
#include <vector>
#include <stdio.h>
#include <string.h>
#include "../Interfaces/ITShader.h"
 
using namespace std; 
 
class hud  
{ 
public:
    //constructor y destructor
    hud(const char* n);
    ~hud();
    
    //getters
    const char* getName();
    elementoHud* getElement(const char* n); //Funcion que devuelve un elemento a partir de su nombre
    //añadir elementos y borrar
    void addElement(const char* n, const char* p); //Añade un elemento con textura al hud
	elementoHud* addElementHud(const char* n, const char* p); //Añade un elemento con textura al hud
    void addElement(const char* n, glm::vec4 c); //Añade un elemento con color al hud
    void addElement2(elementoHud *a);            //Añade un elemento al hud
	void deleteElement(const char* nombre); // Elimina el elemento del array


    //Tratamiento de los elementosHud
    void rotateElement(const char* n, float angle);
    void traslateElement(const char* n, float x, float y);
    void scaleElement(const char* n, float x, float y);
    void changeTextureElement(const char* n, const char* p);
    void changeColorElement(const char* n, glm::vec4 c);
    void changeTransparencyElement(const char* n, bool t, float l);
    
    //dibujado
    void drawHud(ITShader* shaderHud); //Dibuja todos los elementos del hud
 
private:
    const char* nombre; //Nombre del hud, por ejemplo "Opciones"
 
    std::vector <elementoHud*> elems; //Array con los elementos que forman el hud
 
   
	int getElementPosition(const char * n); // Funcion que devuelve la posicion del elemento en el array
};