#include "engine/graphics/rendering/Texture.hpp"
#include <GL/gl.h>
#include <filesystem>
#include <iostream>

std::string engine::Texture::defaultTextureDirectory = "./assets/textures/";

engine::Texture::Texture(const std::string& name) : m_name(name) 
{
    generate();
};
engine::Texture::Texture(const std::string& name, const std::string& filepath) : m_name(name) 
{
    generate();
};

void engine::Texture::generate()
{
    glGenTextures(1, &ID);
}

void engine::Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void engine::Texture::cleanup()
{
    glDeleteTextures(1, &ID);
}

void engine::Texture::load(bool flip)
{
    stbi_set_flip_vertically_on_load(flip);

    int width, height, nrChannels;
    unsigned char* data = stbi_load((defaultTextureDirectory + m_name).c_str(), &width, &height, &nrChannels, 0);
       std::cout << std::filesystem::current_path() << std::endl;

    GLenum colorMode = GL_RGB;
    switch (nrChannels)
    {
        case 1:
            colorMode = GL_RED;
            break;
        case 4:
            colorMode = GL_RGBA;
            break;
    }

    if (data == nullptr)
    {
        std::cout << "FAILED TO LOAD IMAGE AT: " << (defaultTextureDirectory + m_name).c_str() << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
}
