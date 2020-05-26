#include "ITEngine.h"
#include <iomanip>
#include <iostream>
//inicializar cache
Cache TEntity::cache = Cache();
//inicializar instancia
ITEngine *ITEngine::instancia = nullptr;
//obtener instncia o crear si no existe
ITEngine *ITEngine::getInstancia(){

    if(instancia == nullptr)
        instancia = new ITEngine();

    return instancia;
}
//constructor
ITEngine::ITEngine(){

    scene= new TNode();

    // Inicializamos la libreria GLFW
    if(!glfwInit()){
        std::cout << "Error al iniciar la libreria GLFW" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Version minima de opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Version maxima de opengl
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Se usa la version Core de OpenGL

    // Ventana
    window = glfwCreateWindow(1280, 720, "Speed Crashers", NULL, NULL);

    // Nos devuelve en width y en height el tamanyo de la ventana actual
    glfwGetFramebufferSize(window, &width, &height);

    if(!window){
        glfwTerminate();
        std::cout << "Error al crear la ventana" << std::endl;
    }

    

    // Indicamos que window va a ser nuestra ventana actual
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK){
        std::cout << "Error al iniciar la libreria GLEW" << std::endl;
    }

    setProperties();

    // Inicializamos el gestor de recursos
    manager = new TResourceManager();
    
}

ITEngine::~ITEngine(){

    delete manager;
    delete scene;

    delete coco;

    Focales.clear();
    Puntuales.clear();
    Direccionales.clear();
    Camaras.clear();

    instancia = nullptr;

}
//destructor
void ITEngine::resetScene(){
    if(scene){
        delete scene;
    }

    if(manager){
        delete manager;
    }

    scene= new TNode();
    manager= new TResourceManager();

    Focales.clear();
    Puntuales.clear();
    Direccionales.clear();
    Camaras.clear();
 
}

// Redimensiona la pantalla
void ITEngine::resizeWindow(int newWidth, int newHeight){

    // Opcion full screen
    if(newWidth == 1920){
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
    // Opcion ventana
    }else{
        glfwSetWindowMonitor(window, NULL, 0, 0, newWidth, newHeight, 60);
    }
    
    glViewport(0,0,newWidth,newHeight);

    // Seteamos nuevos valores de la ventana
    setWidth(newWidth);
    setHeight(newHeight);

    // Actualizamos fondo
    getActiveHud()->deleteElement("fondo");
    getActiveHud()->addElement("fondo", "media/GUI/Start/Play.png");  

}

//Crea luz puntual o direccional y la coloca a partir del nodo raiz
ITLight* ITEngine::createLight(glm::vec4 direc, glm::vec3 amb,glm::vec3 dif,glm::vec3 spec){

    ITLight* luz= new ITLight(scene, direc, amb, dif, spec);

    //1 puntual     //0 direccional
    if(direc[3]==1){
        Puntuales.push_back(luz);
        TLight* n=(TLight*)luz->getNode()->getEntity();
        n->setID(Puntuales.size()-1);
    }
    else{
        Direccionales.push_back(luz);
        TLight* n=(TLight*)luz->getNode()->getEntity();
        n->setID(Direccionales.size()-1);

    }

    return luz;
}

//Crea luz puntual o direccional y la coloca a partir del nodo padre
ITLight* ITEngine::createLight(TNode* father,glm::vec4 direc, glm::vec3 amb,glm::vec3 dif,glm::vec3 spec){

    ITLight* luz= new ITLight(father,direc, amb, dif, spec);

    
    if(direc[3]==1){
        Puntuales.push_back(luz);
        TLight* n=(TLight*)luz->getNode()->getEntity();
        n->setID(Puntuales.size()-1);
    }
    else{
        Direccionales.push_back(luz);
        TLight* n=(TLight*)luz->getNode()->getEntity();
        n->setID(Direccionales.size()-1);
    }
    return luz;
}


//Crea luz focal y la coloca a partir del nodo raiz
ITLight* ITEngine::createLight(glm::vec3 amb, glm::vec3 dif ,glm::vec3 spec,glm::vec3 targ,glm::vec3 Pos,float cut,float out){

    ITLight* luz= new ITLight(scene, amb, dif, spec, targ, Pos,cut,out);

        Focales.push_back(luz);
        TLight* n=(TLight*)luz->getNode()->getEntity();
        n->setID(Focales.size()-1);
    
    return luz;
}

