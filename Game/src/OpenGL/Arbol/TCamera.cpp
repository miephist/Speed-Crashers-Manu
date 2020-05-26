#include "TCamera.h"
#include "TShaderProgram.h"

TCamera::TCamera(viewport newv) : TEntity(){

    TEntity::cache.camera = this;

    view=newv;
    type = TCamera::CamType::PERSPECTIVE;
    camPosition = glm::vec3(0,0,0);
    target = glm::vec3(0,0,0);

    calculateProjectionMatrix();
    calculateViewMatrix();

    tipo=0;

}

TCamera::~TCamera(){

    //son de memoria estatica no hace falta pasarlos, si fuesen punteros si
}

void TCamera::beginDraw(int pasada){

    if(pasada==1 && TEntity::cache.getCamera()==this){

        TEntity::cache.camera = this;
        //aplicar transformaciones
        glm::vec3 pos=glm::vec3(TEntity::cache.mpila.top()*glm::vec4(camPosition,1.f));
        
        //camara que el target se traslada junto a la posicion
        //suele ser para camaras sin objetivo fijo, solamente seguir pnj
        if(tipo==0){

            glm::vec3 tar=glm::vec3(TEntity::cache.mpila.top()*glm::vec4(target,1.f));
            calculateViewMatrix(pos, tar);
        }
        //camara cuyo target se actualiza con la posicion del objeto al que está mirando
        else{
            calculateViewMatrix(pos);
        }

        glUniformMatrix4fv(TEntity::cache.shader->projectionMatrixId, 1, GL_FALSE, glm::value_ptr(projectionMatrix)); 
        glUniformMatrix4fv(TEntity::cache.shader->viewMatrixId, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    }
    
}

void TCamera::endDraw(int pasada){
    
}

void TCamera::calculateViewMatrix(){
    viewMatrix = glm::lookAt(camPosition,
                                target,
                                glm::vec3(0,1,0));
    
}

void TCamera::calculateViewMatrix(glm::vec3 Pos){
    viewMatrix = glm::lookAt(Pos,
                                target,
                                glm::vec3(0,1,0));
    
}

void TCamera::calculateViewMatrix(glm::vec3 Pos, glm::vec3 Tar){
    viewMatrix = glm::lookAt(Pos,
                                Tar,
                                glm::vec3(0,1,0));
    
}

void TCamera::setTargetPosition(glm::vec3 tar){
    target = tar;
    calculateViewMatrix();
}

void TCamera::setCameraPosition(glm::vec3 pos){
    camPosition = pos;
    calculateViewMatrix();
}

void TCamera::setNear(float n){
    view.near = n;
    calculateProjectionMatrix();
}

void TCamera::setFar(float f){
    view.far = f;
    calculateProjectionMatrix();
}

void TCamera::setFov(float fo){
    view.fov = fo;
    calculateProjectionMatrix();
}

void TCamera::calculateProjectionMatrix(){
    
    if(type == TCamera::CamType::PERSPECTIVE)
        projectionMatrix = glm::perspective(glm::radians(view.fov), view.ratio, view.near, view.far); //fov y aspect ratio de la pantalla
    
}

glm::mat4 TCamera::getProjectionMatrix(){

    return(projectionMatrix);
}

glm::mat4 TCamera::getViewMatrix(){
    return(viewMatrix);
}

glm::vec3 TCamera::getPosition(){
    return(camPosition);
}
