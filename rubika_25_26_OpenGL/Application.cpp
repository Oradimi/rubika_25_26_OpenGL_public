#include "Application.h"

void Application::Init()
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

void Application::Update()
{
    // useless for now
}

void Application::Render(Camera& camera)
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

void Application::Destroy()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}