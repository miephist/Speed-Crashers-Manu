#include "TResourceMaterial.h"

#define NAMESPACE mtl_objl
#include <include/OpenGL/OBJ_Loader.h>
//#include <../../include/OpenGL/OBJ_Loader.h>

TResourceMaterial::TResourceMaterial(){

}

TResourceMaterial::~TResourceMaterial(){

}

void TResourceMaterial::loadMaterial(std::string name){

	// Obtenemos toda la ruta hasta el ultimo punto
	std::size_t found = name.find_last_of('.');
	std::string newName = name.substr(0,found);

	// Le anyadimos el tipo de archivo que es
	newName += ".mtl";

	mtl_objl::Loader loader;


	bool isLoaded = loader.LoadMaterials(newName);

	if(isLoaded){
		for(int i=0; i < loader.LoadedMaterials.size(); i++){
			mtl_objl::Material curMaterial = loader.LoadedMaterials[i];

			// Seteamos las propiedades del material
			setAmbient(curMaterial.Ka.X, curMaterial.Ka.Y, curMaterial.Ka.Z);
			setDiffuse(curMaterial.Kd.X, curMaterial.Kd.Y, curMaterial.Kd.Z);
			setSpecular(curMaterial.Ks.X, curMaterial.Ks.Y, curMaterial.Ks.Z);
			setShiny(curMaterial.illum);

		}
	}else{
		std::cout<< "Error cargando el material con ruta: " << name << std::endl;
		return;
	}
}

// Llamar antes del dibujado de la malla
void TResourceMaterial::activeMaterial(){
	
	// Vec3 de colores de los materiales (no se utilizan, utilizamos texturas)
	TEntity::cache.shader->setVec3("material.colAmb", colAmb);
	TEntity::cache.shader->setVec3("material.colDif", colDif);
    TEntity::cache.shader->setVec3("material.colSpec", colSpec);
	
	// Seteamos el brillo del material
	TEntity::cache.shader->setFloat("material.shininess", shiny);
}
//getter del name
const char *TResourceMaterial::getName(){
    return name;
}
//setter del name
void TResourceMaterial::setName(const char *newName){
    name = newName;
}