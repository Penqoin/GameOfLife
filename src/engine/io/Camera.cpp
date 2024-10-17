#include "engine/io/Camera.hpp"
#include "engine/scene/Environment.hpp"
#include "glm/trigonometric.hpp"
#include <cmath>
#include <iostream>

/*
    constructor
*/

// default and initialize with position
engine::Camera::Camera(glm::vec3 position)
    : cameraPos(position),
    yaw(-90.0f),
    pitch(0.0f),
    speed(3.f),
    sensitivity(0.01f),
    zoom(45.0f)
{
    updateCameraVectors();
}

/*
    modifiers
*/

void engine::Camera::updateCameraPos(CameraDirection direction, double dt)
{
    float velocity =  dt * speed;

    switch (direction)
    {
    case CameraDirection::RIGHT:
        cameraPos += cameraRight * velocity;
        break;
    case CameraDirection::LEFT:
        cameraPos -= cameraRight * velocity;
        break;
    case CameraDirection::UP:
        cameraPos += cameraUp * velocity;
        break;
    case CameraDirection::DOWN:
        cameraPos -= cameraUp * velocity;
        break;
    }
}

// change camera zoom (scroll wheel)
void engine::Camera::updateCameraZoom(double dy)
{
    if (zoom >= 0.5f && zoom <= 100.0f)
        zoom -= dy;
    else if (zoom < 0.5f)
        zoom = 1.0f;
}

/*
    private modifier
*/

// change camera directional vectors based on movement
void engine::Camera::updateCameraVectors()
{
    glm::vec3 front;

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    cameraRight = glm::normalize(glm::cross(front, Environment::worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, front));
}
