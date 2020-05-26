#include "hud.h"

//Constructor que crea el hud asignandole un nombre
hud::hud(const char* n) {
	nombre = n;
}

//Destructor que elimina todos los elementos del hud
hud::~hud() {
	//Eliminamos el array de elementos hud
	for (int i = 0; i < elems.size(); i++) {
		delete elems[i];
	}
}

//Funcion para añadir un elemento al hud - se le pasa el ancho, alto, nombre y ruta de imagen del elementoHud
void hud::addElement(const char* n, const char* p) {

	//Creamos un elemento con las caracteristicas deseadas
	elementoHud *e = new elementoHud(n, p);

	//Lo añadimos al array de elementos
	elems.push_back(e);
}
//Funcion para añadir un elemento al hud - se le pasa el ancho, alto, nombre y ruta de imagen del elementoHud
elementoHud *hud::addElementHud(const char* n, const char* p) {
	
	//Lo añadimos al array de elementos
	elems.push_back(new elementoHud(n, p));
	return elems.at(elems.size() - 1);
}

//Funcion para añadir un elemento con color al hud - se le pasa el ancho, alto, nombre y color del elementoHud
void hud::addElement(const char* n, glm::vec4 c) {
	//Creamos un elemento con las caracteristicas deseadas
	elementoHud *e = new elementoHud(n, c);

	//Lo añadimos al array de elementos
	elems.push_back(e);
}
void hud::addElement2(elementoHud *a){
	elems.push_back(a);
}

// Funcion para eleminar un elemento HUD del array
void hud::deleteElement(const char* n) {
	elementoHud *elemento = getElement(n);
	//Lo borramos del array de elementos
	int posicion = getElementPosition(n);
	if(posicion > -1)// -1 Posicion no valida
		elems.erase(elems.begin() + posicion);

}

//Funcion para dibujar el hud
void hud::drawHud(ITShader* shaderHud) {
	//Recorremos el array de elementos, dibujando cada uno de ellos
	for (int i = 0; i < elems.size(); i++) {
		//Llamamos al dibujado de cada elementoHud
		elems.at(i)->draw(shaderHud);
	}
}

//Funcion para trasladar un elemento a partir de su nombre y el punto de traslacion
void hud::traslateElement(const char* n, float x, float y) {
	//Trasladamos el elemento
	getElement(n)->traslacion(x, y);
}

//Funcion para escalar un elemento a partir de su nombre y los indices de escalado
void hud::scaleElement(const char* n, float x, float y) {
	//Escalamos el elemento
	getElement(n)->escalado(x, y);
}

//Funcion para rotar un elemento a partir de su nombre y el angulo de rotacion
void hud::rotateElement(const char* n, float angle) {
	//Rotamos el elemento
	getElement(n)->rotacion(angle);
}

//Funcion para cambiar la textura de un elemento a partir de su nombre y la ruta a la nueva imagen
void hud::changeTextureElement(const char* n, const char* p) {
	//Cambiamos la textura del elemento
	getElement(n)->cambiarTextura(p);
}

//Funcion para cambiar el color de un elemento a partir de su nombre y el nuevo color
void hud::changeColorElement(const char* n, glm::vec4 c) {
	//Cambiamos el color del elemento
	getElement(n)->cambiarColor(c);
}

//Funcion para cambiar la transparencia de un elemento a partir de un booleano y un nivel de transparencia
void hud::changeTransparencyElement(const char* n, bool t, float l) {
	//Cambiamos el color del elemento
	getElement(n)->cambiarTransparencia(t,l);
}

//Funcion que devuelve un elemento a partir de su nombre
elementoHud* hud::getElement(const char* n) {
	elementoHud* e = NULL;
	//Recorremos el array de elementos, buscando el elemento con el nombre especificado
	for (int i = 0; i < elems.size(); i++) {
		if (strcmp(elems.at(i)->getName(), n) == 0) {
			e = elems.at(i);
		}
	}
	return e;
}

//Funcion que devuelve la posicion de un elemento en el array
int hud::getElementPosition(const char* n) {
	//Recorremos el array de elementos, buscando el elemento con el nombre especificado
	for (int i = 0; i < elems.size(); i++) {
		if (strcmp(elems.at(i)->getName(), n) == 0) {
			return i;
		}
	}
	return -1;
}

//Funcion para retornar el nombre
const char* hud::getName() {
	return nombre;
}