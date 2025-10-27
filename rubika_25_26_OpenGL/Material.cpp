#include "Shader.h"
#include "Texture.h"
#include "Material.h"

Material::Material(
    Texture& diffuseTexture,
    Texture& specularTexture,
    const glm::vec3& ambient,
    const glm::vec3& diffuse,
    const glm::vec3& specular,
    float shininess
) : DiffuseTexture(&diffuseTexture), SpecularTexture(&specularTexture),
Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(shininess)
{

}

Material::Material(
    const glm::vec3& ambient,
    const glm::vec3& diffuse,
    const glm::vec3& specular,
    float shininess
) : Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(shininess)
{

}

void Material::Use(Shader& shader) const
{
    GLint location = glGetUniformLocation(shader.Get(), "material.ambient");
    glUniform3f(location, Ambient.x, Ambient.y, Ambient.z);
    location = glGetUniformLocation(shader.Get(), "material.diffuse");
    glUniform3f(location, Diffuse.x, Diffuse.y, Diffuse.z);
    location = glGetUniformLocation(shader.Get(), "material.specular");
    glUniform3f(location, Specular.x, Specular.y, Specular.z);
    location = glGetUniformLocation(shader.Get(), "material.shininess");
    glUniform1f(location, Shininess);
}