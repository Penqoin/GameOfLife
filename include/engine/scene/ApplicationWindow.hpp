#ifndef CLASS_APPLICATION_WINDOW_HPP
#define CLASS_APPLICATION_WINDOW_HPP

#include "engine/graphics/rendering/Shader.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <cstdint>
#include <memory>
#include <span>
#include <string>

namespace engine 
{
    class ApplicationWindow 
    {
    public:
        uint32_t WindowWidth;
        uint32_t WindowHeight;

        std::string WindowName;

        /*
         * CONSTRUCTORS
         */
        //default
        ApplicationWindow();

        // custom values
        ApplicationWindow(
                uint32_t WindowHeight, 
                uint32_t WindowWidth, 
                std::string& WindowName, 
                uint8_t contextVersionMajor, 
                uint8_t contextVersionMinor,
                std::array<float, 4> rgba
        );


        ~ApplicationWindow();

        void init();

        /*
         * HELPERS
         */

        void updateWindow();

        void setWindoWColor(std::array<float, 4> rgba);

        bool shouldClose();
        void setShouldClose(bool close);

    private:
        std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> m_window;

        uint8_t m_contextVersionMajor;
        uint8_t m_contextVerionMinor;

        std::array<float, 4> m_windowColor;

        static void m_frameBufferSizeCallback(GLFWwindow* window, int width, int height)
        {
            ApplicationWindow* appWindow = static_cast<ApplicationWindow*>(glfwGetWindowUserPointer(window));
            appWindow->WindowHeight = height;
            appWindow->WindowWidth = width;
            
            glViewport(0, 0, width, height);
        }
    };
};

#endif // !CLASS_APPLICATION_WINDOW_HPP
