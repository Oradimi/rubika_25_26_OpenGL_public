#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader();
    ~Shader();

    // Read both file to init the vertex shader and the fragment shader
    bool Init(const char* vertexPath, const char* fragmentPath);

    // Use the corresponding program
    void Use();

    GLuint Get();

    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetMatrix(const std::string& name, glm::mat4 value) const;

private:
    GLuint ProgramID;
};