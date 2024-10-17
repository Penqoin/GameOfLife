#ifndef CLASS_SHADER_HPP
#define CLASS_SHADER_HPP


#include <string>
#include "glm/glm.hpp"

namespace engine
{
    class Shader 
    {
    public:
        unsigned int ID;
        static std::string shaderDir;



        Shader();
        Shader(const std::string vertShader, const std::string fagShader);

        void generate(const std::string& vertShader, const std::string& fragShader);
        unsigned int compileShader(const std::string& filepath, unsigned int type);


        /*
         * SET UNIFORM VARIABLES
         */

        void setBool(const std::string& name, bool value);
        void setInt(const std::string& name, int value);
        void setFloat(const std::string& name, float vlaue);
        void setFloat3(const std::string& name, glm::vec3 pos);
        void setFloat4(const std::string& name, glm::vec4 vect);
        void setMat4(const std::string& name, glm::mat4 mat);

        /* 
         * ACCESSORS
         */
        void activate();
        void cleanup();

    };
}

#endif // !CLASS_SHADER_HPP

