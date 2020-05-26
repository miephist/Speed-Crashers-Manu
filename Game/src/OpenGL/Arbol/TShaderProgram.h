#define GLM_ENABLE_EXPERIMENTAL

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TEntity.h"

class TShaderProgram : public TEntity{
    public:

    //constructor y destructor
    TShaderProgram(std::string, std::string);
    ~TShaderProgram();
    //dibujado
    void beginDraw(int);
    void endDraw(int);
 
    //setter
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setVec3(const std::string &name, const glm::vec3 &value);
    void setVec4(const std::string &name, const glm::vec4 &value);
    void setMat3(const std::string &name, const glm::mat3 &value);
    void setMat4(const std::string &name, const glm::mat4 &value);

    //getter
    GLuint getID(){return programId;};

    //mvp id
    void registerVar();


    //variables del shader
    GLuint modelViewProjectionMatrixId;
    GLuint projectionMatrixId;
    GLuint viewMatrixId;
    GLuint modelMatrixId;
    GLuint TransInvMatrixId;

    //luz
    GLuint lightAmountId;
    GLuint lightBufferId;
    GLuint lightPointerId;

    private:

    GLuint vertexShaderId;
    GLuint fragmentShaderId;
    GLuint programId;

};