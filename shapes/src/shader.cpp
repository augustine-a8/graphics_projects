#include "shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::string fileToString(const std::string &filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) return "";

    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

void shaderCompileStatus(GLuint shader, GLenum shaderType) {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        switch (shaderType) {
            case GL_VERTEX_SHADER: {
                std::cout << "Vertex Shader Compilation Error\n";
                break;
            }
            case GL_FRAGMENT_SHADER: {
                std::cout << "Fragment Shader Compilation Error\n";
            }
            default: break;
        }
        std::cout << infoLog << std::endl;
    }
}

GLuint createShader(const std::string &shaderPath, GLenum shaderType) {
    auto shaderFileContents = fileToString(shaderPath);
    if (shaderFileContents == "") return 0;

    const char* shaderSource = shaderFileContents.c_str();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    shaderCompileStatus(shader, shaderType);
    return shader;
}

GLuint createShaderProgram(std::initializer_list<GLuint> shaders) {
    GLuint shaderProgram = glCreateProgram();
    for (const auto &shader : shaders) {
        glAttachShader(shaderProgram, shader);
    }
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "Shader Program Linking Failed\n" << infoLog << std::endl;
    }

    return shaderProgram;
}