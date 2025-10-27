#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;

class Texture;

class Material
{
public:
    Material(
        Texture& diffuseTexture,
        Texture& specularTexture,
        const glm::vec3& ambient = glm::vec3(1.f),
        const glm::vec3& diffuse = glm::vec3(1.f),
        const glm::vec3& specular = glm::vec3(1.f),
        float shininess = 1.f
    );

    Material(
        const glm::vec3& ambient,
        const glm::vec3& diffuse,
        const glm::vec3& specular,
        float shininess
    );

    void Use(Shader& shader) const;

private:
    Texture* DiffuseTexture = nullptr;
    Texture* SpecularTexture = nullptr;

    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;
    float Shininess;
};