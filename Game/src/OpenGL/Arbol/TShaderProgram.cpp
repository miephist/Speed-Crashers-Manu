#include "TShaderProgram.h"
#include "TLight.h"

TShaderProgram::TShaderProgram(std::string vertexShader, std::string fragmentShader){
    std::string vertexShaderCode;
    //carga de shader, se transforma de stream de bits a texto para pasarselo a la grafica
    std::ifstream vertexShaderStream(vertexShader, std::ios::in);
    if(vertexShaderStream.is_open()){
        std::stringstream stream;
        stream<<vertexShaderStream.rdbuf();
        vertexShaderCode = stream.str();
        vertexShaderStream.close();
    }
    
    //reservamos espacio para el shader para la compilacion en la grafica
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

    //compilamos el vertexShader en la grafica
    const char *vertexShaderSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderId, 1, &vertexShaderSourcePointer, NULL);
    glCompileShader(vertexShaderId);
    
    //comprobamos que se haya compilado bien
    GLint vertexShaderResult = GL_FALSE;
    GLint vertexShaderInfoLogLenght;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &vertexShaderResult);
    glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &vertexShaderInfoLogLenght);
    if(vertexShaderInfoLogLenght > 0){
        std::vector<char> vertexShaderErrorMessage(vertexShaderInfoLogLenght+1);
        glGetShaderInfoLog(vertexShaderId, vertexShaderInfoLogLenght, NULL, &vertexShaderErrorMessage[0]);
        std::cerr<<"ERROR: "<<&vertexShaderErrorMessage[0]<<"."<<std::endl;
        exit(0);
    }

    std::string fragmentShaderCode;
    //carga de shader, se transforma de stream de bits a texto para pasarselo a la grafica
    std::ifstream fragmentShaderStream(fragmentShader, std::ios::in);
    if(fragmentShaderStream.is_open()){
        std::stringstream stream;
        stream<<fragmentShaderStream.rdbuf();
        fragmentShaderCode = stream.str();
        fragmentShaderStream.close();
    }
    //reservamos espacio para el shader para la compilacion en la grafica
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    //compilamos el fragmentShader en la grafica
    const char *fragmentShaderSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSourcePointer, NULL);
    glCompileShader(fragmentShaderId);
    
    //comprobamos que se haya compilado bien
    GLint fragmentShaderResult = GL_FALSE;
    GLint fragmentShaderInfoLogLenght;
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &fragmentShaderResult);
    glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &fragmentShaderInfoLogLenght);
    if(fragmentShaderInfoLogLenght > 0){
        std::vector<char> fragmentShaderErrorMessage(fragmentShaderInfoLogLenght+1);
        glGetShaderInfoLog(fragmentShaderId, fragmentShaderInfoLogLenght, NULL, &fragmentShaderErrorMessage[0]);
        std::cerr<<"ERROR: "<<&fragmentShaderErrorMessage[0]<<"."<<std::endl;
        exit(0);
    }

    //############################################################################
    //############# CREAMOS EL PROGRAMA QUE UTILIZA LOS SHADERS ##################
    programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);

    //Comprobamos la creacion del programa
    GLint programResult = GL_FALSE;
    GLint infoLogLenght;
    glGetProgramiv(programId, GL_LINK_STATUS, &programResult);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLenght);
    if(infoLogLenght > 0){
        std::vector<char> programErrorMessage(infoLogLenght+1);
        glGetProgramInfoLog(programId, infoLogLenght, NULL, &programErrorMessage[0]);
        std::cerr<<"ERROR: "<<&programErrorMessage[0]<<"."<<std::endl;
        exit(0);
    }
    modelMatrixId=glGetUniformLocation(programId, "M");//model
    projectionMatrixId = glGetUniformLocation(programId, "P");// proyeccion 
    viewMatrixId = glGetUniformLocation(programId, "V");// vista
    modelViewProjectionMatrixId = glGetUniformLocation(programId, "MVP");
    TransInvMatrixId= glGetUniformLocation(programId, "TI");

    TEntity::cache.shader = this;

}

TShaderProgram::~TShaderProgram(){
    glDetachShader(programId, vertexShaderId);
    glDeleteShader(vertexShaderId);
    glDetachShader(programId, fragmentShaderId);
    glDeleteShader(fragmentShaderId);
    glDeleteProgram(programId);
}

void TShaderProgram::beginDraw(int pasada){
    glUseProgram(programId);
    TEntity::cache.shader = this;
}
void TShaderProgram::endDraw(int pasada){

}

void TShaderProgram::registerVar(){
    modelViewProjectionMatrixId = glGetUniformLocation(programId, "MVP");
}

//Funcion que establece un uniform de tipo boolean
void TShaderProgram::setBool(const std::string &name, bool value){
	glUniform1i(glGetUniformLocation(programId, name.c_str()), (int)value);
}

//Funcion que establece un uniform de tipo int
void TShaderProgram::setInt(const std::string &name, int value){
	glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

//Funcion que establece un uniform de tipo float
void TShaderProgram::setFloat(const std::string &name, float value){
	glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}

//Funcion set vec3
void TShaderProgram::setVec3(const std::string &name, const glm::vec3 &value){
    glUniform3fv(glGetUniformLocation(programId,name.c_str()),1, &value[0]);
}

//Funcion set vec4
void TShaderProgram::setVec4(const std::string &name, const glm::vec4 &value){
    glUniform4fv(glGetUniformLocation(programId,name.c_str()),1, &value[0]);
}
//Funcion set Mat3
void TShaderProgram::setMat3(const std::string &name, const glm::mat3 &value){
    glUniformMatrix3fv(glGetUniformLocation(programId,name.c_str()),1,GL_FALSE, &value[0][0]);
}
//Funcion set Mat4
void TShaderProgram::setMat4(const std::string &name, const glm::mat4 &value){
    glUniformMatrix4fv(glGetUniformLocation(programId,name.c_str()),1,GL_FALSE, &value[0][0]);
}

