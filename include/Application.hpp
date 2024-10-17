#ifndef CLASS_APPLICATION_HPP
#define CLASS_APPLICATION_HPP


#include "engine/graphics/objects/Model.hpp"
#include "engine/io/Camera.hpp"
#include "engine/io/Keyboard.hpp"
#include "engine/scene/ApplicationWindow.hpp"
#include "engine/graphics/memory/VAO.hpp"
#include "engine/graphics/rendering/Shader.hpp"

#include <memory>
namespace engine 
{
    class Application
    {
    public:
        Application();

        void run();
    private:
        std::unique_ptr<ApplicationWindow> m_sceneWindow;
        std::unique_ptr<Camera> m_Camera;
        std::vector<std::shared_ptr<Model>> m_Objects;

        void render();
        void renderShader(Shader shader);

        void processInputs(double dt);
    };
};
#endif // !CLASS_SCENE_HPP
