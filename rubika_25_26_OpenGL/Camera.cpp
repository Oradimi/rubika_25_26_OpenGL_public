#include "Camera.h"

#define M_PI 3.14159265358979323846264338327950288f

Camera::Camera() : Position(glm::vec3(0.f, 1.f, -3.f)), WorldUp(glm::vec3(0.f, 1.f, 0.f)),
Pitch(0.f), Yaw(0.f), MovementSpeed(10.f), MouseSensitivity(1.f), Fov(70.f),
Front(std::cosf(Pitch) * std::sinf(Yaw), std::sinf(Pitch),
                     std::cosf(Pitch)* std::cosf(Yaw)),
Right(std::sinf(Yaw + M_PI / 2.f), 0.f,
                std::cosf(Yaw + M_PI / 2.f)),
Up(glm::cross(Front, Right))
{

}

Camera::Camera(const glm::vec3& pos,
    const glm::vec3& worldUp,
    float pitch,
    float yaw) : Position(pos), WorldUp(worldUp), Pitch(pitch), Yaw(yaw),
    MovementSpeed(10.f), MouseSensitivity(1.f), Fov(45.f),
    Front(std::cosf(Pitch)* std::sinf(Yaw), std::sinf(Pitch),
        std::cosf(Pitch)* std::cosf(Yaw)),
    Right(std::sinf(Yaw + M_PI / 2.f), 0.f,
        std::cosf(Yaw + M_PI / 2.f)),
    Up(glm::cross(Front, Right))
{

}

// use glm::lookAt
glm::mat4 Camera::GetMatrix() const
{
    return glm::lookAt(Position, Position + Front, WorldUp);
}

float Camera::GetFov() const
{
    return Fov;
}

glm::vec3 Camera::Pos() const
{
    return Position;
}

// Input
void Camera::ProcessKeyboard(Direction direction, float deltaTime)
{
    switch (direction)
    {
    case Direction::Forward:
        Position += deltaTime * Front;
        break;
    case Direction::Left:
        Position += deltaTime * Right;
        break;
    case Direction::Backward:
        Position -= deltaTime * Front;
        break;
    case Direction::Right:
        Position -= deltaTime * Right;
        break;
    }
}

void Camera::ProcessMouse(float xoffset, float yoffset)
{
    float degrees = xoffset * 0.3f;

    Yaw -= glm::radians(degrees);

    degrees = yoffset * 0.3f;

    Pitch -= glm::radians(degrees);
    Pitch = glm::clamp(Pitch, -M_PI / 2.f + 0.1f, M_PI / 2.f - 0.1f);

    UpdateCameraRotation();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Fov -= yoffset * 5.f;
}

// Compute the Front and Right vector using the euler angles
void Camera::UpdateCameraRotation()
{
    Front = { std::cosf(Pitch) * std::sinf(Yaw), std::sinf(Pitch),
                     std::cosf(Pitch) * std::cosf(Yaw) };
    Right = { std::sinf(Yaw + M_PI / 2.f), 0.f,
                    std::cosf(Yaw + M_PI / 2.f) };
    Up = glm::cross(Front, Right);
}