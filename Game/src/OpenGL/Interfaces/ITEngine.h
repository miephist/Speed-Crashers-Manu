#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ITAnimation.h"
#include "ITEntity.h"
#include "ITCamera.h"
#include "ITLight.h"
#include "ITResourceMesh.h"
#include "ITResourceText.h"
#include "ITPivote.h"
#include "../ResourceManager/TResourceManager.h"
#include "ITShader.h"
#include "../HUD/hud.h"
#include "../Skybox/Skybox.h"
#include "Lines.h"


//Maximo nivel de la interfaz tambien usado como fachada
class ITEngine{

    private:

        Skybox* skybox;

        //Instancia
        static ITEngine* instancia;

        //nodo a partir del cual van el resto
        TNode* scene;
        //manejador de recursos
        TResourceManager* manager;

        //vectores con las distintas luces
        std::vector<ITLight*> Focales;
        std::vector<ITLight*> Puntuales;
        std::vector<ITLight*> Direccionales;

        //vector con camaras creadas
        std::vector<ITCamera*> Camaras;

        GLFWwindow* window;
        int width, height;

        // Comprobar si el debug esta activo
        std::vector<Lines*> allLines;
        bool isDebugActive = false;

        // TEXTO
        std::vector<TResourceText*> vectorText;

    public:
        //constructor y destructor
        ITEngine();
        ~ITEngine();

        //cambiar tamaño ventana
        void resizeWindow(int newWidth, int newHeight);

        //set
        void setActiveCamera(ITCamera);
        void setProperties();
        void setHUDProperties();
        void setWidth(int newWidth)                 {width = newWidth;};
        void setHeight(int newHeight)               {height = newHeight;};   
        void setViewport(int x, int y, int width, int height);   
        void setDebug(bool state)                   {isDebugActive = state;};  

        //CREACIONES
        ITCamera* createCamera(glm::vec3 pos, glm::vec3 tar, viewport v);
        ITLight* createLight(glm::vec4 direc, glm::vec3 amb,glm::vec3 dif,glm::vec3 spec);
        ITLight* createLight(glm::vec3 amb, glm::vec3 dif ,glm::vec3 spec,glm::vec3 targ,glm::vec3 Pos,float cut,float out);

        ITResourceMesh* createMesh(const char*, const char*);
        TResourceTexture* createTexture(const char *file);
        TResourceText* createText(std::string t = "Texto de prueba", GLfloat newX = 25.0f, GLfloat newY = 25.0f, GLfloat s = 1.0f, glm::vec3 c = glm::vec3(0.5f, 0.8f, 0.2f), std::string f = "media/fonts/TIMES.TTF");

        ITPivote* createPivote();

        ITAnimation* createAnimation(std::string ruta,std::string ext,int ini, int fin, const char* text);

        //pasando nodo padre
        ITCamera* createCamera(TNode* father, glm::vec3 pos, glm::vec3 tar, viewport v);
        ITLight* createLight(TNode* father, glm::vec4 direc, glm::vec3 amb,glm::vec3 dif,glm::vec3 spec);
        ITLight* createLight(TNode* father, glm::vec3 amb, glm::vec3 dif ,glm::vec3 spec,glm::vec3 targ,glm::vec3 Pos,float cut,float out);        
        ITResourceMesh* createMesh(TNode* father, const char*, const char*);
        TResourceText* createText(TNode* father, std::string t = "Texto de prueba", GLfloat newX = 25.0f, GLfloat newY = 25.0f, GLfloat s = 1.0f, glm::vec3 c = glm::vec3(0.5f, 0.8f, 0.2f), std::string f = "media/fonts/TIMES.TTF");
        ITPivote* createPivote(TNode* father);

        ITAnimation* createAnimation(TNode* father,std::string ruta,std::string ext,int ini, int fin, const char* text);

        //SHADER
        ITShader* createShader(std::string, std::string);

        // HUD
        void newHud(const char* n);
        void drawHudMenus(ITShader* shaderHud);
        void cleanHUD(); //Limpieza de HUDs
        void setActiveHud(const char *n);
        hud *getHud(const char* n);
        hud* getActiveHud(){return activeHud;};

	    std::vector <hud*> HUDs; //Vector que guarda los diferentes huds-menus del motor
	    hud *activeHud; //Hud activo en cada momento

        // Skybox
        Skybox* createSkybox();
        void drawSkybox(ITShader* shaderSkybox);

        //DIBUJADO
        void draw(ITShader* shader);

        //GLFW
        GLFWwindow* getWindow(){return window;};

        //DEBUG
        Lines* createLine(float x, float y, float z, float a, float b, float c, glm::vec4 color);
        void drawLines(ITShader* shaderLines);
        bool getIsDebugActive(){return isDebugActive;};
        void drawText(ITShader* shader);

        //GET
        static ITEngine* getInstancia();
        TNode* getScene(){return scene;};
        int getWidth(){return width;};
        int getHeight(){return height;};

        //borra los objetos de la escena
        void resetScene();

        //Camara
        void useCamera(int);

        std::vector<TMesh*> createMalla(std::string ruta,std::string ext,int ini, int fin, const char* text);

        //cadena usada para concatenar en la creacion de animaciones
        char* coco;

};