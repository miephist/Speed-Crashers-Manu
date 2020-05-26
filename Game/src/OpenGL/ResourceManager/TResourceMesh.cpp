#include "TResourceMesh.h"
#include "TResourceMaterial.h"

TResourceMesh::TResourceMesh(){
    // Inicializamos el material
    material = new TResourceMaterial();
}

TResourceMesh::~TResourceMesh(){
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    delete nickname;
    delete material;

}

void TResourceMesh::loadMesh(std::string file){
    const aiScene* scene = imp.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout<< "Error: " << imp.GetErrorString() << std::endl;
        return;
    }

    directory = file.substr(0, file.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void TResourceMesh::processNode(aiNode *node, const aiScene *scene){

    //procesado de los nodos de la malla en caso de haber
    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        
        processMesh(mesh,scene);
        
    }

    // hacer lo mismo para hijos
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    } 
}

void TResourceMesh::processMesh(aiMesh *mesh, const aiScene *scene){
   
        
    for(unsigned int i = 0; i < mesh->mNumVertices; i++){
        Vertex vertex;
        // procesa vertices de posicion, normales y coordenadas de textura

        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z; 
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector; 

        if(mesh->mTextureCoords[0]){ // Comprueba si tiene coordenadas de textura
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else{
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);  
        }

        vertices.push_back(vertex);
    }

    // procesa indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++){
            indices.push_back(face.mIndices[j]);
        }
    }  
}  


void TResourceMesh::processMaterial(aiMesh *mesh, const aiScene *scene) {
	TResourceMaterial *recMat = NULL;
	int numMaterials = scene->mNumMaterials - 1;
	
	// Comprobamos que haya materiales
	if (mesh->mMaterialIndex >= 0) {// solo cuando no haya nada para comprobar
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];//recogemos el material

	}
}

void TResourceMesh::setupMesh(){ 
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
                    &indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);	
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);	        
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
}

const char *TResourceMesh::getName(){
    return name;
}

int TResourceMesh::getID(){
    return id;
}

const char *TResourceMesh::getNickname(){
    return nickname;
}

void TResourceMesh::setID(int newId){
    id = newId;
}

void TResourceMesh::setName(const char *newName){
    name = newName;
}

void TResourceMesh::setNickname(const char *newNick){
    nickname = newNick;
}
// https://learnopengl.com/Model-Loading/Mesh