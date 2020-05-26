#version 300 es
#undef lowp
#undef mediump
#undef highp

precision mediump float;

//Recoger los datos de los vertices en los buffers correctamente (segun orden de envio en el programa)
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>

out vec2 TexCoords;

//Uniform para la matriz de proyeccion
uniform mat4 projection;
 
void main() {
    //Calculamos la posicion final de cada vertice a partir de la matriz mvp
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);

    TexCoords = vertex.zw;

}
