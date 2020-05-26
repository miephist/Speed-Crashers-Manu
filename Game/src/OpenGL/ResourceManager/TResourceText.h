#ifndef TRESOURCETEXT_H
#define TRESOURCETEXT_H

#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H  

#include "../Interfaces/ITShader.h"
#include "TResource.h"

// Enlace: https://learnopengl.com/In-Practice/Text-Rendering

struct Character{
    GLuint      textID;     // ID de la textura
    glm::ivec2  Size;       // Tamaño del glifo   
    glm::ivec2  Bearing;    // Distancia desde la linea base hasta la parte izq/arriba del glifo
    GLuint      Advance;    // Distancia para avanzar al siguiente glifo
};

struct Params{

    std::string text; 
    GLfloat x; 
    GLfloat y; 
    GLfloat scale; 
    glm::vec3 color;

};

class TResourceText : public TResource {

    public:

        // Constructor and destructor
        TResourceText(std::string t, GLfloat newX, GLfloat newY, GLfloat s, glm::vec3 c, std::string f);
        ~TResourceText();

        // Cargamos la fuente
        void loadFont();

        // Init OpenGL
        void setupText();

        // Draw
        void draw(ITShader* shader);

        // Setters
        void setText(std::string text){parameters.text = text;};
        void setX(GLfloat x){parameters.x = x;};
        void setY(GLfloat y){parameters.y = y;};
        void setScale(GLfloat scale){parameters.scale = scale;};
        void setColor(glm::vec3 color){parameters.color = color;};
        void setParams(std::string t, GLfloat newX, GLfloat newY, GLfloat s, glm::vec3 c){ parameters = {t, newX, newY, s, c};};


        // Getters
        Params getParameters(){return parameters;};
        std::map<GLchar, Character> getMap(){return Characters;};
        GLuint getVAO(){return VAO;};
        GLuint getVBO(){return VBO;};

        const char *getName() override;
        void setName(const char *newName) override;

    private:

        char * ruta;
        std::string font;

        std::map<GLchar, Character> Characters;

        Params parameters;

        GLuint VAO, VBO;

        FT_Library ft;
        FT_Face face;

};

#endif