#define GLFW_INCLUDE_NONE

#include "shader.h"

#include <cmath>
#include <cstddef>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <numbers>
#include <vector>

void framebufferSizeCallback(GLFWwindow *, int, int);
void processInputs(GLFWwindow*);
std::vector<GLfloat> generateCircleVertices(float radius, int numOfTriangles);
std::string getAssetPath(std::string);

const int Width = 800;
const int Height = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow *window = glfwCreateWindow(Width, Height, "Triangle", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Could not load GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, Width, Height);

    GLfloat triangleVertices[] = {
         0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    };

    GLfloat quadVertices[] = {
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    };

    auto circleVertices = generateCircleVertices(0.5f, 64);

    GLuint vao[3], vbo[3];
    glGenVertexArrays(3, vao);

    glBindVertexArray(vao[0]);
    glGenBuffers(1, &vbo[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(vao[1]);
    glGenBuffers(1, &vbo[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(vao[2]);
    glGenBuffers(1, &vbo[2]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, circleVertices.size() * sizeof(GLfloat), circleVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    auto vertexShader = createShader(getAssetPath("shaders/shape.vert"), GL_VERTEX_SHADER);
    auto fragmentShader = createShader(getAssetPath("shaders/shape.frag"), GL_FRAGMENT_SHADER);
    auto shader = createShaderProgram({vertexShader, fragmentShader});

    while (!glfwWindowShouldClose(window)) {
        processInputs(window);

        glClearColor(0.3f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao[1]);
        glUseProgram(shader);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(vao[2]);
        glUseProgram(shader);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 64+2);

        glBindVertexArray(vao[0]);
        glUseProgram(shader);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow *window, int w, int h) {
    glViewport(0, 0, w, h);
}

void processInputs(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

std::vector<GLfloat> generateCircleVertices(float radius, int numOfTriangles) {
    std::vector<GLfloat> vertices;

    vertices.insert(vertices.end(), {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f});
    for (int i = 0; i <= numOfTriangles; ++i) {
        const float angle = 2.0f * std::numbers::pi_v<float> * i / numOfTriangles;
        vertices.push_back(radius * std::cos(angle));
        vertices.push_back(radius * std::sin(angle));
        vertices.push_back(0.0f);
        vertices.insert(vertices.end(), {0.0f, 0.0f, 1.0f});
    }

    return vertices;
}

std::string getAssetPath(std::string path) {
    namespace fs = std::filesystem;

    fs::path p = fs::path(ASSETS_DIR) / path;
    return p.string();
}