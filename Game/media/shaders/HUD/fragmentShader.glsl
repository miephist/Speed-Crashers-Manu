#version 300 es
#undef lowp
#undef mediump
#undef highp

precision mediump float;

// Valores de salida
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D textureDiffuse;
uniform sampler2D textureOclusions;
uniform sampler2D textureSpecular;
uniform sampler2D textureAlpha;

// HUD
uniform float transparencyLevel;
uniform bool transparency;

void main(){

    // Color de Salida = color de la textura en las coordenadas UV específicadas
    if(transparency == true){
        if(texture(textureSpecular, TexCoord).w > 0.0){
            FragColor = vec4(vec3(texture(textureSpecular, TexCoord)), transparencyLevel);
        }else{
            discard;
        }
    }else{
        if(texture(textureSpecular, TexCoord).w > 0.0){
            FragColor = texture(textureSpecular, TexCoord);
        }else{
            discard;
        }
    }  
}
