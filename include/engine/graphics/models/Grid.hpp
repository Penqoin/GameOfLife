#ifndef CLASS_GRID_HPP
#define CLASS_GRID_HPP

#include "engine/Defaults.hpp"
#include "engine/graphics/objects/Mesh.hpp"
#include "engine/graphics/objects/Model.hpp"
#include "engine/graphics/rendering/Shader.hpp"
#include "engine/io/Camera.hpp"
#include "engine/scene/ApplicationWindow.hpp"
#include "glm/fwd.hpp"
#include <cmath>
#include <cstdint>
#include <iostream>
namespace model 
{
    class Grid : public engine::Model
    {
    public:
        Grid(engine::ApplicationWindow* window)
        {
            float poses[] = {
               0.5f,  0.5f,  1.0f, 1.0f, // top right
             0.5f, -0.5f,  1.0f, 0.0f, // bottom right
            -0.5f, -0.5f,  0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f, 1.0f  // top left 
            };

            std::vector<unsigned int> indices = {
                0, 1, 3,  // first Triangle
                1, 2, 3   // second Triangle
            };

            std::vector<engine::Vertex> verts = engine::Vertex::genVertices(poses, 4, 4);            

            engine::Mesh m(verts, indices);
            this->setMesh(std::make_unique<engine::Mesh>(m));
        }
    };
};

#endif // !CLASS_GRID_HPP
