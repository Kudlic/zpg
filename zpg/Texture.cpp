#include "Texture.h"
#include <GL/glew.h>
#include "stb_image.h"

Texture::Texture() {}

Texture::Texture(const char* path, int index) : index(index)
{
    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
   // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
   // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
   // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data)
    {
        glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA, 
            width, 
            height, 
            0, 
            GL_RGBA, 
            GL_UNSIGNED_BYTE, 
            data
        );
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    this->textureID = texture1;

    //Bind the first texture to the first texture unit.\
    
    /*
    glActiveTexture(GL_TEXTURE0);
    this->textureID = SOIL_load_OGL_texture(path, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (this->textureID == 0)
    {
        printf("Popièi cesta k obrázku\n");
    }
    glGenTextures(1, &this->textureID);
    glBindTexture(GL_TEXTURE_2D, this->textureID);

    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, this->textureID);

    glGenerateMipmap(GL_TEXTURE_2D);
    printf("added texture to index: %d\n", index);
    */
}

void Texture::useTexture(ShaderProg* sp) {
    GLint uniformID = sp->getUniformLocation("textureUnitID");
    glUniform1i(uniformID, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->textureID);
}

int Texture::getIndex() {
    return index;
}

