#include "Application.h"
#include <iostream>

// Public methods

bool Application::IsRunning() {
    startTime = glfwGetTime();
    return !glfwWindowShouldClose(window);
}

int Application::Setup() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Rubika OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int width, int height) {
        static_cast<Application*>(glfwGetWindowUserPointer(w))->framebuffer_size_callback(w, width, height);
    });
    glfwSetCursorPosCallback(window, [](GLFWwindow* w, double xpos, double ypos) {
        static_cast<Application*>(glfwGetWindowUserPointer(w))->mouse_callback(w, xpos, ypos);
    });
    glfwSetScrollCallback(window, [](GLFWwindow* w, double xoffset, double yoffset) {
        static_cast<Application*>(glfwGetWindowUserPointer(w))->scroll_callback(w, xoffset, yoffset);
    });


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 0;
}

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

void Application::Input()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(Camera::Direction::Forward, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(Camera::Direction::Left, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(Camera::Direction::Backward, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(Camera::Direction::Right, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(Camera::Direction::Up, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(Camera::Direction::Down, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(GLFW_KEY_LEFT_SHIFT, GLFW_PRESS, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        camera.ProcessKeyboard(GLFW_KEY_LEFT_SHIFT, GLFW_RELEASE, deltaTime);
    }
}

void Application::Update()
{
    // useless for now
}

void Application::Render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float time = glfwGetTime();

    for (auto& cubePosition : cubePositions) {
        glm::mat4 viewMatrix = camera.GetMatrix();
        glm::mat4 projMatrix =
            glm::perspective(glm::radians(camera.GetFov()), 4.f / 3.f, 0.1f, 100.f);
        glm::mat4 modelMatrix = glm::mat4(1.f);

        modelMatrix = glm::translate(modelMatrix, cubePosition);
        modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

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

    glfwSwapBuffers(window);
    glfwPollEvents();

    deltaTime = glfwGetTime() - startTime;
}

void Application::Destroy()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
}

// Private methods

void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Application::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (lastXPos < -9999998.f || lastYPos < -9999998.f) {
        lastXPos = xpos;
        lastYPos = ypos;
    }

    camera.ProcessMouse(xpos - lastXPos, ypos - lastYPos);
    lastXPos = xpos;
    lastYPos = ypos;
}

void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}