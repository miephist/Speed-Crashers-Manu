#include "TTransform.h"
#include "TEntity.h"


//TEntity::mpila.push(glm::mat4(1.0f));
//mpila.push(glm::mat4(1.0f));
TTransform::TTransform() : TEntity() {
    identity();
    resultado = glm::mat4(1.0f);
}

TTransform::~TTransform(){

}

void TTransform::identity(){

    // Matriz identidad
    matrix = glm::mat4(1.0f);

}

void TTransform::inverse(){
    matrix=glm::inverse(matrix);
}

void TTransform::load(glm::mat4 newMatrix){

    matrix = newMatrix;

}

void TTransform::transpose(){

    // Darle la vuelta a la matriz
    matrix = glm::transpose(matrix);

}

void TTransform::translate(float x, float y, float z){
    identity();
    matrix = glm::translate(matrix, glm::vec3(x, y, z));

}

void TTransform::translate(glm::vec3 trans){
    identity();
    matrix = glm::translate(matrix, trans);

}

void TTransform::rotate(float x, float y, float z, float angle){
    identity();
    glm::vec3 myRotationAxis(x,y,z);
    matrix = glm::rotate(matrix, glm::radians(angle), myRotationAxis);

}

void TTransform::rotate(glm::vec3 rotAxis, float angle){
    identity();
    matrix=glm::rotate(matrix,glm::radians(angle),rotAxis);
}

void TTransform::scale(float x, float y, float z){
    identity();
    matrix = glm::scale(matrix, glm::vec3(x,y,z));
    
}

void TTransform::scale(glm::vec3 scal){
    identity();
    matrix=glm::scale(matrix, scal);
}

void TTransform::beginDraw(int pasada){

    resultado = matrix*TEntity::cache.mpila.top();
    TEntity::cache.mpila.push(resultado);
    
}

void TTransform::endDraw(int pasada){

    TEntity::cache.mpila.pop();
    
}