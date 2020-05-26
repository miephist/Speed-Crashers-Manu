#include "elementoHud.h"
#include "../Interfaces/ITEngine.h"

//Constructor que crea e inicializa el quad con una textura
elementoHud::elementoHud(const char* n, const char* p){  

    //Guardamos los datos 
    TResourceTexture* texture = ITEngine::getInstancia()->createTexture(p);

    float x = texture->getWidth()/1280;
    float y = texture->getHeight()/720;
    
    width = x; 
    height = y; 
    name = n; 
    path = p; 
    color = glm::vec4(0.f, 0.f, 0.f, 0.f);
    transparency = false;
    transLevel = 0.6; //Por defecto

    // Inicializamos matrices
    tras = glm::mat4(1.0f);
    rot = glm::mat4(1.0f);
    esc = glm::mat4(1.0f);

    //Inicializamos y creamos el elemento del hud
    setData();
    setBuffersOpenGL();
}

//Constructor que crea e inicializa el quad con una color
elementoHud::elementoHud(const char* n, glm::vec4 c){ 
    //Guardamos los datos 

    TResourceTexture* texture = ITEngine::getInstancia()->createTexture(n);

    float x = ITEngine::getInstancia()->getWidth()/texture->getWidth();
    float y = ITEngine::getInstancia()->getHeight()/texture->getHeight();

    width = x; 
    height = y; 
    name = n; 
    path = ""; 
    color = c;
    transparency = false;
    transLevel = 0.6; //Por defecto
    
    // Inicializamos matrices
    tras = glm::mat4(1.0f);
    rot = glm::mat4(1.0f);
    esc = glm::mat4(1.0f);

    //Inicializamos y creamos el elemento del hud
    setData();
    setBuffersOpenGL();

}

//Destructor del elemento hud
elementoHud::~elementoHud(){
    //Eliminar los distintos buffers utilizados por OpenGL
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);

}


//Funcion que asigna las posiciones de los vertices del quad a partir del ancho y alto definido
//Tambien, establece las coordenadas de textura para cada punto
void elementoHud::setData(){
    //Dividimos entre 2 para sacar la x e y normalizadas entre [-1, 1]
    float x = width;
    float y = height;

    array <float, 32> vertices = {
        //Posiciones     // Colores         // Texturas
        x,   y, 0.0f,    1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   //Esquina superior derecha
		x,  -y, 0.0f,    0.0f, 1.0f, 0.0f,  1.0f, 0.0f,   //Esquina inferior derecha
		-x, -y, 0.0f,    0.0f, 0.0f, 1.0f,  0.0f, 0.0f,   //Esquina inferior izquierda
		-x,  y, 0.0f,    1.0f, 1.0f, 0.0f,  0.0f, 1.0f    //Esquina superior izquierda
    }; 

    //Guardamos los datos del quad
    data = vertices;
}

//Funcion que inicializa los buffers de OpenGL y pasa los datos  de los vertices y coordenadas de textura
void elementoHud::setBuffersOpenGL(){
    //Inicalizar cada uno de los buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Enlazar el VAO en el que se guardan los distintos datos
    glBindVertexArray(VAO);

    //Enlazar el VBO al que se le pasan los datos del quad
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data[0], GL_STATIC_DRAW);

    //Enlazar el EBO, al que se le pasan los indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //Desactivamos el VAO hasta el dibujado del quad
    glBindVertexArray(0); 
}

//Funcion para dibujar el elemento hud
void elementoHud::draw(ITShader* shaderHud){

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ITEngine::getInstancia()->createTexture(path)->getTextureID());

    glm::mat4 model = rot * esc * tras;

    //enviar matriz modelo al shader
    glUniformMatrix4fv(shaderHud->getShader()->modelViewProjectionMatrixId, 1, GL_FALSE, &model[0][0]);

    shaderHud->getShader()->setBool("transparency", transparency);
    shaderHud->getShader()->setFloat("transparencyLevel", transLevel);

    //Enlazamos el VAO que antes hemos rellenado
    glBindVertexArray(VAO);
    //Dibujamos el quad con OpenGL
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //Vaciamos los datos utilizamos
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

//Funcion para rotar el elemento sobre si mismo
void elementoHud::rotacion(float angle){
    glm::vec3 myRotationAxis(0.0f, 0.0f, 1.0f);
	rot =  glm::rotate(rot, glm::radians(angle), myRotationAxis);
}

//Funcion para trasladar el elemento por la pantalla
void elementoHud::traslacion(float x, float y){
    tras = glm::translate(tras, glm::vec3(x, y, 0.0f));
}

//Funcion para escalar el elemento hud
void elementoHud::escalado(float x, float y){
    esc = glm::scale(esc, glm::vec3(x,y,1.0f));
}

//Funcion que devuelve el nombre 
const char* elementoHud::getName(){ 
    return name; 
}

//Funcion para cambiar la textura del elemento hud
void elementoHud::cambiarTextura(const char* p){
    //Asignar la nueva ruta
    path = p;
}

//Funcion para cambiar el color del elemento hud
void elementoHud::cambiarColor(glm::vec4 c){
    //Asignar el nuevo color
    color = c;
}

//Funcion para cambiar la transparencia del elemento
//0 == totalmente trasparente , 1 == opaco
void elementoHud::cambiarTransparencia(bool t, float l){
    //Asignamos si el elemento sera transparente o no
    transparency = t;
    //Asignamos el nivel de transparencia en caso de que si lo sea
    transLevel = l;
}