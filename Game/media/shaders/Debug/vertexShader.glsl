#version 300 es
#undef lowp
#undef mediump
#undef highp

precision mediump float;

//Recoger los datos de los vertices en los buffers correctamente (segun orden de envio en el programa)
layout (location = 0) in vec3 aPos; //Posicion

//Uniform para la matriz mvp
uniform mat4 MVP;
 
void main() {
    //Calculamos la posicion final de cada vertice a partir de la matriz mvp
    gl_Position = MVP * vec4(aPos, 1.0);

}
