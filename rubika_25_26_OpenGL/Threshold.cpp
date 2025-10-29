#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Light.h"
#include "Vertex.h"
#include "Threshold.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

namespace threshold
{
    GLuint vbo{};
    GLuint vao{};
    GLuint ebo{};
    Vertex vertices[] = {
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

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(1.0f,  1.0f, -1.0f),
    };

    unsigned int indices[] = {
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

    Shader shader;
    Texture textureDiffuse;
    Texture textureSpecular;

    Material container2{ textureDiffuse, textureSpecular };

    Material greenPlastic{ glm::vec3(0.f), glm::vec3(0.1f, 0.35f, 0.1f), glm::vec3(0.45f, 0.55f, 0.45f), 0.25f };
    Material cyanPlastic{ glm::vec3(0.f, 0.1f, 0.06f), glm::vec3(0.0f, 0.50980392f, 0.50980392f), glm::vec3(0.50196078f, 0.50196078f, 0.50196078f), 0.25f };
    Material pearl{ glm::vec3(0.25f, 0.20725f, 0.20725f), glm::vec3(1.0f, 0.829f, 0.829f), glm::vec3(0.296648f, 0.296648f, 0.296648f), 0.088f };

    Light light{ glm::vec3(1.0f, 1.0f, -1.0f),
        glm::vec3(1.f), 0.2f,
        glm::vec3(1.f), 3.0f,
        glm::vec3(1.f), 1.0f
    };

    const char* vertexPath = "./Resources/vertexShader.glsl";
    const char* fragmentPath = "./Resources/fragmentShader.glsl";

    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

    void init()
    {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexCount * sizeof(Vertex), indices, GL_STATIC_DRAW);

        static constexpr GLuint vertex_attr_position = 0;
        static constexpr GLuint vertex_attr_normal = 1;
        static constexpr GLuint vertex_attr_color = 2;
        static constexpr GLuint vertex_attr_texCoord = 3;
        glEnableVertexAttribArray(vertex_attr_position);
        glEnableVertexAttribArray(vertex_attr_normal);
        glEnableVertexAttribArray(vertex_attr_color);
        glEnableVertexAttribArray(vertex_attr_texCoord);

        glVertexAttribPointer(vertex_attr_position, 3, GL_FLOAT, GL_FALSE,
            sizeof(Vertex),
            (const GLvoid*)offsetof(Vertex, position));
        glVertexAttribPointer(vertex_attr_normal, 3, GL_FLOAT, GL_FALSE,
            sizeof(Vertex),
            (const GLvoid*)offsetof(Vertex, normal));
        glVertexAttribPointer(vertex_attr_color, 3, GL_FLOAT, GL_FALSE,
            sizeof(Vertex),
            (const GLvoid*)offsetof(Vertex, color));
        glVertexAttribPointer(vertex_attr_texCoord, 2, GL_FLOAT, GL_FALSE,
            sizeof(Vertex),
            (const GLvoid*)offsetof(Vertex, texCoord));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        shader.Init(vertexPath, fragmentPath);
        textureDiffuse.Init("../Resources/container2_diffuse.png");
        textureSpecular.Init("../Resources/container2_specular.png");

        glEnable(GL_DEPTH_TEST);
        glCullFace(GL_BACK);
    }

    void update()
    {
        // useless for now
    }

    void draw(Camera& camera)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time = glfwGetTime();

        bool lightPass = true;

        for (auto& cubePosition : cubePositions) {
            lightPass = !lightPass;
            glm::mat4 viewMatrix = camera.GetMatrix();
            glm::mat4 projMatrix =
                glm::perspective(glm::radians(camera.GetFov()), 4.f / 3.f, 0.1f, 100.f);
            glm::mat4 modelMatrix = glm::mat4(1.f);

            modelMatrix = glm::translate(modelMatrix, cubePosition);
            
            if (lightPass) {
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
            }

            GLint location = glGetUniformLocation(shader.Get(), "viewPos");
            glUniform3f(location, camera.Pos().x, camera.Pos().y, camera.Pos().z);

            textureDiffuse.Use(shader.Get(), "textureDiffuse", 0);
            textureSpecular.Use(shader.Get(), "textureSpecular", 1);

            container2.Use(shader);
            light.Use(shader);

            shader.SetFloat("time", std::abs(std::sinf(time)));
            shader.SetMatrix("uMVPMatrix", projMatrix * viewMatrix * modelMatrix);
            shader.SetMatrix("uModelMatrix", modelMatrix);
            shader.Use();
            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, NULL);
            glBindVertexArray(0);
        }
    }

    void destroy()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
    }
}