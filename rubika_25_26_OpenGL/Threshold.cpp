#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Light.h"
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
        // Pos - Normal
        { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f },
        {  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f },
        {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f },
        {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f },
        { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f },
        { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f },

        { -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
        {  0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
        {  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
        {  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
        { -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
        { -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },

        { -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f },
        { -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f },
        { -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f },
        { -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f },
        { -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f },
        { -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f },

        { 0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f },
        { 0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f },
        { 0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f },
        { 0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f },
        { 0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f },
        { 0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f },

        { -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f },
        {  0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f },
        {  0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 1.0f },
        {  0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 1.0f },
        { -0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f },
        { -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f },

        { -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f },
        {  0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f },
        {  0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f },
        {  0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f },
        { -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 0.0f, 1.0f },
        { -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f }
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(1.0f,  1.0f, -1.0f),
    };

    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
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

        //glGenBuffers(1, &ebo);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexCount * sizeof(Vertex), indices, GL_STATIC_DRAW);

        static constexpr GLuint vertex_attr_position = 0;
        static constexpr GLuint vertex_attr_color = 1;
        static constexpr GLuint vertex_attr_texCoord = 2;
        static constexpr GLuint vertex_attr_normal = 3;
        glEnableVertexAttribArray(vertex_attr_position);
        glEnableVertexAttribArray(vertex_attr_color);
        glEnableVertexAttribArray(vertex_attr_texCoord);
        glEnableVertexAttribArray(vertex_attr_normal);

        glVertexAttribPointer(vertex_attr_position, 3, GL_FLOAT, GL_FALSE,
            sizeof(Vertex),
            (const GLvoid*)offsetof(Vertex, position));
        glVertexAttribPointer(vertex_attr_normal, 3, GL_FLOAT, GL_FALSE,
            sizeof(Vertex),
            (const GLvoid*)offsetof(Vertex, normal));
        //glVertexAttribPointer(vertex_attr_color, 3, GL_FLOAT, GL_FALSE,
        //    sizeof(Vertex),
        //    (const GLvoid*)offsetof(Vertex, color));
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
            //modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f), glm::vec3(0.0, 1.0, 0.0));

            modelMatrix = glm::translate(modelMatrix, cubePosition);
            //modelMatrix = glm::rotate(modelMatrix, time * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            
            if (lightPass) {
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
            }
            
            //modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f) * std::sinf(time / 10.0), glm::vec3(0.0, 0.0, 1.0));
            //modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0) * std::sinf(time / 10.0));
            //GLint location = glGetUniformLocation(shader.Get(), "ambiantLightColor");
            //glUniform3f(location, 1.0f, 0.1f, 0.1f);

            //location = glGetUniformLocation(shader.Get(), "ambiantLightIntensity");
            //glUniform1f(location, std::abs(std::sinf(time)));

            //location = glGetUniformLocation(shader.Get(), "lightColor");
            //glUniform3f(location, lightColor.x, lightColor.y, lightColor.z);

            GLint location = glGetUniformLocation(shader.Get(), "viewPos");
            glUniform3f(location, camera.Pos().x, camera.Pos().y, camera.Pos().z);

            textureDiffuse.Use(shader.Get(), "textureDiffuse", 0);
            textureSpecular.Use(shader.Get(), "textureSpecular", 1);

            container2.Use(shader);
            light.Use(shader);

            //location = glGetUniformLocation(shader.Get(), "uShininess");
            //glUniform1f(location, 200.f);

            shader.SetFloat("time", std::abs(std::sinf(time)));
            shader.SetMatrix("uMVPMatrix", projMatrix * viewMatrix * modelMatrix);
            shader.SetMatrix("uModelMatrix", modelMatrix);
            shader.Use();
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, vertexCount);
            //glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, NULL);
            glBindVertexArray(0);
        }
    }

    void destroy()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
    }
}