//Crea luz focal y la coloca a partir del nodo padre
ITLight* ITEngine::createLight(TNode* father,glm::vec3 amb, glm::vec3 dif ,glm::vec3 spec,glm::vec3 targ,glm::vec3 Pos,float cut,float out){

    ITLight* luz= new ITLight(father, amb, dif, spec, targ, Pos,cut,out);

        Focales.push_back(luz);
        TLight* n=(TLight*)luz->getNode()->getEntity();
        n->setID(Focales.size()-1);
    
    return luz;
}

//Crea camara y la coloca a partir del nodo raiz
ITCamera* ITEngine::createCamera(glm::vec3 pos, glm::vec3 tar, viewport v){

    ITCamera* cam= new ITCamera(scene, pos, tar, v);

    Camaras.push_back(cam);

    TEntity::cache.setCamera(cam->getCamera());

    return cam;
}


//Crea camara y la coloca a partir del nodo padre
ITCamera* ITEngine::createCamera(TNode* father, glm::vec3 pos, glm::vec3 tar, viewport v){

    ITCamera* cam= new ITCamera(father, pos, tar, v);

    Camaras.push_back(cam);

    TEntity::cache.setCamera(cam->getCamera());

    return cam;
}

//cambiar camara para usar
void ITEngine::useCamera(int pos){


    if(pos>0 && pos>=Camaras.size()){
        TEntity::cache.setCamera(Camaras.at(pos-1)->getCamera());
    }
}


//Crea malla y la coloca a partir del nodo raiz
ITResourceMesh* ITEngine::createMesh(const char *file, const char *text){

    TResourceMesh *mesh;
    mesh = (TResourceMesh*)manager->getResource(file, 0);

    TResourceTexture *texture = (TResourceTexture*)manager->getResource(text,1);

    ITResourceMesh* malla = new ITResourceMesh(scene, mesh, texture);

    return malla;
}

//Crea malla y la coloca a partir del nodo padre
ITResourceMesh* ITEngine::createMesh(TNode* father, const char *file, const char *text){

    TResourceMesh *mesh;
    mesh = (TResourceMesh*)manager->getResource(file, 0);

    TResourceTexture *texture = (TResourceTexture*)manager->getResource(text,1);

    ITResourceMesh* malla= new ITResourceMesh(father, mesh, texture);

    return malla;
}
//crea el conjunto de objetos que supone la animacion
std::vector<TMesh*> ITEngine::createMalla(std::string ruta,std::string ext,int ini,int fin, const char* text){
    
    std::vector<TMesh*> Mallas;
    for(int i=ini;i<fin;i++){
        //crear ruta objeto
        std::string num=std::to_string(i);
        std::stringstream ss;
        ss << std::setw(4) << std::setfill('0') << std::to_string(i);
        
        std::string str = ss.str();
        std::string anima=ruta+str+ext;

        // se añade a cadena dinamica
        coco = new char[anima.size()+1];
        std::strncpy(coco, anima.c_str(), anima.size()+1);
        
        //crear animacion
        TResourceMesh *mesh;
        mesh = (TResourceMesh*)manager->getResource(coco, 0);
        TResourceTexture *texture;
        texture = (TResourceTexture*)manager->getResource(text,1);
        
        //falta material
        TMesh* malla=new TMesh(mesh, texture);
        Mallas.push_back(malla);
    }

    return Mallas;
}

//Crea animacion y la coloca a partir del nodo raiz
ITAnimation* ITEngine::createAnimation(std::string ruta,std::string ext,int ini,int fin, const char* text){

    std::vector<TMesh*> Mallas;
    
    Mallas=createMalla(ruta,ext,ini,fin, text);

    ITAnimation* anim= new ITAnimation(scene,Mallas);

    return anim;
}

//Crea animacion y la coloca a partir del nodo padre
ITAnimation* ITEngine::createAnimation(TNode* father, std::string ruta,std::string ext,int ini,int fin, const char* text){
    
    std::vector<TMesh*> Mallas;
    
    Mallas=createMalla(ruta,ext, ini,fin, text);

    ITAnimation* anim= new ITAnimation(father,Mallas);

    return anim;
}


// Crea las texturas para el menu y HUD
TResourceTexture* ITEngine::createTexture(const char *file){

    TResourceTexture *texture = (TResourceTexture*)manager->getResource(file,1, true);

    return texture;

}

// Crea pivote
ITPivote* ITEngine::createPivote(TNode* father){

    ITPivote* piv= new ITPivote(father);

    return piv;

}

