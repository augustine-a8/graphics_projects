#pragma once

#include <glad/glad.h>
#include <string>

std::string fileToString(const std::string &filepath);

void shaderCompileStatus(GLuint shader, GLenum shaderType);

GLuint createShader(const std::string &shaderPath, GLenum shaderType);

GLuint createShaderProgram(std::initializer_list<GLuint> shaders);