#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Light.h"
#include "Vertex.h"
#include "Camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

class Application {
private:
    GLuint vbo{};
    GLuint vao{};
    GLuint ebo{};

    static constexpr Vertex vertices[] = {
        // Front face (Z+)
        {{-0.5f, -0.5f,  0.5f}, {0.0f,  0.0f,  1.0f}, {1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}}, // 0
        {{0.5f, -0.5f,  0.5f},  {0.0f,  0.0f,  1.0f}, {1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}}, // 1
        {{0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f}, {1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}}, // 2
        {{-0.5f,  0.5f,  0.5f}, {0.0f,  0.0f,  1.0f}, {1.0f,  1.0f,  1.0f}, {0.0f, 1.0f}}, // 3

        // Back face (Z-)
        {{-0.5f, -0.5f, -0.5f}, {0.0f,  0.0f, -1.0f}, {1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}}, // 4
        {{0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f}, {1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}}, // 5
        {{0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f}, {1.0f,  1.0f,  1.0f}, {0.0f, 1.0f}}, // 6
        {{-0.5f,  0.5f, -0.5f}, {0.0f,  0.0f, -1.0f}, {1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}}, // 7

        // Left face (X-)
        {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}}, // 8
        {{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}}, // 9
        {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}}, // 10
        {{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f,  1.0f,  1.0f}, {0.0f, 1.0f}}, // 11

        // Right face (X+)
        {{0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f}, {1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}}, // 12
        {{0.5f, -0.5f,  0.5f},  {1.0f,  0.0f,  0.0f}, {1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}}, // 13
        {{0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f}, {1.0f,  1.0f,  1.0f}, {0.0f, 1.0f}}, // 14
        {{0.5f,  0.5f, -0.5f},  {1.0f,  0.0f,  0.0f}, {1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}}, // 15

        // Bottom face (Y-)
        {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f,  0.0f}, {1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}}, // 16
        {{0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f}, {1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}}, // 17
        {{0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f}, {1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}}, // 18
        {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f,  0.0f}, {1.0f,  1.0f,  1.0f}, {0.0f, 1.0f}}, // 19

        // Top face (Y+)
        {{-0.5f,  0.5f, -0.5f}, {0.0f,  1.0f,  0.0f}, {1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}}, // 20
        {{0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f}, {1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}}, // 21
        {{0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f}, {1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}}, // 22
        {{-0.5f,  0.5f,  0.5f}, {0.0f,  1.0f,  0.0f}, {1.0f,  1.0f,  1.0f}, {0.0f, 1.0f}}, // 23
    };

    static constexpr glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    static constexpr unsigned int indices[] = {
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Back face
        4, 5, 6,
        6, 7, 4,

        // Left face
        8, 9, 10,
        10, 11, 8,

        // Right face
        12, 13, 14,
        14, 15, 12,

        // Bottom face
        16, 17, 18,
        18, 19, 16,

        // Top face
        20, 21, 22,
        22, 23, 20
    };

    const int vertexCount = 36;

    GLFWwindow* window = nullptr;

    Camera camera;
    Shader shader;
    Texture textureDiffuse;
    Texture textureSpecular;

    Material container2{ textureDiffuse, textureSpecular };

    Material greenPlastic{ glm::vec3(0.f), glm::vec3(0.1f, 0.35f, 0.1f), glm::vec3(0.45f, 0.55f, 0.45f), 0.25f };
    Material cyanPlastic{ glm::vec3(0.f, 0.1f, 0.06f), glm::vec3(0.0f, 0.50980392f, 0.50980392f), glm::vec3(0.50196078f, 0.50196078f, 0.50196078f), 0.25f };
    Material pearl{ glm::vec3(0.25f, 0.20725f, 0.20725f), glm::vec3(1.0f, 0.829f, 0.829f), glm::vec3(0.296648f, 0.296648f, 0.296648f), 0.088f };

    Light light{ glm::vec3(1.0f, 1.0f, -5.0f),
        glm::vec3(1.f), 0.4f,
        glm::vec3(1.f), 2.0f,
        glm::vec3(1.f), 1.0f
    };

    const char* vertexPath = "./Resources/vertexShader.glsl";
    const char* fragmentPath = "./Resources/fragmentShader.glsl";

    glm::vec3 lightColor{ 1.0f, 1.0f, 1.0f };

    float startTime = glfwGetTime();
    float deltaTime = 1.f / 30.f;

    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    float lastXPos = -9999999.f;
    float lastYPos = -9999999.f;

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

public:
    Application() = default;
    ~Application() = default;
    bool IsRunning();
    int Setup();
    void Init();
    void Input();
    void Update();
    void Render();
    void Destroy();
};