// Crea pivote con scene
ITPivote* ITEngine::createPivote(){

    ITPivote* piv= new ITPivote(scene);

    return piv;

}


//Crear un shader
ITShader* ITEngine::createShader(std::string vertex, std::string fragment){

    ITShader* shader= new ITShader(vertex, fragment);

    return shader;
}
//Crear skybox
Skybox* ITEngine::createSkybox(){
    
    skybox = new Skybox();

    return skybox;
}
//dibujado de skybox
void ITEngine::drawSkybox(ITShader* shaderSkybox){

    skybox->draw(shaderSkybox);

}
//establece hud
void ITEngine::setHUDProperties(){

    glFrontFace(GL_CW);

}

void ITEngine::setProperties(){

    // Activamos buffer de profundidad
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Activamos las caras y lo ponemos en sentido antihorario
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); 
    glFrontFace(GL_CCW);

}

//dibujar el arbol
void ITEngine::draw(ITShader* shader){

    TEntity::cache.setShader(shader->getShader());
    glUseProgram(shader->getShader()->getID());

    for(int z=0;z<3;z++){

      scene->draw(z);               //0 luces, 1 camara, 2 el resto
    }
    
}   

void ITEngine::setViewport(int x, int y, int width, int height){

    glViewport(x,y,width,height);

}

/* ----------- HUD ------------------- */

void ITEngine::newHud(const char* n) {
	//Creamos el nuevo hud con su nombre
	hud* h = new hud(n);
	//Lo añadimos al array de hud
	HUDs.push_back(h);
	//Lo activamos por defecto
	setActiveHud(n);
}

//Funcion que dibuja el hud activo 
void ITEngine::drawHudMenus(ITShader* shaderHud) {
	//Desactivamos el z-buffer, queremos dibujarlo encima de todo
    glFrontFace(GL_CW);
	glDisable(GL_DEPTH_TEST);
    //glFrontFace(GL_CW);
	//Se activa el shader para el dibujado del HUD
	//shaderHUD->use();
    glUseProgram(shaderHud->getShader()->getID());
	//Dibujamos el hud activo
	activeHud->drawHud(shaderHud);
	//Desactivamos el z-buffer, queremos dibujarlo encima de todo
    glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
}

//Funcion que limpia el array de HUDs del motor
void ITEngine::cleanHUD() {
	HUDs.clear();
}

//Funcion para activar un hud, que sera el que se utilice, solo puede haber un hud activo por iteracion
void ITEngine::setActiveHud(const char* n) {
	hud* h = getHud(n); //Obtenemos el hud a partir del nombre
	activeHud = h; //Lo activamos
}
//obtener el hud
hud* ITEngine::getHud(const char* n) {
	hud* h = NULL;
	//Recorremos el array de HUDs
	for (int i = 0; i < HUDs.size(); i++) {
		//Comparamos los nombres y nos guardamos el correcto
		if (strcmp(HUDs.at(i)->getName(), n) == 0) {
			h = HUDs.at(i);
		}
	}
	return h;
}


/*****************
 ***** DEBUG *****
 ****************/

Lines* ITEngine::createLine(float x, float y, float z, float a, float b, float c, glm::vec4 color){

    Lines* l = new Lines(x,y,z,a,b,c,color);

    allLines.push_back(l);

    return l;

}

void ITEngine::drawLines(ITShader* shaderLines){

    for(unsigned int i = 0; i < allLines.size(); i++){
        allLines.at(i)->drawDebugLines(shaderLines, isDebugActive);
    }
}

TResourceText* ITEngine::createText(std::string text, GLfloat newX, GLfloat newY, GLfloat s, glm::vec3 c, std::string f){

    //TResourceText *t = (TResourceText*)manager->getResource(file,2);

    TResourceText *t = new TResourceText(text, newX, newY, s, c, f);

    vectorText.push_back(t);

    //ITResourceText* text = new ITResourceText(scene, t, s->getShader());

    return t;

}

TResourceText* ITEngine::createText(TNode* father, std::string text, GLfloat newX, GLfloat newY, GLfloat s, glm::vec3 c, std::string f){

    //TResourceText *t = (TResourceText*)manager->getResource(file,2);

    TResourceText *t = new TResourceText(text, newX, newY, s, c, f);

    vectorText.push_back(t);

    //ITResourceText* text = new ITResourceText(father, t, s->getShader());

    return t;

}

void ITEngine::drawText(ITShader* shader){

    for(unsigned int i = 0; i < vectorText.size(); i++){
        vectorText.at(i)->draw(shader);
    }
}