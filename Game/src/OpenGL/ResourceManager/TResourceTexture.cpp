#include "TResourceTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <include/OpenGL/stb_image.h>

TResourceTexture::TResourceTexture(){}

TResourceTexture::~TResourceTexture(){
    delete image;
}


void TResourceTexture::loadTexture(std::string file){

    // Conversión de file a const char* (necesario para SOIL)
    char * writable = new char[file.size() + 1];
    std::copy(file.begin(), file.end(), writable);
    writable[file.size()] = '\0';

    image = stbi_load(writable, &width, &height, &channels, STBI_default);

    if(!image){
        std::cout<< "Error cargando la imagen con ruta: " << file << std::endl;
        return;
    }
}

void TResourceTexture::setupTexture(){

    // Generamos los buffers
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glGenerateMipmap(GL_TEXTURE_2D);

    if (channels == 1)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, image);
    else if (channels == 2)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, image);
    else if (channels == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    else if (channels == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(image);

}

void TResourceTexture::setFlip(bool flip){

    stbi_set_flip_vertically_on_load(flip);

}

const char *TResourceTexture::getName(){
    return name;
}

void TResourceTexture::setName(const char *newName){
    name = newName;
}
