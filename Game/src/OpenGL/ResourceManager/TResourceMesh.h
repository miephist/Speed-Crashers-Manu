#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TResource.h"
#include "TResourceMaterial.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//informacion vertices
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};
//informacion textura
struct Texture {
    unsigned int id;
    std::string type;
    std::string path;  
}; 

class TResourceMesh : public TResource{

    private:

        Assimp::Importer imp;
        std::string directory;
        int id;
        const char* nickname;

        TResourceMaterial *material;

    public:
        // Constructor y destructor
        TResourceMesh();
        ~TResourceMesh();

        void setupMesh();

        /*  Render   */
        unsigned int VAO, VBO, EBO;
        
        /*  Mesh   */
        //struct
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        /*  Funciones */
        // Tratamiento de mallas
        void loadMesh(std::string file);
        void processNode(aiNode *node, const aiScene *scene);
        void processMaterial(aiMesh *mesh, const aiScene *scene);

        void processMesh(aiMesh *mesh, const aiScene *scene);
        // Inheritance methods
        // Override: https://stackoverflow.com/questions/18198314/what-is-the-override-keyword-in-c-used-for
        
        //getters
        int getID();
        const char *getName() override;
        const char *getNickname();
        TResourceMaterial* getMaterial()    {return material;};

        //setters
        void setID(int newId);
        void setName(const char *newName) override;
        void setNickname(const char *newNick);

};