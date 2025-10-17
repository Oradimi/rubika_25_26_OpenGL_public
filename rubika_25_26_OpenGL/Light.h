#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;

class Light
{
public:
    Light(); // white light at 0.0.0
    Light(
        const glm::vec3& position,
        const glm::vec3& ambient,
        float ambientIntensity,
        const glm::vec3& diffuse,
        float diffuseIntensity,
        const glm::vec3& scalar,
        float scalarIntensity
    );

    void Use(Shader& shader);

private:
    glm::vec3 Position;
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Scalar;
};