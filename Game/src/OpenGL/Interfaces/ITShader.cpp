#include "ITShader.h"

ITShader::ITShader(std::string vertex, std::string fragment){

    sha= new TShaderProgram(vertex, fragment);

}
ITShader::~ITShader(){
    
    delete sha;
}