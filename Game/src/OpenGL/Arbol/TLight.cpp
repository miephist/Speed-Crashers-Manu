#include "TLight.h"

#include "TShaderProgram.h"
#include "TCamera.h"

//https://learnopengl.com/Lighting/Colors

TLight::TLight(glm::vec3 amb, glm::vec3 dif, glm::vec3 spec){

    Activate(true);

    setSpecular(spec);
    setAmbient(amb);
    setDiffuse(dif);

    // Generamos el array de vertices
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // we only need to bind to the VBO, the container's VBO's data already contains the correct data.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // set the vertex attributes (only position data for our lamp)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}

TLight::~TLight(){
}