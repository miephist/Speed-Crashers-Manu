#include "Skybox.h"
#include <include/OpenGL/stb_image.h>
//#include <../../include/OpenGL/stb_image.h>

Skybox::Skybox(){
    // Cargamos todas als texturas del cubo
    loadCubemap();
    // Cargamos los vetices del cubo
    setSkyboxVertices();
}

Skybox::~Skybox(){

}

//cargar imagen para colocar
unsigned char* Skybox::loadImage(const char* file, int pos){

    unsigned char* image = stbi_load(file, &width[pos], &height[pos], &channels[pos], 4);

    if(!image){
        std::cout<< "Error cargando la imagen con ruta: " << file << std::endl;
        return 0;
    }

    return image;
}

//ajustar la skybox
void Skybox::setupSkybox(){
    //Creamos una textura
    glGenTextures(1, &skyboxID);
    //Decimos que esta textura se trata de una de mapa de textura en forma de cubo (6 texturas = una textura por cada cara del cubo)
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);
    //Generamos las 6 texturas diferentes
    //Para cada lado del cubo, especificando su direccion en el primer parametro, le asignamos una de las imagenes cargadas junto con su respectivo ancho y alto
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width[0], height[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, textures[0]);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width[1], height[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, textures[1]);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width[2], height[2], 0, GL_RGBA, GL_UNSIGNED_BYTE, textures[2]);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width[3], height[3], 0, GL_RGBA, GL_UNSIGNED_BYTE, textures[3]);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width[4], height[4], 0, GL_RGBA, GL_UNSIGNED_BYTE, textures[4]);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width[5], height[5], 0, GL_RGBA, GL_UNSIGNED_BYTE, textures[5]);
    //Establecemos los parametros de cada textura
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    //Desactivamos el cubemap hasta que volvamos a usarlo
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

}
//cargar el cubo
void Skybox::loadCubemap(){

    //Cargamos las 6 imagenes distintas que se usaran en cada cara del cubo
    textures[0] = loadImage("media/skybox/darkcity_lf.tga", 0);
    textures[1] = loadImage("media/skybox/darkcity_rt.tga", 1);
    textures[2] = loadImage("media/skybox/darkcity_dn.tga", 2);
    textures[3] = loadImage("media/skybox/darkcity_up.tga", 3);
    textures[4] = loadImage("media/skybox/darkcity_ft.tga", 4);
    textures[5] = loadImage("media/skybox/darkcity_bk.tga", 5);
    
    //Creamos la textura cubo 
    setupSkybox();

    // Liberamos la memoria de las imagenes
    for (int i = 0; i < 6; i++){
        stbi_image_free(textures[i]);
    }
}

void Skybox::setSkyboxVertices(){

    GLfloat skyboxVertices[] = {
        // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
    };

    //Establecemos los buffers que pasaran los datos anteriores a los shaders para su dibujado
    //Creamos un VAO y un VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //Activamos el VAO
    glBindVertexArray(VAO);
    //Activamos el VBO, al que se le pasan los datos de posicion de cada vertice
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    //POSICION
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    //Desactivamos el VAO hasta que dibujemos
    glBindVertexArray(0);

}

void Skybox::draw(ITShader* shaderSkybox){

    glUseProgram(shaderSkybox->getShader()->getID());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);

    //Calculamos la matriz model del elemento
    glm::mat4 model = glm::mat4(1.0f);
    // Trasladamos el elemento para situarla correctamente
    model = glm::translate(model, glm::vec3(0, -15, 0));
    // Lo rotamos que ingame sale invetido debido a bullet
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0,0,1));
    // Lo escalamos para que englobe totalmente al mapa
    model = glm::scale(model, glm::vec3(400, 400, 400));
    // Calculamos la matriz mvp a partir de la projection y view de la camara activa
	glm::mat4 mvp = TEntity::cache.camera->getProjectionMatrix() * TEntity::cache.camera->getViewMatrix() * model;

    // Le pasamos la matriz al shader
    shaderSkybox->getShader()->setMat4("MVP", mvp);

    glUniform1i(glGetUniformLocation(shaderSkybox->getShader()->getID(), "skybox"), 0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

}