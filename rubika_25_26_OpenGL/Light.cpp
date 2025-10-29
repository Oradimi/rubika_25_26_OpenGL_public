#include "Shader.h"
#include "Light.h"

Light::Light() : _position(glm::vec3(0.f)),
_ambient(glm::vec3(1.f)), _diffuse(glm::vec3(1.f)), _scalar(glm::vec3(1.f))
{

}

Light::Light(
    const glm::vec3& position,
    const glm::vec3& ambient,
    float ambientIntensity,
    const glm::vec3& diffuse,
    float diffuseIntensity,
    const glm::vec3& scalar,
    float scalarIntensity
) : _position(position),
_ambient(ambient * ambientIntensity),
_diffuse(diffuse * diffuseIntensity),
_scalar(scalar * scalarIntensity)
{

}

void Light::Use(Shader& shader)
{
    GLint location = glGetUniformLocation(shader.Get(), "light.position");
    glUniform3f(location, _position.x, _position.y, _position.z);
    location = glGetUniformLocation(shader.Get(), "light.ambient");
    glUniform3f(location, _ambient.x, _ambient.y, _ambient.z);
    location = glGetUniformLocation(shader.Get(), "light.diffuse");
    glUniform3f(location, _diffuse.x, _diffuse.y, _diffuse.z);
    location = glGetUniformLocation(shader.Get(), "light.scalar");
    glUniform3f(location, _scalar.x, _scalar.y, _scalar.z);
}