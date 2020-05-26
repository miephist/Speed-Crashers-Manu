#ifndef TRESOURCETEXTURE_H
#define TRESOURCETEXTURE_H

#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TResource.h"

class TResourceTexture : public TResource {

    public:

        // Constructor and destructor
        TResourceTexture();
        ~TResourceTexture();

        // Cargar textura
        void loadTexture(std::string file);

        // Init OpenGL
        void setupTexture();

        // Getters and Setters
        float getWidth()          { return width;};
        float getHeight()         { return height;};
        int getChannels()       { return channels;};
        GLuint getTextureID()   { return textureID;};

        const char *getName() override;
        void setName(const char *newName) override;

        void setFlip(bool flip);

    private:

        unsigned char* image;
        int width, height, channels;

        GLuint textureID;

};

#endif