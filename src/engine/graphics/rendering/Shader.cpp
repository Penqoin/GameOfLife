#include "engine/graphics/rendering/Shader.hpp"
#include "glad//glad.h"
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>

#include "engine/macros/fileMacros.hpp"

std::string engine::Shader::shaderDir = "/shaders/";

const char* getShaderContents(const std::string& shaderPath)
{
    FILE* shaderFile = nullptr;
    shaderFile = fopen((CMAKE_RENDERING_DIR+ shaderPath).c_str(), "rb");

    if (!shaderFile)
    {
        std::cout << "SYSTEM: Failed to open: " + shaderPath << std::endl;
        return nullptr;
    }

    fseek(shaderFile, 0L, SEEK_END);
    int len = ftell(shaderFile);
    fseek(shaderFile, 0, SEEK_SET);

    char* ret = nullptr;
    int cursor = 0;
    ret = (char*)malloc(len + 1);

    fread(ret + cursor, 1, len, shaderFile);
    ret[cursor + len] = 0;
    return ret;
}


engine::Shader::Shader() {}

engine::Shader::Shader(std::string vertShader, std::string fragShader)
{
    generate(vertShader, fragShader);
}

void engine::Shader::generate(const std::string& vertFilePath, const std::string& fragFilePath)
{
    unsigned int vertID = compileShader(vertFilePath, GL_VERTEX_SHADER);
    unsigned int fragID = compileShader(fragFilePath, GL_FRAGMENT_SHADER);

    ID = glCreateProgram();
    glAttachShader(ID, vertID);
    glAttachShader(ID, fragID);
    glLinkProgram(ID);

    int success;
    char infoLog[512];
    glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(ID, 512, NULL, infoLog);
        std::cout << "SYSTEM: shader compilation error: update" << infoLog << std::endl;;
        throw std::runtime_error("");
    } 

    glDeleteShader(vertID);
    glDeleteShader(fragID);
}

unsigned int engine::Shader::compileShader(const std::string& shaderPath, GLenum type)
{
    unsigned int ID = glCreateShader(type);
    const char* shader = getShaderContents(shaderDir + shaderPath);
    glShaderSource(ID, 1, &shader, NULL);
    glCompileShader(ID);

    int success;
    char infoLog[512];
    glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(ID, 512, NULL, infoLog);
        std::cout << shaderPath << std::endl;
        std::cout << "SYSTEM: shader compilation error: \n" << infoLog << std::endl;
        throw std::runtime_error("");
    }
    
    return ID;
}

void engine::Shader::activate()
{
    glUseProgram(ID);
}

void engine::Shader::setInt(const std::string& name, int val)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), val);
}

void engine::Shader::setFloat(const std::string& name, float val)
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), val);
}

void engine::Shader::setFloat3(const std::string& name, glm::vec3 pos)
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), pos.x, pos.y, pos.z);
}

void engine::Shader::setFloat4(const std::string& name, glm::vec4 vect)
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), vect.x, vect.y, vect.z, vect.w);
}

void engine::Shader::setMat4(const std::string& name, glm::mat4 mat)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
