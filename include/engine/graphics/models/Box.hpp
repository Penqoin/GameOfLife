#ifndef CLASS_BOX_HPP
#define CLASS_BOX_HPP

#include "engine/graphics/memory/VAO.hpp"
#include "engine/graphics/objects/Model.hpp"
#include "glm/ext/matrix_transform.hpp"
namespace engine 
{
    class Box :  public Model
    {
    public:
        Box() : Model() 
        {
            unsigned int scale = 1;
            unsigned int offset = 2;
            float poses[] = {
                 0.5f * scale + offset,  0.5f * scale + offset,  // top right
                 0.5f * scale + offset, -0.5f * scale + offset,  // bottom right
                -0.5f * scale - offset, -0.5f * scale - offset,  // bottom left
                -0.5f * scale - offset,  0.5f * scale - offset,  // top left 
            };

            std::vector<unsigned int> indices = {
                0, 1, 3,  // first Triangle
                1, 2, 3   // second Triangle
            };

            std::vector<Vertex> verts = Vertex::genVertices(poses, 4);            

            Mesh m(verts, indices);
            this->setMesh(std::make_unique<Mesh>(m));


        }

        Box(float offset, int scale) :  Model() 
        {
            float poses[] = {
                 0.5f * scale + offset,  0.5f * scale + offset,  // top right
                 0.5f * scale + offset, -0.5f * scale - offset,  // bottom right
                -0.5f * scale - offset, -0.5f * scale - offset,  // bottom left
                -0.5f * scale - offset,  0.5f * scale + offset,  // top left 
            };

            std::vector<unsigned int> indices = {
                0, 1, 3,  // first Triangle
                1, 2, 3   // second Triangle
            };

            std::vector<Vertex> verts = Vertex::genVertices(poses, 4);            

            Mesh m(verts, indices);
            this->setMesh(std::make_unique<Mesh>(m));
        }

        virtual void render(Shader shader)
        {
            shader.activate();
    
            for (Instance& inst : m_instances)
            {
                glm::mat4 model(1.f);
                model = glm::translate(model, inst.position);
                model = glm::scale(model, inst.scale);

                shader.setMat4("model", model);
                shader.setFloat4("color", glm::vec4(1.f));
                m_Mesh->vao.bind();
                m_Mesh->vao.drawArrays(GL_LINE_LOOP, 0, 4);

                m_Mesh->vao.unbind();
            }
        }
    };
};

#endif // !CLASS_SQUARE_HPP
