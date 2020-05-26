#include "Camera.h"

Camera::Camera(){

    // Cargamos la camara
    glm::vec3 pos=glm::vec3(0.0f,1.0f,25.0f);
    glm::vec3 tar=glm::vec3(0.0f,0.0f,0.0f);
    viewport v;
    v.near = 0.1f;
    v.far = 1000.0f;
    v.fov = 60.0f;
    v.ratio = 1.77777777f;
    camera = ITEngine::getInstancia()->createCamera(pos, tar, v);

    change = false;
    isPressed = 0;

    // Keyboard
    oldState = GLFW_RELEASE;
    newState = -1;

    oldState2 = GLFW_RELEASE;
    newState2 = -1;

    zoom = Options::getInstancia()->getZoom();

    extraAngle = Options::getInstancia()->getAngle();

}

Camera::~Camera(){

}


void Camera::updateCamera(float angle, float angleCamera, ITResourceMesh* coche, float cameraHeight, ITPivote* jugadorpiv, char pantalla, ITResourceMesh* cocheIA){

    // Parametros mando
    bool controller = false;
    const float* axes = nullptr;
    const unsigned char* buttons = nullptr;
    const char* name = nullptr;

    // Comprobamos si se conecta un mando
    if(glfwJoystickPresent(GLFW_JOYSTICK_1) == 1){
        // Contador para los ejes
        int axesCount;
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

        // Contador para los botones
        int buttonsCount;
        buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonsCount);

        // Guardamos el nombre
        name = glfwGetJoystickName(GLFW_JOYSTICK_1);

        // Indicamos que el controlador/pad esta activo
        controller = true;
    }

    newState = glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_C);
    
    if(controller == true)
        newState2 = buttons[2];

    if((newState == GLFW_RELEASE && oldState == GLFW_PRESS &&  pantalla == 't') || ((controller && newState2 == GLFW_RELEASE && oldState2 == GLFW_PRESS && pantalla == 'm'))){
        isPressed = 1;
    }

    oldState = newState;
    oldState2 = newState2;

    if(isPressed == 1){
        if(change == false){
            change = true;
        }else{
            change = false;
        }
        isPressed = 0;
    }

    // Camara centrada en el coche
    if(change == false){

        if(ITEngine::getInstancia()->getIsDebugActive()){
            
            // Actualizamos los valores de la posicion de la camara
            nodePositionCamera.x = cocheIA->getPosition().x + (sin(angle + extraAngle) * (4.0f + zoom));
            nodePositionCamera.y = cocheIA->getPosition().y + 2.5f;
            nodePositionCamera.z = cocheIA->getPosition().z + (cos(angle + extraAngle) * (4.0f + zoom));

            // Actualizamos la posicion y target de la camara  
            camera->getCamera()->setCameraPosition(nodePositionCamera + glm::vec3(0,0.5f,4.f));

            // Lo situamos detras del coche
            nodePositionCamera.z = nodePositionCamera.z - 20;

            camera->getCamera()->setTargetPosition(nodePositionCamera);
            
        }else{
            // Actualizamos los valores de la posicion de la camara
            nodePositionCamera.x = coche->getPosition().x + (sin(angle + extraAngle) * (4.0f + zoom));
            nodePositionCamera.y = coche->getPosition().y + 2.5f;
            nodePositionCamera.z = coche->getPosition().z + (-1*(cos(angle + extraAngle)) * (4.0f + zoom));

            // Actualizamos la posicion y target de la camara  
            camera->getCamera()->setCameraPosition(nodePositionCamera + glm::vec3(0,0.5f,-4.f));
            camera->getCamera()->setTargetPosition(nodePositionCamera);
        }
    
    // Camara centarada en la pelota
    }else{

        if(ITEngine::getInstancia()->getIsDebugActive()){

            // Actualizamos los valores de la posicion de la camara
            nodePositionCamera.x = 0;
            nodePositionCamera.y = 225;
            nodePositionCamera.z = 1;

            // Actualizamos la posicion y target de la camara  
            camera->getCamera()->setCameraPosition(nodePositionCamera);
            camera->getCamera()->setTargetPosition(glm::vec3(0, -30, 0));

        }else{

            // Actualizamos los valores de la posicion de la camara
            nodePositionCamera.x = coche->getPosition().x + (sin(angleCamera + extraAngle) * (10.0f + zoom));
            nodePositionCamera.y = coche->getPosition().y + 2.5f;
            nodePositionCamera.z = coche->getPosition().z + (cos(angleCamera) * (10.0f + zoom));

            // Actualizamos la posicion y target de la camara  
            camera->getCamera()->setCameraPosition(nodePositionCamera);
            camera->getCamera()->setTargetPosition(Pelota::getInstancia()->getNode()->getPosition());

        } 
    }
}