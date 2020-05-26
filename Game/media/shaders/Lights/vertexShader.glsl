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

uniform mat4 M;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 TI;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;

void main(){

    // Posición de salida del vértice. En el espacio clip: MVP * position

    //Normal=aColor;

    FragPos = vec3(M*vec4(aPos,1.0));

    Normal = TI*aColor;

    TexCoord = aTexCoord;

    // Al utilizar el FragPos peta
    gl_Position = MVP * vec4(aPos,1);
    
    /*FragPos=vec3()
    ourColor = aColor;*/

   

}
