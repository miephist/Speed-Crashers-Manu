#include "TResourceManager.h"

TResourceManager::TResourceManager(){}
TResourceManager::~TResourceManager(){
    if(resources.size()>0){
        for(int z=0;z<resources.size();z++){
            delete resources.at(z);
        }
        resources.clear();
    }
}


/** parametro type:
 *  - 0: Tipo malla.
 *  - 1: TIpo textura.
 *  - 2: Tipo texto.
 *  - 3: Tipo JSON.
 *  parametro flip:
 *  - True: Voltear verticalmente la imagen (solo en menus).
 */
TResource *TResourceManager::getResource(const char *name, int type, bool flip){
    TResourceMesh *mesh = nullptr; // Buscar el recurso mesh en el vector
    TResourceTexture *texture = nullptr;
    TResourceMaterial *material = nullptr;
    TResourceText *text = nullptr;
    TResourceJSON *json = nullptr;

    for(GLuint i=0; i < resources.size(); i++){
        // Si coincide el nombre del resource pasado por parametro
        // con alguno de los del vector se guarda en rec y se devuelve
            if(resources.at(i)->getName() == name){
                if(type == 0){
                }else if(type == 1){
                    texture = (TResourceTexture*)resources.at(i);
                    return texture;
                }else if(type == 2){
                    //text = (TResourceText*)resources.at(i);
                    //return text;
                }else if(type == 3){
                    json = (TResourceJSON*)resources.at(i);
                    return json;
                }
            }
    }

    // Si no existe el resource malla que buscamos
    if(mesh == nullptr && type == 0){
        // Creamos el objeto malla
        mesh = new TResourceMesh();
        // Cargamos el archivo de malla con la ruta indicada que nos pasan por parametro
        mesh->loadMesh(name);
        // Inicializamos valores de OpenGL
        mesh->setupMesh();
        // Seteamos su nombre
        mesh->setName(name);
        // Obtenemos su material
        mesh->getMaterial()->loadMaterial(name);
        // Anayadirlo al vector de recursos mediante un push_back
        resources.push_back(mesh);

        return mesh;

    // Si no existe el resource texture que buscamos
    }else if(texture == nullptr && type == 1){
        // Creamos el objeto textura
        texture = new TResourceTexture();
        // Le indicamos si hay que voltear la imagen
        texture->setFlip(flip);
        // Cargamos el archivo de textura con la ruta indicada que nos pasan por parametro
        texture->loadTexture(name);
        // Inicializamos valores de OpenGL
        texture->setupTexture();
        // Seteamos su nombre
        texture->setName(name);
        // Anayadirlo al vector de recursos mediante un push_back
        resources.push_back(texture);

        return texture;

    }else if(json == nullptr && type == 3){

        // Creamos el objeto json
        json = new TResourceJSON();
        // Cargamos el archivo de texto con la ruta indicada que nos pasan por parametro
        json->loadJSON(name);
        // Seteamos su nombre
        json->setName(name);
        // Anayadirlo al vector de recursos mediante un push_back
        resources.push_back(json);

        return json;
    }

    // En caso de que se pase algo que no sea ni texture ni malla se devuelve un nullptr
    return nullptr;
}