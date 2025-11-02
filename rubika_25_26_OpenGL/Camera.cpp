#include "Camera.h"
#include <glfw/glfw3.h>

#define M_PI 3.14159265358979323846264338327950288f

Camera::Camera() : _position(glm::vec3(1.f, 1.f, -5.f)), _worldUp(glm::vec3(0.f, 1.f, 0.f)),
_speedUp(false), _pitch(0.f), _yaw(0.f), _movementSpeed(1.f), _mouseSensitivity(1.f), _fov(70.f),
_front(std::cosf(_pitch) * std::sinf(_yaw), std::sinf(_pitch),
                     std::cosf(_pitch)* std::cosf(_yaw)),
_right(std::sinf(_yaw + M_PI / 2.f), 0.f,
                std::cosf(_yaw + M_PI / 2.f)),
_up(glm::cross(_front, _right))
{

}

Camera::Camera(const glm::vec3& pos,
    const glm::vec3& worldUp,
    float pitch,
    float yaw) : _position(pos), _worldUp(worldUp),
    _speedUp(false), _pitch(pitch), _yaw(yaw),
    _movementSpeed(1.f), _mouseSensitivity(1.f), _fov(45.f),
    _front(std::cosf(_pitch)* std::sinf(_yaw), std::sinf(_pitch),
        std::cosf(_pitch)* std::cosf(_yaw)),
    _right(std::sinf(_yaw + M_PI / 2.f), 0.f,
        std::cosf(_yaw + M_PI / 2.f)),
    _up(glm::cross(_front, _right))
{

}

// use glm::lookAt
glm::mat4 Camera::GetMatrix() const
{
    return glm::lookAt(_position, _position + _front, _worldUp);
}

float Camera::GetFov() const
{
    return _fov;
}

glm::vec3 Camera::Pos() const
{
    return _position;
}

// Input
void Camera::ProcessKeyboard(Direction direction, float deltaTime)
{
    float processedSpeedDelta = deltaTime * (_speedUp ? _movementSpeed * 5.f : _movementSpeed);

    switch (direction)
    {
    case Direction::Forward:
        _position += processedSpeedDelta * _front;
        break;
    case Direction::Left:
        _position += processedSpeedDelta * _right;
        break;
    case Direction::Backward:
        _position -= processedSpeedDelta * _front;
        break;
    case Direction::Right:
        _position -= processedSpeedDelta * _right;
        break;
    case Direction::Up:
        _position += processedSpeedDelta * _worldUp;
        break;
    case Direction::Down:
        _position -= processedSpeedDelta * _worldUp;
        break;
    }
}

void Camera::ProcessKeyboard(int key, int pressed, float deltaTime)
{
    switch (key)
    {
    case GLFW_KEY_LEFT_SHIFT:
        _speedUp = pressed;
        break;
    }
}

void Camera::ProcessMouse(float xoffset, float yoffset)
{
    float degrees = xoffset * 0.3f;

    _yaw -= glm::radians(degrees);

    degrees = yoffset * 0.3f;

    _pitch -= glm::radians(degrees);
    _pitch = glm::clamp(_pitch, -M_PI / 2.f + 0.1f, M_PI / 2.f - 0.1f);

    UpdateCameraRotation();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    _fov -= yoffset * 5.f;
}

// Compute the Front and Right vector using the euler angles
void Camera::UpdateCameraRotation()
{
    _front = { std::cosf(_pitch) * std::sinf(_yaw), std::sinf(_pitch),
                     std::cosf(_pitch) * std::cosf(_yaw) };
    _right = { std::sinf(_yaw + M_PI / 2.f), 0.f,
                    std::cosf(_yaw + M_PI / 2.f) };
    _up = glm::cross(_front, _right);
}