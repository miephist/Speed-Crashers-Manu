#define GLM_ENABLE_EXPERIMENTAL

#pragma once
#include "../Arbol/TCamera.h"
#include "../Interfaces/ITShader.h"

#include "../Arbol/TEntity.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <array>

using namespace std; 
 
/*Clase para definir los elementos del hud. Estos elementos son cuadrados
de un ancho y alto  a los que se asigna una textura. Se trasladasn y rotan mediante
una matriz modelo*/

class elementoHud  
{ 
public: 
    //constructores y destructor
    elementoHud(const char* n, const char* p); 
    elementoHud(const char* n, glm::vec4 c);
    ~elementoHud();

    const char* getName(); 

    //Dibujado
    void draw(ITShader* shaderHud);

    //Transformaciones
    void rotacion(float angle);
    void traslacion(float x, float y);
    void escalado(float x, float y);
    void cambiarTextura(const char* p);
    void cambiarColor(glm::vec4 c);
    void cambiarTransparencia(bool t, float l);

private:
    //---- VARIABLES ----
    float width; //Ancho del quad
    float height; //Alto del quad
    const char* name; //Nombre del quad 
    const char* path; //Ruta de la imagen
    bool transparency; //Booleano para saber si el elemento HUD debe ser transparente
    float transLevel; //Nivel de transparencia del elemento HUD

    std::array<float, 32> data; //Array con las posiciones y coordenadas de textura de cada vertice del quad
    GLuint indices[6] = { //Indices para crear los triangulos que forman el cuadrado
		0, 1, 3,
		1, 2, 3
	};

    GLuint VAO, VBO, EBO; //Buffers de OpenGL

    glm::vec4 color; //Color del elemento hud

    glm::mat4 tras;  // Matriz de traslacion
    glm::mat4 rot;   // Matriz de rotacion
    glm::mat4 esc;   // Matriz de escalado
    glm::mat4 model; // Matriz modelo

    GLuint textureID; // ID de la textura
    

    //---- FUNCIONES SET
    void setData();
    void setBuffersOpenGL();

};