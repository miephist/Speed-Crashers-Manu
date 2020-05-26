#include "Lines.h"

Lines::Lines(float x, float y, float z, float a, float b, float c, glm::vec4 col){

    setAdditionalPoints(a,y,z,a,b,c);
    setColorLine(col);

    // Buffers para el debug de las fisicas
    glGenVertexArrays(1, &debugPhysicsVAO);
    glGenBuffers(1, &debugPhysicsVBO);

}

Lines::~Lines(){

}

void Lines::setAdditionalPoints(float x, float y, float z, float a, float b, float c){

    points.push_back(x);
    points.push_back(y);
    points.push_back(z);

    points.push_back(a);
    points.push_back(b);
    points.push_back(c);

}

void Lines::drawDebugLines(ITShader* shaderLines, bool isDebugActive){

    if(isDebugActive && points.size() > 0){

        glBindVertexArray(debugPhysicsVAO);

        glBindBuffer(GL_ARRAY_BUFFER, debugPhysicsVBO);
        glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), &points[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(0);

        glUseProgram(shaderLines->getShader()->getID());

        //Calculamos la matriz modelo por defecto
        glm::mat4 model = glm::mat4(1.0f);
        // Calculamos la matriz mvp a partir de la projection y view de la camara activa
	    glm::mat4 mvp = TEntity::cache.camera->getProjectionMatrix() * TEntity::cache.camera->getViewMatrix() * model;

        shaderLines->getShader()->setMat4("MVP", mvp);
        shaderLines->getShader()->setVec4("color", color);

        glLineWidth(3.0f);

        glDrawArrays(GL_LINES, 0, points.size());

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        points.clear();

    }
}