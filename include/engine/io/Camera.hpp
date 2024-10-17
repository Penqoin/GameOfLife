#ifndef CLASS_CAMERA_HPP
#define CLASS_CAMERA_HPP

// external
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraDirection
{
    NONE = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

/*
    camera class to help display from POV of camera
*/

namespace engine 
{
    class Camera
    {
    public:
        /*
            camera values
        */

        // position
        glm::vec3 cameraPos;

        glm::vec3 cameraFront = glm::vec3(0.f, 0.f, -1.f);
        glm::vec3 cameraUp = glm::vec3(0, 1.f, 0);
        glm::vec3 cameraRight = glm::vec3(-1.f, 0, 0);

        // camera rotational values
        float yaw; // x-axis
        float pitch; // y-axis

        // camera movement values
        float speed;
        float sensitivity;
        float zoom;

        /*
            constructor
        */

        Camera(glm::vec3 position = glm::vec3(0.f));

        /*
            modifiers
        */

        void updateCameraPos(CameraDirection direction, double dt);
        void updateCameraZoom(double dy);

        /*
            accessors
        */

        glm::mat4 getViewMatrix() { return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); }
        float getZoom() { return zoom; }

    private:
        /*
            private modifier
        */

        // change camera directional vectors based on movement
        void updateCameraVectors();
    };
}

#endif
