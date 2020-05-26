#include "TResourceText.h"

TResourceText::TResourceText(std::string t, GLfloat newX, GLfloat newY, GLfloat s, glm::vec3 c, std::string f){

    // Valores por defecto
    parameters = { t, newX, newY, s, c};

    font = f;

    loadFont();
    setupText();

}

TResourceText::~TResourceText(){}


void TResourceText::loadFont(){

    // Conversión de font a const char*
    ruta = new char[font.size() + 1];
    std::copy(font.begin(), font.end(), ruta);
    ruta[font.size()] = '\0';

    if(FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: No se pudo inicializar la libreria de Freetype." << std::endl;

    if(FT_New_Face(ft, ruta, 0, &face))
        std::cout << "ERROR::FREETYPE: Fallo al cargar la fuente." << std::endl;

    // Probar con 48 de altura
    FT_Set_Pixel_Sizes(face, 0, 20.0f);

    if(FT_Load_Char(face, 'X', FT_LOAD_RENDER))
        std::cout << "ERROR::FREETYPE: Fallo al cargar el glifo." << std::endl;
        
}


void TResourceText::setupText(){

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(GLubyte c = 0; c < 128; c++){

        // Cargamos el caracter del glifo
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)){
            std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
            continue;
        }

        // Generamos las textures    
        GLuint texture;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 
        face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, 
        GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        // Opciones de las texturas
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Guardamos el caracter para un uso posterior
        Character character = {texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), (GLuint)face->glyph->advance.x};

        Characters.insert(std::pair<GLchar, Character> (c, character));
    }

    // Destruimos Freetype una vez hemos acabado
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // Configuramos los buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void TResourceText::draw(ITShader* shader){

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

    glUseProgram(shader->getShader()->getID());
    shader->getShader()->setMat4("projection", glm::ortho(0.0f, 800.0f, 0.0f, 600.0f));
    shader->getShader()->setVec3("textColor", parameters.color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    GLfloat aux = parameters.x;

    int i = 0;

    for(c = parameters.text.begin(); c != parameters.text.end(); c++){

        Character ch = Characters[*c];

        GLfloat xpos = aux + ch.Bearing.x * parameters.scale;
        GLfloat ypos = parameters.y - (ch.Size.y - ch.Bearing.y) * parameters.scale;

        GLfloat w = ch.Size.x * parameters.scale;
        GLfloat h = ch.Size.y * parameters.scale;

        GLfloat vertices[6][4] = {
            {xpos,      ypos + h,       0.0, 0.0},
            {xpos,      ypos,           0.0, 1.0},
            {xpos + w,  ypos,           1.0, 1.0},

            {xpos,      ypos + h,       0.0, 0.0},
            {xpos + w,  ypos,           1.0, 1.0},
            {xpos + w,  ypos + h,       1.0, 0.0}
        };

        glBindTexture(GL_TEXTURE_2D, ch.textID);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        aux += (ch.Advance >> 6) * parameters.scale;
    }

    
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
}

const char *TResourceText::getName(){
    return name;
}

void TResourceText::setName(const char *newName){
    name = newName;
}
