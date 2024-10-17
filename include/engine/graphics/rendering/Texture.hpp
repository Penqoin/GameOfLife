#ifndef CLASS_TEXTURES_HPP
#define CLASS_TEXTURES_HPP

#include <stb/stb_image.h>
#include "glad/glad.h"
#include <cstdint>
#include <string>

namespace engine
{
    class Texture 
    {
    public:
        uint32_t ID;

        Texture(const std::string& name);
        Texture(const std::string& name, const std::string& textureFilePath);

        void generate();
        void load(bool flip = true);
        void bind();
        void cleanup();

    private:

        std::string m_name;
        static std::string defaultTextureDirectory;

    };
};

#endif // !CLASS_TEXTURES_HPP
