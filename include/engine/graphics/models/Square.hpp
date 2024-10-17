#ifndef CLASS_SQUARE_HPP
#define CLASS_SQUARE_HPP

#include "engine/graphics/objects/Model.hpp"
namespace engine 
{
    class Square: public Model
    {
    public:
        Square() : Model() 
        {
            float poses[] = {
                 0.5f,  0.5f,  // top right
                 0.5f, -0.5f,  // bottom right
                -0.5f, -0.5f,  // bottom left
                -0.5f,  0.5f,  // top left 
            };

            std::vector<unsigned int> indices = {
                0, 1, 3,  // first Triangle
                1, 2, 3   // second Triangle
            };

            std::vector<Vertex> verts = Vertex::genVertices(poses, 4);            

            Mesh m(verts, indices);
            this->setMesh(std::make_unique<Mesh>(m));
        }
    };
};

#endif // !CLASS_SQUARE_HPP
