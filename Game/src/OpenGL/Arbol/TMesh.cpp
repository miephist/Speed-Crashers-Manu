#include "TMesh.h"

TMesh::TMesh(TResourceMesh* m, TResourceTexture* t) : TEntity() {
    
    mesh = m;
    texture = t;
    material = mesh->getMaterial();


    // Generamos los buffers
    glGenBuffers(1, &textureID);
    glBindBuffer(GL_UNIFORM_BUFFER, textureID);
    glBindBufferBase(GL_UNIFORM_BUFFER, 3, textureID);

}

TMesh::~TMesh(){
    delete mesh;
    delete texture;
    delete material;
}

void TMesh::beginDraw(int pasada){

    if(pasada==2){
        
        // Obtenemos las matrices de vista y proyeccion mediante la camara actual almacenada en la cache
        glm::mat4 projectionMatrix = TEntity::cache.camera->getProjectionMatrix();
        glm::mat4 viewMatrix = TEntity::cache.camera->getViewMatrix();
        // Obtenemos la matriz modelo mediante la matriz estatica de la cache
        glm::mat4 modelMatrix = TEntity::cache.mpila.top();

        //enviar matriz modelo al shader
        glm::mat4 modelViewProjection = projectionMatrix * viewMatrix * modelMatrix;
        
        glUniformMatrix4fv(TEntity::cache.shader->modelViewProjectionMatrixId, 1, GL_FALSE, &modelViewProjection[0][0]);
        glUniformMatrix4fv(TEntity::cache.shader->modelMatrixId,1,GL_FALSE, &modelMatrix[0][0]);

        glm::mat3 transinv = glm::transpose(glm::inverse(modelMatrix));
        glUniformMatrix3fv(TEntity::cache.shader->TransInvMatrixId,1,GL_FALSE, &transinv[0][0]);

        glBindBuffer(GL_UNIFORM_BUFFER, textureID);
        glBindBufferBase(GL_UNIFORM_BUFFER, 3, textureID);

        int loadedTextures = 0;   

        glActiveTexture(GL_TEXTURE0 + loadedTextures);
        glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
        TEntity::cache.shader->setInt("textureDiffuse", loadedTextures);
        loadedTextures++;

        glActiveTexture(GL_TEXTURE0 + loadedTextures);
        glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
        TEntity::cache.shader->setInt("textureSpecular", loadedTextures);
        loadedTextures++;

        glActiveTexture(GL_TEXTURE0 + loadedTextures);
        glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
        loadedTextures++;

        glActiveTexture(GL_TEXTURE0 + loadedTextures);
        glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
        loadedTextures++;

        // Activamos materiales modelado
        material->activeMaterial();

        glBindVertexArray(mesh->VAO);
        glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

    }

}


void TMesh::endDraw(int pasada){

    if(pasada==2){
        // Free textures off the buffers.
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, 0);

    }

}


