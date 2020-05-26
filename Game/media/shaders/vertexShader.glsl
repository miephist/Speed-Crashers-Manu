#version 300 es
#undef lowp
#undef mediump
#undef highp

precision mediump float;

// Información de entrada de los vértices. Es diferente para cada una de las ejecuciones de este shader.
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

// Valores que permanecen constantes para toda la malla. .
uniform mat4 MVP;
out vec3 ourColor;
out vec2 TexCoord;

void main(){

    // Posición de salida del vértice. En el espacio clip: MVP * position
    gl_Position =  MVP * vec4(aPos,1);

    ourColor = aColor;

    TexCoord = aTexCoord;

}
