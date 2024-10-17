#include "engine/scene/ApplicationWindow.hpp"
#include "GLFW/glfw3.h"
#include "engine/io/Keyboard.hpp"
#include "engine/io/Mouse.hpp"

#include <iostream>

engine::ApplicationWindow::ApplicationWindow() : m_window(nullptr, glfwDestroyWindow), m_windowColor{0.f, 0.f, 0.f, 0.f}
{
   WindowName = "SampleWindow";
   WindowHeight = 800;
   WindowWidth = 800;
   

   m_contextVersionMajor = 3;
   m_contextVerionMinor = 3;

}

engine::ApplicationWindow::ApplicationWindow(
        uint32_t WindowHeight,
        uint32_t WindowWidth,
        std::string& WindowName,
        uint8_t contextVersionMajor, 
        uint8_t contextVersionMinor,
        std::array<float, 4> rgba
):  WindowHeight(WindowHeight), WindowWidth(WindowWidth), WindowName(WindowName), 
    m_contextVerionMinor(contextVersionMinor), m_contextVersionMajor(contextVersionMajor), m_window(nullptr, glfwDestroyWindow), m_windowColor(rgba) 
{}

engine::ApplicationWindow::~ApplicationWindow()
{
    glfwTerminate();
}

void engine::ApplicationWindow::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_contextVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_contextVerionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // create window hopefully successfull 
    std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> window(
        glfwCreateWindow(WindowWidth, WindowHeight, WindowName.c_str(), nullptr, nullptr),
        glfwDestroyWindow
    );    

    if (window.get() == NULL)
    {
        std::cout << "SYSTEM: FAILED to craete GLFW window, line 37 ApplicationWindow.cpp" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window.get());
    
    m_window = std::move(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std:: cout << "SYSTEM: FAILED TO INIT GLAD" << std::endl;
        return ;
    }

    glfwSetWindowUserPointer(m_window.get(), this);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, WindowWidth, WindowHeight);

    glfwSetFramebufferSizeCallback(m_window.get(), m_frameBufferSizeCallback);
    glfwSetKeyCallback(m_window.get(), Keyboard::keyCallback);
    glfwSetScrollCallback(m_window.get(), Mouse::mouseWheelCallback);
}

void engine::ApplicationWindow::updateWindow()
{
    glfwSwapBuffers(m_window.get());
    glfwPollEvents();

    glClearColor(m_windowColor[0], m_windowColor[1], m_windowColor[2], m_windowColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}


/*
 * HELPERS
 */

void engine::ApplicationWindow::setWindoWColor(std::array<float, 4> rgba)
{
    m_windowColor[0] = rgba[0];
    m_windowColor[1] = rgba[1];
    m_windowColor[2] = rgba[2];
    m_windowColor[3] = rgba[3];
}

bool engine::ApplicationWindow::shouldClose() { return glfwWindowShouldClose(m_window.get()); }
void engine::ApplicationWindow::setShouldClose(bool close) { glfwSetWindowShouldClose(m_window.get(), close); }
