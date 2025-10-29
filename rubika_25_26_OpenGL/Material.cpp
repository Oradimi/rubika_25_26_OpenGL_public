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
) : _diffuseTexture(&diffuseTexture), _specularTexture(&specularTexture),
_ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess)
{

}

Material::Material(
    const glm::vec3& ambient,
    const glm::vec3& diffuse,
    const glm::vec3& specular,
    float shininess
) : _ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess)
{

}

void Material::Use(Shader& shader) const
{
    GLint location = glGetUniformLocation(shader.Get(), "material.ambient");
    glUniform3f(location, _ambient.x, _ambient.y, _ambient.z);
    location = glGetUniformLocation(shader.Get(), "material.diffuse");
    glUniform3f(location, _diffuse.x, _diffuse.y, _diffuse.z);
    location = glGetUniformLocation(shader.Get(), "material.specular");
    glUniform3f(location, _specular.x, _specular.y, _specular.z);
    location = glGetUniformLocation(shader.Get(), "material.shininess");
    glUniform1f(location, _shininess);
}