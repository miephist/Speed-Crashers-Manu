#version 300 es
#undef lowp
#undef mediump
#undef highp

precision mediump float;

//NUEVO
/*
#define MaxLights 10

struct Light{
    vec4 color;
    vec3 lightPos;

    float intensity;
    float ambient;
    float attenuation;
};
*/
//END NEW

// Valores de salida
out vec4 FragColor;

//NUEVO
/*
layout(location=0)out vec4 FragColor;
*/
//END

in vec3 ourColor;
in vec2 TexCoord;

//NUEVO
/*
layout(std140) uniform LightBuffer{
    Light lights[MaxLights];
};
uniform int LightAmount;
*/
//END

uniform sampler2D textureDiffuse;
uniform sampler2D textureOclusions;
uniform sampler2D textureSpecular;
uniform sampler2D textureAlpha;

//NEW
/*
vec3 Phong(Light light, vec3 surfaceColor, vec3 specularColor){
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    vec3 dist;

        dist = -light.lightPos.xyz;
    
    
    float d = sqrt(pow(dist.x, 2.0) + pow(dist.y, 2.0) + pow(dist.z, 2.0)); //sacamos la distancia

    //componente Ambiental
    Ambient = light.color.rgb * light.intensity * light.ambient * surfaceColor;//TODO calcular color*intensity en light.cpp
    //componente Difusa
    //TODO calcular difusa
    Diffuse = light.color.rgb *light.intensity * surfaceColor;
    //componente Especular
   
    //TODO specular
    
    
    float attenuation = 1.0 / (1.0 + light.attenuation);
    return Ambient + Diffuse * attenuation;
}
*/
//END

void main(){

    // Color de Salida = color de la textura en las coordenadas UV específicadas
    //old to com
    FragColor = texture(textureSpecular, TexCoord);

    //NEW
    /*
    vec4 specularColor = vec4(1,1,1,1);
    vec4 surfaceColor = texture(textureSpecular, TexCoord);
    vec4 finalColor = vec4(0,0,0,0);
    
    for(int i = 0; i < LightAmount; i++){
        finalColor.rgb = finalColor.rgb + Phong(lights[i], surfaceColor.rgb, specularColor.rgb);
    }
    
    FragColor = finalColor;
    */
    //END
}
