#version 300 es
#undef lowp
#undef mediump
#undef highp

precision mediump float;

#define NUM_LIGHTS 1 

// Valores de salida
out vec4 FragColor;

// Materiales
struct Material {
    vec3 colAmb;
    vec3 colDif;
    vec3 colSpec;

    float shininess;
};

// Luces direccionales
struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    bool creada;
}; 

// Luces puntuales
struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    bool creada;
};  

// Luces focales
struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular; 

    bool creada;      
};


in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;
uniform DirLight[10] dirLights;
uniform PointLight[10] pointLights;
uniform SpotLight[10] spotLights;
uniform Material material;

// Texturas
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D textureDiffuse;
uniform sampler2D textureSpecular;

// Funciones
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);  
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(){

    vec3 result=vec3(0,0,0);

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // Calculamos luces direccionales
    for(int z=0;z<1;z++){
        if(dirLights[z].creada==true){
           result += CalcDirLight(dirLights[z], norm, viewDir);
        }
    }
    // Calculamos luces puntuales
    for(int z=0;z<1;z++){
        if(pointLights[z].creada==true){
            result += CalcPointLight(pointLights[z], norm, FragPos, viewDir);
        }
    }
    
    // Calculamos SpotLight
    for(int z=0;z<4;z++){
        if(spotLights[z].creada==true){
            result += CalcSpotLight(spotLights[z], norm, FragPos, viewDir);
        }
    }

    FragColor = vec4(result, 1.0);
}


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

  //new blinn-Phong
    vec3 halfwayDir=normalize(lightDir + viewDir);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);

    //old spec
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//new spec
    float spec= pow(max(dot(normal,halfwayDir),0.0),material.shininess);
  
    
    // Combine results
    vec3 ambient  = light.ambient  * vec3(texture(textureDiffuse, TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(textureDiffuse, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(textureSpecular, TexCoord));
    return (ambient + diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    //new blinn-Phong
    vec3 halfwayDir=normalize(lightDir + viewDir);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);

    //old spec
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //new spec
    float spec= pow(max(dot(normal,halfwayDir),0.0),material.shininess);
   
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(textureDiffuse, TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(textureDiffuse, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(textureSpecular, TexCoord));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    //if(light.creada){
        vec3 lightDir = normalize(light.position - fragPos);

        //new blinn-Phong
        vec3 halfwayDir=normalize(lightDir + viewDir);

        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        
        //old spec
        //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //new spec
        float spec= pow(max(dot(normal,halfwayDir),0.0),material.shininess);
    
       
        // attenuation
        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
        // spotlight intensity
        float theta = dot(lightDir, normalize(-light.direction)); 
        float epsilon = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
        // combine results
        vec3 ambient = light.ambient * vec3(texture(textureDiffuse, TexCoord));
        vec3 diffuse = light.diffuse * diff * vec3(texture(textureDiffuse, TexCoord));
        vec3 specular = light.specular * spec * vec3(texture(textureSpecular, TexCoord));
        ambient *= attenuation * intensity;
        diffuse *= attenuation * intensity;
        specular *= attenuation * intensity;
        return (ambient + diffuse + specular);
    //}
        //return vec3(0,0,0);
}
