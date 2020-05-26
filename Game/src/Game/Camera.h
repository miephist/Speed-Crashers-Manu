#pragma once
#include "Pelota.h"
#include "../Engines/structs.h"
#include "../Engines/Options.h"

class Camera{

public:

     // Constructor
    Camera();

    // Destrcutor
    ~Camera();

    // Variables
    ITCamera* camera;
    glm::vec3 nodePositionCamera;

    // Funciones
    void updateCamera(float angle,float angleCamera, ITResourceMesh* coche, float cameraHeight, ITPivote* jugadorpiv, char pantalla, ITResourceMesh* cocheIA);

    // Change zoom of the camera
    void setZoom(float newZoom)     {zoom = newZoom;};
    void setAngle(float newAngle)   {extraAngle = newAngle;};

    // Activar la camara actual
    void setActivate(bool s)    {camera->Activate(s);};

private:

    //Instancia
    int isPressed;
    bool change;

    // Keyboard && Joystick
    int oldState;
    int oldState2;

    int newState;
    int newState2;

    float zoom;
    float extraAngle;

};