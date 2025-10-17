#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
    enum class Direction
    {
        Forward,
        Backward,
        Right,
        Left
    };

    Camera();
    Camera(const glm::vec3& pos,
        const glm::vec3& worldUp,
        float pitch,
        float yaw);

    // use glm::lookAt
    glm::mat4 GetMatrix() const;

    float GetFov() const;

    glm::vec3 Pos() const;

    // Input
    void ProcessKeyboard(Direction direction, float deltaTime);
    void ProcessMouse(float xoffset, float yoffset);
    void ProcessMouseScroll(float yoffset);

private:
    // Compute the Front and Right vector using the euler angles
    void UpdateCameraRotation();

    // Translation
    glm::vec3 Position;

    // Rotation - Must be normalized
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Euler Angles
    float Yaw;
    float Pitch;

    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Fov;
};