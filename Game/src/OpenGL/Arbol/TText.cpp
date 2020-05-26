#include "TText.h"

TText::TText(TResourceText* t, TShaderProgram* s) : TEntity() {
    
    text = t;
    shader = s;

}

TText::~TText(){
    delete text;
}

void TText::beginDraw(int pasada){

    if(pasada == 2){

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

        glUseProgram(shader->getID());
        shader->setMat4("projection", glm::ortho(0.0f, 800.0f, 0.0f, 600.0f));
        shader->setVec3("textColor", text->getParameters().color);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(text->getVAO());


        GLfloat suma = text->getParameters().x;
        std::map<GLchar, Character> Characters = text->getMap();
        std::string::const_iterator c;

        int i = 0;

        for(c = text->getParameters().text.begin(); c != text->getParameters().text.end() && i <= text->getParameters().text.capacity(); c++){
            
            if(i <= text->getParameters().text.capacity()){
    
                Character ch = Characters[*c];

                GLfloat xpos = suma + ch.Bearing.x * text->getParameters().scale;
                GLfloat ypos = text->getParameters().y - (ch.Size.y - ch.Bearing.y) * text->getParameters().scale;

                GLfloat w = ch.Size.x * text->getParameters().scale;
                GLfloat h = ch.Size.y * text->getParameters().scale;

                GLfloat vertices[6][4] = {
                    {xpos,      ypos + h,       0.0, 0.0},
                    {xpos,      ypos,           0.0, 1.0},
                    {xpos + w,  ypos,           1.0, 1.0},

                    {xpos,      ypos + h,       0.0, 0.0},
                    {xpos + w,  ypos,           1.0, 1.0},
                    {xpos + w,  ypos + h,       1.0, 0.0}
                };

                glBindTexture(GL_TEXTURE_2D, ch.textID);

                glBindBuffer(GL_ARRAY_BUFFER, text->getVBO());
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                glDrawArrays(GL_TRIANGLES, 0, 6);

                suma += (ch.Advance >> 6) * text->getParameters().scale;

                i++;

            }
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glDisable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

    }
    
}


void TText::endDraw(int pasada){


}


