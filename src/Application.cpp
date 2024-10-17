#include "Application.hpp"
#include "engine/graphics/models/Grid.hpp"
#include "iostream"
#include "GLFW/glfw3.h"
#include "engine/graphics/memory/VAO.hpp"
#include "engine/graphics/models/Box.hpp"
#include "engine/graphics/models/Square.hpp"
#include "engine/io/Camera.hpp"
#include "engine/io/Mouse.hpp"
#include "glm/fwd.hpp"
#include <algorithm>
#include <memory>


engine::Application::Application()
{
    m_sceneWindow = std::make_unique<ApplicationWindow>();
    m_sceneWindow->init();

    m_Camera = std::make_unique<Camera>();
}

void engine::Application::run()
{
    Shader shader("default.vert", "default.frag");
    Shader gridShader("grid.vert", "grid.frag");
    m_sceneWindow->setWindoWColor({0.f, 0.f, 0.f, 1.f});

    model::Grid grid(m_sceneWindow.get());
    grid.addInstance(Instance(glm::vec2(0.f), glm::vec3(.5f), glm::vec3(.5f), Texture("somthing.jpg")));

    gridShader.activate();
    gridShader.setInt("text", 0);
    
    double dt = 0.f, lastFrame = 0.f;
    float time = dt;
    while(!m_sceneWindow->shouldClose())
    {
        double currTime = glfwGetTime();
        dt = currTime - lastFrame;
        lastFrame = currTime;

        processInputs(dt);
        time += dt;


        // render grid then rest of objects
        renderShader(gridShader);
        gridShader.activate();
        gridShader.setFloat("time", time);
        grid.render(gridShader);

        renderShader(shader);
        for (std::shared_ptr<Model> m : m_Objects)
            m->render(shader);


        m_sceneWindow->updateWindow();
    }
}

void engine::Application::renderShader(engine::Shader shader)
{
    shader.activate();
    glm::mat4 projection = glm::perspective(glm::radians(m_Camera->getZoom()),(float)m_sceneWindow->WindowWidth / (float)m_sceneWindow->WindowHeight, 0.1f, 100.f);

    shader.setMat4("proj", projection);
    shader.setMat4("view", m_Camera->getViewMatrix());
    shader.setFloat3("PosCamera", m_Camera->cameraPos);
}

void engine::Application::processInputs(double dt)
{
    double scrollDy = Mouse::getScrollDy();
    if (scrollDy != 0)
        m_Camera->updateCameraZoom(scrollDy);

    else if (Keyboard::key(GLFW_KEY_ESCAPE))
        m_sceneWindow->setShouldClose(true);

    else if (Keyboard::key(GLFW_KEY_W))
        m_Camera->updateCameraPos(CameraDirection::UP, dt);
    else if (Keyboard::key(GLFW_KEY_S))
        m_Camera->updateCameraPos(CameraDirection::DOWN, dt);
    else if (Keyboard::key(GLFW_KEY_D))
        m_Camera->updateCameraPos(CameraDirection::RIGHT, dt);
    else if (Keyboard::key(GLFW_KEY_A))
        m_Camera->updateCameraPos(CameraDirection::LEFT, dt);
}
