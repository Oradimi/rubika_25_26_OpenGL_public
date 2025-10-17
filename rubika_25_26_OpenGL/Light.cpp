#include "Shader.h"
#include "Light.h"

Light::Light() : Position(glm::vec3(0.f)),
Ambient(glm::vec3(1.f)), Diffuse(glm::vec3(1.f)), Scalar(glm::vec3(1.f))
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
) : Position(position),
Ambient(ambient * ambientIntensity),
Diffuse(diffuse * diffuseIntensity),
Scalar(scalar * scalarIntensity)
{

}

void Light::Use(Shader& shader)
{
    GLint location = glGetUniformLocation(shader.Get(), "light.position");
    glUniform3f(location, Position.x, Position.y, Position.z);
    location = glGetUniformLocation(shader.Get(), "light.ambient");
    glUniform3f(location, Ambient.x, Ambient.y, Ambient.z);
    location = glGetUniformLocation(shader.Get(), "light.diffuse");
    glUniform3f(location, Diffuse.x, Diffuse.y, Diffuse.z);
    location = glGetUniformLocation(shader.Get(), "light.scalar");
    glUniform3f(location, Scalar.x, Scalar.y, Scalar.z);
}