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
        Left,
        Up,
        Down,
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
    void ProcessKeyboard(int key, int pressed, float deltaTime);
    void ProcessMouse(float xoffset, float yoffset);
    void ProcessMouseScroll(float yoffset);

private:
    // Compute the Front and Right vector using the euler angles
    void UpdateCameraRotation();

    // Translation
    glm::vec3 _position;

    // Rotation - Must be normalized
    glm::vec3 _front;
    glm::vec3 _up;
    glm::vec3 _right;
    glm::vec3 _worldUp;

    // Euler Angles
    float _yaw;
    float _pitch;

    // Camera states
    bool _speedUp;

    // Camera options
    float _movementSpeed;
    float _mouseSensitivity;
    float _fov;
};